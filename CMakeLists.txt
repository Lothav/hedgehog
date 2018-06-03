cmake_minimum_required(VERSION 2.8.4)
project(hedgehog)

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
        src/renderer/BulkObject2D.cpp src/renderer/BulkObject2D.hpp)

include_directories(/usr/include/freetype2)

target_link_libraries(launcher SDL2 SDL2_image GL GLEW freetype)