/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "SHA256.h"
#include "BigNumber.h"
#include "Errors.h"
#include <cstring>
#include <cstdarg>

SHA256Hash::SHA256Hash() : _ctx(EVP_MD_CTX_create())
{
    EVP_DigestInit_ex(_ctx, EVP_sha256(), nullptr);
    memset(mDigest, 0, SHA256_DIGEST_LENGTH * sizeof(uint8));
}

SHA256Hash::~SHA256Hash()
{
    EVP_MD_CTX_destroy(_ctx);
    _ctx = nullptr;
}

void SHA256Hash::UpdateData(uint8 const* data, size_t len)
{
    EVP_DigestUpdate(_ctx, data, len);
}

void SHA256Hash::UpdateData(const std::string &str)
{
    UpdateData((uint8 const*)str.c_str(), str.length());
}

void SHA256Hash::UpdateBigNumbers(BigNumber* bn0, ...)
{
    va_list v;

    va_start(v, bn0);
    auto bn = bn0;
    while (bn)
    {
        UpdateData(bn->AsByteArray().get(), bn->GetNumBytes());
        bn = va_arg(v, BigNumber*);
    }
    va_end(v);
}

void SHA256Hash::Initialize()
{
    EVP_DigestInit_ex(_ctx, EVP_sha256(), nullptr);
}

void SHA256Hash::Finalize(void)
{
    uint32 length = SHA256_DIGEST_LENGTH;
    EVP_DigestFinal_ex(_ctx, mDigest, &length);
    ASSERT(length == SHA256_DIGEST_LENGTH);
}

uint8* SHA256Hash::GetDigest()
{
    return mDigest;
}

uint32 SHA256Hash::GetLength() const
{
    return SHA256_DIGEST_LENGTH;
}
