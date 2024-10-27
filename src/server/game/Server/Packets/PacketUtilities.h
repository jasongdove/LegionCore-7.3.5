/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#ifndef PacketUtilities_h__
#define PacketUtilities_h__

#include "ByteBuffer.h"
#include "Duration.h"
#include <ctime>

namespace WorldPackets
{
    class PacketArrayMaxCapacityException : public ByteBufferException
    {
    public:
        PacketArrayMaxCapacityException(std::size_t requestedSize, std::size_t sizeLimit)
        {
            std::ostringstream builder;
            builder << "Attempted to read more array elements from packet " << requestedSize << " than allowed " << sizeLimit;
            message().assign(builder.str());
        }
    };

    /**
     * Utility class for automated prevention of loop counter spoofing in client packets
     */
    template<typename T, std::size_t N>
    class Array
    {
    public:
        typedef boost::container::static_vector<T, N> storage_type;

        typedef std::integral_constant<std::size_t, N> max_capacity;

        typedef typename storage_type::value_type value_type;
        typedef typename storage_type::size_type size_type;
        typedef typename storage_type::reference reference;
        typedef typename storage_type::const_reference const_reference;
        typedef typename storage_type::iterator iterator;
        typedef typename storage_type::const_iterator const_iterator;

        Array() { }

        iterator begin() { return _storage.begin(); }
        const_iterator begin() const { return _storage.begin(); }

        iterator end() { return _storage.end(); }
        const_iterator end() const { return _storage.end(); }

        size_type size() const { return _storage.size(); }
        bool empty() const { return _storage.empty(); }

        reference operator[](size_type i) { return _storage[i]; }
        const_reference operator[](size_type i) const { return _storage[i]; }

        void resize(size_type newSize)
        {
            if (newSize > max_capacity::value)
                throw PacketArrayMaxCapacityException(newSize, max_capacity::value);

            _storage.resize(newSize);
        }

        void push_back(value_type const& value)
        {
            if (_storage.size() >= max_capacity::value)
                throw PacketArrayMaxCapacityException(_storage.size() + 1, max_capacity::value);

            _storage.push_back(value);
        }

        void push_back(value_type&& value)
        {
            if (_storage.size() >= max_capacity::value)
                throw PacketArrayMaxCapacityException(_storage.size() + 1, max_capacity::value);

            _storage.push_back(std::forward<value_type>(value));
        }

    private:
        storage_type _storage;
    };

    template<typename Underlying = uint32>
    class Timestamp
    {
    public:
        Timestamp() = default;
        Timestamp(time_t value) : _value(value) { }
        Timestamp(std::chrono::system_clock::time_point const& systemTime) : _value(std::chrono::system_clock::to_time_t(systemTime)) { }

        Timestamp& operator=(time_t value)
        {
            _value = value;
            return *this;
        }

        Timestamp& operator=(std::chrono::system_clock::time_point const& systemTime)
        {
            _value = std::chrono::system_clock::to_time_t(systemTime);
            return *this;
        }

        operator time_t() const
        {
            return _value;
        }

        Underlying AsUnderlyingType() const
        {
            return static_cast<Underlying>(_value);
        }

        friend ByteBuffer& operator<<(ByteBuffer& data, Timestamp timestamp)
        {
            data << static_cast<Underlying>(timestamp._value);
            return data;
        }

        friend ByteBuffer& operator>>(ByteBuffer& data, Timestamp& timestamp)
        {
            timestamp._value = data.read<time_t, Underlying>();
            return data;
        }

    private:
        time_t _value = time_t(0);
    };

    template<typename ChronoDuration, typename Underlying = uint32>
    class Duration
    {
    public:
        Duration() = default;
        Duration(ChronoDuration value) : _value(value) { }

        Duration& operator=(ChronoDuration value)
        {
            _value = value;
            return *this;
        }

        operator ChronoDuration() const
        {
            return _value;
        }

        friend ByteBuffer& operator<<(ByteBuffer& data, Duration duration)
        {
            data << static_cast<Underlying>(duration._value.count());
            return data;
        }

        friend ByteBuffer& operator>>(ByteBuffer& data, Duration& duration)
        {
            duration._value = ChronoDuration(data.read<Underlying>());
            return data;
        }

    private:
        ChronoDuration _value = ChronoDuration::zero();
    };

    template <typename T>
    class CompactArray
    {
    public:
        CompactArray() : _mask(0) { }

        CompactArray(CompactArray const& right) : _mask(right._mask), _contents(right._contents)
        { }

        CompactArray(CompactArray&& right) noexcept : _mask(right._mask), _contents(std::move(right._contents))
        {
            right._mask = 0;
        }

        CompactArray& operator= (CompactArray const& right)
        {
            _mask = right._mask;
            _contents = right._contents;
            return *this;
        }

        CompactArray& operator= (CompactArray&& right) noexcept
        {
            _mask = right._mask;
            right._mask = 0;
            _contents = std::move(right._contents);
            return *this;
        }

        uint32 GetMask() const { return _mask; }
        T const& operator[](size_t index) const { return _contents[index]; }
        size_t GetSize() const { return _contents.size(); }

        void Insert(size_t index, T const& value)
        {
            ASSERT(index < 0x20);

            _mask |= 1 << index;
            if (_contents.size() <= index)
                _contents.resize(index + 1);
            _contents[index] = value;
        }

        void Clear()
        {
            _mask = 0;
            _contents.clear();
        }

        bool operator==(CompactArray const& r) const
        {
            if (_mask != r._mask)
                return false;

            return _contents == r._contents;
        }

        bool operator!=(CompactArray const& r) const { return !(*this == r); }

    private:
        uint32 _mask;
        std::vector<T> _contents;
    };

    template <typename T>
    ByteBuffer& operator<<(ByteBuffer& data, CompactArray<T> const& v)
    {
        uint32 mask = v.GetMask();
        data << uint32(mask);
        for (size_t i = 0; i < v.GetSize(); ++i)
        {
            if (mask & (1 << i))
                data << v[i];
        }

        return data;
    }

    template <typename T>
    ByteBuffer& operator >> (ByteBuffer& data, CompactArray<T>& v)
    {
        uint32 mask;
        data >> mask;

        for (size_t index = 0; mask != 0; mask >>= 1, ++index)
        {
            if ((mask & 1) != 0)
            {
                T value;
                data >> value;
                v.Insert(index, value);
            }
        }

        return data;
    }
}

#endif // PacketUtilities_h__