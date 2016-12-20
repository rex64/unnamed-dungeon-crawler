package.path = package.path 
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?.lua"
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?/?.lua"

.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\lualibs\\?.lua"
.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\lualibs\\?\\?.lua"

package.cpath = package.cpath 
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/?.dylib"
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/socket/?.dylib"

.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\bin\\clibs53\\?.dll"
.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\bin\\clibs53\\socket\\?.dll"

require('mobdebug').start()

--local omar = debug.getinfo(1,"S").source
--debugger.verbose=true
--print (omar)

dofile('data/base/scripts/game.lua');
dofile('data/base/scripts/field.lua');
dofile('data/base/scripts/ui.lua');
dofile('data/base/scripts/battle.lua');

local ChangeFloorEvent = require('field.events.ChangeFloorEvent')
print("main");

print('main - ok');

game.eventManager:addEvent(ChangeFloorEvent.new('base.dungeons.dungeon1', 1))
