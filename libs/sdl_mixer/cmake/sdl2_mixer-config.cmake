# SDL2_mixer CMake configuration file:
# This file is meant to be placed in a cmake subfolder of SDL2_mixer-devel-2.x.y-mingw

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(SDL2_MIXER_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../i686-w64-mingw32/include/SDL2")
    set(SDL2_MIXER_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../i686-w64-mingw32/lib/libSDL2_mixer.a")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SDL2_MIXER_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../x86_64-w64-mingw32/include/SDL2")
    set(SDL2_MIXER_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../x86_64-w64-mingw32/lib/libSDL2_mixer.a")
else("${CMAKE_SIZEOF_VOID_P}" STREQUAL "")
    set(SDL2_mixer_FOUND FALSE)
    return()
endif()
