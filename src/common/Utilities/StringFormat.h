/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

#ifndef TRINITYCORE_STRING_FORMAT_H
#define TRINITYCORE_STRING_FORMAT_H

#include "fmt/printf.h"
#include <fmt/core.h>

namespace Trinity
{
    /// Default TC string format function.
    template<typename... Args>
    std::string StringFormat(std::string_view fmt, Args&&... args)
    {
        try
        {
            return fmt::sprintf(fmt, std::forward<Args>(args)...);
        }
        catch (fmt::format_error const& formatError)
        {
            std::string error = "An error occurred formatting string \"" + std::string(fmt) + "\" : " + formatError.what();
            return error;
        }
    }

    /// Returns true if the given char pointer is null.
    inline bool IsFormatEmptyOrNull(char const* fmt)
    {
        return fmt == nullptr;
    }

    /// Returns true if the given std::string is empty.
    inline bool IsFormatEmptyOrNull(std::string const& fmt)
    {
        return fmt.empty();
    }

    /// Returns true if the given std::string_view is empty.
    inline bool IsFormatEmptyOrNull(std::string_view const& fmt)
    {
        return fmt.empty();
    }
}

// allow implicit enum to int conversions for formatting
template <typename E, std::enable_if_t<std::is_enum_v<E>, std::nullptr_t> = nullptr>
auto format_as(E e) { return std::underlying_type_t<E>(e); }

#endif
