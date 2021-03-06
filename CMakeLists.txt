cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (unnamed-dungeon-crawler)
set(CMAKE_BUILD_TYPE Debug)

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
   src/res/CharData.h
   src/res/DungeonData.h
   src/res/EnemyData.h
   src/res/EntityData.h
   src/res/EquipData.h
   src/res/FieldEntityData.h
   src/res/FontData.h
   src/res/HeroData.h
   src/res/SkillData.h
   src/res/Stats.h
   src/res/default_sprite.c
   src/Console.h
   src/Console.cpp
   src/RenderManager.h
   src/RenderManager.cpp
   src/IRenderable.h
   src/ui/UI.h
   src/ui/UI.cpp
   src/ui/MenuManager.h
   src/ui/MenuManager.cpp
   src/ui/lua_menu.h
   src/ui/lua_menu.cpp
   src/lua_save.h
   src/lua_save.cpp
   src/lua_data.h
   src/lua_data.cpp
   external/tinydir.h
   external/tinyxml2.h
   external/tinyxml2.cpp
   src/save/SaveManager.h
   src/save/SaveManager.cpp
)

add_executable(unnamed-dungeon-crawler ${project_sources})
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD 11)
set_property(TARGET unnamed-dungeon-crawler PROPERTY CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/)

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
