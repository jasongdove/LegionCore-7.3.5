/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

#ifndef TRINITYCORE_COMMON_H
#define TRINITYCORE_COMMON_H

#include "Define.h"
#include <memory>
#include <string>
#include <utility>

#if TRINITY_PLATFORM == TRINITY_PLATFORM_WINDOWS
#  if TRINITY_COMPILER == TRINITY_COMPILER_INTEL
#    if !defined(BOOST_ASIO_HAS_MOVE)
#      define BOOST_ASIO_HAS_MOVE
#    endif // !defined(BOOST_ASIO_HAS_MOVE)
#  endif // if TRINITY_COMPILER == TRINITY_COMPILER_INTEL
#else
#  include <sys/types.h>
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <unistd.h>
#  include <netdb.h>
#  include <cstdlib>
#endif

#if TRINITY_COMPILER == TRINITY_COMPILER_MICROSOFT

#define snprintf _snprintf
#define atoll _atoi64
#define vsnprintf _vsnprintf
#define llabs _abs64

#else

#define stricmp strcasecmp
#define strnicmp strncasecmp

#endif

inline unsigned long atoul(char const* str) { return strtoul(str, nullptr, 10); }
inline unsigned long long atoull(char const* str) { return strtoull(str, nullptr, 10); }

#define STRINGIZE(a) #a

enum TimeConstants
{
    ONE_SECOND      = 1,
    THREE_SECONDS   = 3,
    FIVE_SECONDS    = 5,
    HALF_MINUTE     = 30,
    MINUTE          = 60,
    HOUR            = MINUTE*60,
    DAY             = HOUR*24,
    WEEK            = DAY*7,
    MONTH           = DAY*30,
    YEAR            = MONTH*12,
    IN_MILLISECONDS = 1000
};

enum AccountTypes
{
    SEC_PLAYER                = 0,
    SEC_MODERATOR             = 1,
    SEC_GAMEMASTER            = 2,
    SEC_CONFIRMED_GAMEMASTER  = 3,
    SEC_REALM_LEADER          = 4,
    SEC_GM_LEADER             = 5,
    SEC_ADMINISTRATOR         = 6,
    SEC_CONSOLE               = 7                                  // must be always last in list, accounts must have less security level always also
};

enum LocaleConstant : uint8
{
    LOCALE_enUS = 0,
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    LOCALE_ruRU = 8,
    LOCALE_none = 9,
    LOCALE_ptBR = 10,
    LOCALE_itIT = 11,

    MAX_LOCALES
};

const uint8 OLD_TOTAL_LOCALES = 9; /// @todo convert in simple system
#define DEFAULT_LOCALE LOCALE_enUS

#define TOTAL_LOCALES 11

TC_COMMON_API extern char const* localeNames[MAX_LOCALES];

TC_COMMON_API LocaleConstant GetLocaleByName(std::string const& name);

#pragma pack(push, 1)

struct TC_COMMON_API LocalizedString
{
    char const* Str[MAX_LOCALES];

    LocalizedString();
    explicit LocalizedString(char const* val);
    char const* Get(uint32 locale) const;
};

#pragma pack(pop)

// we always use stdlib std::max/std::min, undefine some not C++ standard defines (Win API and some other platforms)
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#ifndef M_PI_F
#  define M_PI_F        float(M_PI)
#endif

#ifndef M_RAD
#define M_RAD           57.295779513082320876846364344191f
#endif

#define MAX_QUERY_LEN 32*1024

namespace Trinity
{
    using std::make_unique;
}

#endif
