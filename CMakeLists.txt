cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (unnamed-dungeon-crawler)

set( project_sources
   src/main.cpp
)

add_executable(unnamed-dungeon-crawler ${project_sources})
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD 11)
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD_REQUIRED ON)

if (APPLE)
	message("OSX")
elseif(WIN32)
	message("WIN")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include)
	target_link_libraries(unnamed-dungeon-crawler ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2.lib)
endif()
