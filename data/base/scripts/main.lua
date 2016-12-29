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

--game.eventManager:addEvent(ChangeFloorEvent.new('base.dungeons.debug-room', 1):debug('main.lua 31'))
game.eventManager:addEvent(ChangeFloorEvent.new('base.dungeons.dungeon1', 1):debug('main.lua 32'))

save.addHero('base.heroes.tank',   1)
save.heroEquip('base.heroes.tank',   'base.equips.sword')
save.heroEquip('base.heroes.tank',   'base.equips.subligaria-of-tanking')

save.addHero('base.heroes.heals',  2)
save.heroEquip('base.heroes.heals',  'base.equips.staff')

save.addHero('base.heroes.melee',  3)
save.heroEquip('base.heroes.melee',  'base.equips.knife')

save.addHero('base.heroes.ranged', 4)
save.heroEquip('base.heroes.ranged', 'base.equips.bow')

save.addEquipToInventory('base.equips.junk-sword-of-testing1')
save.addEquipToInventory('base.equips.junk-sword-of-testing2')
save.addEquipToInventory('base.equips.junk-sword-of-testing2')
save.addEquipToInventory('base.equips.junk-sword-of-testing3')
save.addEquipToInventory('base.equips.junk-sword-of-testing4')
save.addEquipToInventory('base.equips.nice-sword')

local omar = save.getInventoryWeapons()
print(omar)
