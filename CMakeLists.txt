cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (unnamed-dungeon-crawler)

set( project_sources
   src/main.cpp
   src/Game.h
   src/Game.cpp
   src/ScriptManager.h
   src/ScriptManager.cpp
   src/stage/StageManager.h
   src/stage/StageManager.cpp
   src/stage/Stage.h
   src/stage/Stage.cpp
   src/res/ResourceManager.h
   src/res/ResourceManager.cpp
)

add_executable(unnamed-dungeon-crawler ${project_sources})
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD 11)
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD_REQUIRED ON)

if (APPLE)
	message("OSX")
	
	#SDL
	FIND_LIBRARY(SDL2_FRAMEWORK SDL2)
	message(${SDL2_FRAMEWORK})
	target_link_libraries(unnamed-dungeon-crawler ${SDL2_FRAMEWORK})

	#LUA
	FIND_LIBRARY(LUA_FRAMEWORK lua $ENV{OPENSSL_LIB_PATH})
	message(${LUA_FRAMEWORK})
	include_directories(/usr/local/include/)
	target_link_libraries(unnamed-dungeon-crawler ${LUA_FRAMEWORK})


elseif(WIN32)
	
	message("WIN")
	
	#SDL
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include)
	target_link_libraries(unnamed-dungeon-crawler ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2.lib)

	#LUA
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lua/include)
	target_link_libraries(unnamed-dungeon-crawler ${CMAKE_CURRENT_SOURCE_DIR}/lua/lua53.lib)

endif()
