/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "DB2Store.h"
#include "ByteBuffer.h"
#include "DB2DatabaseLoader.h"
#include "DB2Meta.h"
#include <boost/filesystem/operations.hpp>

struct DB2FileSystemSource : public DB2FileSource
{
    DB2FileSystemSource(std::string const& fileName)
    {
        _fileName = fileName;
        _file = fopen(_fileName.c_str(), "rb");
    }

    ~DB2FileSystemSource()
    {
        if (_file)
            fclose(_file);
    }

    bool IsOpen() const override
    {
        return _file != nullptr;
    }

    bool Read(void* buffer, std::size_t numBytes) override
    {
        return fread(buffer, numBytes, 1, _file) == 1;
    }

    std::size_t GetPosition() const override
    {
        return ftell(_file);
    }

    std::size_t GetFileSize() const override
    {
        boost::system::error_code error;
        std::size_t size = boost::filesystem::file_size(_fileName, error);
        return !error ? size : 0;
    }

    char const* GetFileName() const override
    {
        return _fileName.c_str();
    }

private:
    std::string _fileName;
    FILE* _file;
};

DB2StorageBase::DB2StorageBase(char const* fileName, DB2LoadInfo const* loadInfo)
    : _tableHash(0), _layoutHash(0), _fileName(fileName), _fieldCount(0), _loadInfo(loadInfo), _dataTable(nullptr), _dataTableEx(nullptr), _indexTable(nullptr), _indexTableSize(0)
{
}

DB2StorageBase::~DB2StorageBase()
{
    delete[] _dataTable;
    delete[] _dataTableEx;
    for (char* strings : _stringPool)
        delete[] strings;
    delete[] _indexTable;
}

void DB2StorageBase::WriteRecord(uint32 id, uint32 locale, ByteBuffer& buffer) const
{
    ASSERT(id < _indexTableSize);
    char const* entry = ASSERT_NOTNULL(_indexTable[id]);

    std::size_t i = 0;
    if (!_loadInfo->Meta->HasIndexFieldInData())
    {
        entry += 4;
        ++i;
    }

    for (; i < _loadInfo->FieldCount; ++i)
    {
        switch (_loadInfo->TypesString[i])
        {
            case FT_INT:
                buffer << *reinterpret_cast<uint32 const*>(entry);
                entry += 4;
                break;
            case FT_FLOAT:
                buffer << *reinterpret_cast<float const*>(entry);
                entry += 4;
                break;
            case FT_BYTE:
                buffer << *reinterpret_cast<uint8 const*>(entry);
                entry += 1;
                break;
            case FT_SHORT:
                buffer << *reinterpret_cast<uint16 const*>(entry);
                entry += 2;
                break;
            case FT_LONG:
                buffer << *reinterpret_cast<uint64 const*>(entry);
                entry += 8;
                break;
            case FT_STRING:
            {
                auto locStr = *reinterpret_cast<LocalizedString const*>(entry);
                if (locStr.Str[locale][0] == '\0')
                    buffer << locStr.Str[0];
                else
                    buffer << locStr.Str[locale];

                entry += sizeof(LocalizedString*);
                break;
            }
            case FT_STRING_NOT_LOCALIZED:
            {
                buffer << *reinterpret_cast<char const* const*>(entry);
                entry += sizeof(char const*);
                break;
            }
        }
    }
}

bool DB2StorageBase::Load(std::string const& path, uint32 locale)
{
    DB2FileLoader db2;
    {
        DB2FileSystemSource source(path + _fileName);
        if (!db2.Load(&source, _loadInfo))
            return false;
    }

    _fieldCount = db2.GetCols();
    _tableHash = db2.GetTableHash();
    _layoutHash = db2.GetLayoutHash();

    // load raw non-string data
    _dataTable = db2.AutoProduceData(_indexTableSize, _indexTable, _stringPool);

    // load strings from db2 data
    if (!_stringPool.empty())
        if (char* stringBlock = db2.AutoProduceStrings(_indexTable, _indexTableSize, locale))
            _stringPool.push_back(stringBlock);

    db2.AutoProduceRecordCopies(_indexTableSize, _indexTable, _dataTable);

    // error in db2 file at loading if NULL
    return _indexTable != nullptr;
}

bool DB2StorageBase::LoadStringsFrom(std::string const& path, uint32 locale)
{
    // DB2 must be already loaded using Load
    if (!_indexTable)
        return false;

    DB2FileLoader db2;
    {
        DB2FileSystemSource source(path + _fileName);
        // Check if load was successful, only then continue
        if (!db2.Load(&source, _loadInfo))
            return false;
    }

    // load strings from another locale db2 data
    if (_loadInfo->GetStringFieldCount(true))
        if (char* stringBlock = db2.AutoProduceStrings(_indexTable, _indexTableSize, locale))
            _stringPool.push_back(stringBlock);

    return true;
}

void DB2StorageBase::LoadFromDB()
{
    char* extraStringHolders = nullptr;
    _dataTableEx = DB2DatabaseLoader(_fileName, _loadInfo).Load(_indexTableSize, _indexTable, extraStringHolders, _stringPool);
    if (extraStringHolders)
        _stringPool.push_back(extraStringHolders);
}

void DB2StorageBase::LoadStringsFromDB(uint32 locale)
{
    if (!_loadInfo->GetStringFieldCount(true))
        return;

    DB2DatabaseLoader(_fileName, _loadInfo).LoadStrings(locale, _indexTableSize, _indexTable, _stringPool);
}
