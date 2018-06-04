cmake_minimum_required(VERSION 2.8.4)
project(hedgehog)

set(TINYXML2_INCLUDE_DIR vendor/lib/tinyxml2)
set(TINYXML2_LIBRARIES tinyxml2)

include_directories(/usr/include/freetype2)
include_directories(vendor/include/tmxparser/src)
include_directories(vendor/lib/tinyxml2)

add_subdirectory(vendor/lib/tinyxml2 ../vendor/lib/tinyxml2)
add_subdirectory(vendor/include/tmxparser ../vendor/include/tmxparser/src)

find_path(TMXPARSER_INCLUDE_DIR NAMES ../vendor/include/tmxparser/src/Tmx.h
        DOC "The tmxparser include directory"
)

find_library(TMXPARSER_LIBRARY NAMES tmxparser
        DOC "The tmxparser library"
)

if(TMXPARSER_LIBRARY)
    set(TMXPARSER_FOUND TRUE)
else()
    set(TMXPARSER_FOUND FALSE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TMXPARSER DEFAULT_MSG TMXPARSER_LIBRARY TMXPARSER_INCLUDE_DIR)

mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARY)

add_executable(
        launcher

        src/main.cpp

        src/memory/Allocator.hpp
        src/memory/Provider.cpp
        src/memory/Provider.hpp
        src/memory/Pool.cpp
        src/memory/Pool.hpp

        src/renderer/Shader.cpp
        src/renderer/Shader.hpp
        src/renderer/Window.hpp
        src/renderer/Window.cpp
        src/renderer/Text.cpp
        src/renderer/Text.hpp
        src/renderer/BulkText.cpp
        src/renderer/BulkText.hpp
        src/renderer/Object2D.cpp
        src/renderer/Object2D.hpp
        src/renderer/BulkObject2D.cpp
        src/renderer/BulkObject2D.hpp
        src/renderer/Map.cpp src/renderer/Map.hpp)

target_link_libraries(launcher SDL2 SDL2_image GL GLEW freetype tmxparser)