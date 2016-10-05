cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (unnamed-dungeon-crawler)

set( project_sources
   src/main.cpp
)

add_executable(unnamed-dungeon-crawler ${project_sources})
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD 11)
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
