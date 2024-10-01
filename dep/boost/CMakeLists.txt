# This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(BOOST_SEARCH_HINTS)
if(WIN32)
  if(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
  endif()
  if(DEFINED BOOST_ROOT AND MSVC)
    # insert a dot (.) character before last digit of MSVC_TOOLSET_VERSION
    # turn 143 into 14.3
    string(LENGTH "${MSVC_TOOLSET_VERSION}" _BOOST_MSVC_TOOLSET_VERSION_LENGTH)
    math(EXPR _BOOST_MSVC_TOOLSET_VERSION_LENGTH "${_BOOST_MSVC_TOOLSET_VERSION_LENGTH} - 1" OUTPUT_FORMAT DECIMAL)
    string(SUBSTRING "${MSVC_TOOLSET_VERSION}" 0 ${_BOOST_MSVC_TOOLSET_VERSION_LENGTH} _BOOST_MSVC_TOOLSET_VERSION_MAJOR)
    string(SUBSTRING "${MSVC_TOOLSET_VERSION}" ${_BOOST_MSVC_TOOLSET_VERSION_LENGTH} -1 _BOOST_MSVC_TOOLSET_VERSION_MINOR)

    set(BOOST_SEARCH_HINTS "${BOOST_ROOT}/lib${PLATFORM}-msvc-${_BOOST_MSVC_TOOLSET_VERSION_MAJOR}.${_BOOST_MSVC_TOOLSET_VERSION_MINOR}/cmake")

    unset(_BOOST_MSVC_TOOLSET_VERSION_LENGTH)
    unset(_BOOST_MSVC_TOOLSET_VERSION_MAJOR)
    unset(_BOOST_MSVC_TOOLSET_VERSION_MINOR)
  endif()

  set(Boost_USE_STATIC_LIBS        ON)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME     OFF)
endif()

if (WIN32)
  # On windows the requirements are higher according to the wiki.
  set(BOOST_REQUIRED_VERSION 1.78)
else()
  set(BOOST_REQUIRED_VERSION 1.74)
endif()

find_package(Boost ${BOOST_REQUIRED_VERSION}
  REQUIRED
  COMPONENTS
    system
    filesystem
    thread
    program_options
    iostreams
    regex
    locale
  CONFIG
  HINTS
    ${BOOST_SEARCH_HINTS})

# Find if Boost was compiled in C++03 mode because it requires -DBOOST_NO_CXX11_SCOPED_ENUMS

include (CheckCXXSourceCompiles)

set(CMAKE_REQUIRED_INCLUDES ${Boost_INCLUDE_DIR})
set(CMAKE_REQUIRED_LIBRARIES ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
set(CMAKE_REQUIRED_FLAGS "-std=c++11")
unset(boost_filesystem_copy_links_without_NO_SCOPED_ENUM CACHE)
check_cxx_source_compiles("
  #include <boost/filesystem/path.hpp>
  #include <boost/filesystem/operations.hpp>
  int main() { boost::filesystem::copy_file(boost::filesystem::path(), boost::filesystem::path()); }"
boost_filesystem_copy_links_without_NO_SCOPED_ENUM)
unset(CMAKE_REQUIRED_INCLUDES CACHE)
unset(CMAKE_REQUIRED_LIBRARIES CACHE)
unset(CMAKE_REQUIRED_FLAGS CACHE)

if (NOT boost_filesystem_copy_links_without_NO_SCOPED_ENUM)
  set(OPTIONAL_BOOST_NO_SCOPED_ENUMS -DBOOST_NO_CXX11_SCOPED_ENUMS)
endif()

add_library(boost INTERFACE)

target_link_libraries(boost
  INTERFACE
    ${Boost_LIBRARIES})

target_include_directories(boost
  INTERFACE
    ${Boost_INCLUDE_DIRS})

target_compile_definitions(boost
  INTERFACE
    -DBOOST_DATE_TIME_NO_LIB
    -DBOOST_REGEX_NO_LIB
    -DBOOST_CHRONO_NO_LIB
    ${OPTIONAL_BOOST_NO_SCOPED_ENUMS})
