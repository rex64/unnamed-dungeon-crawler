data.dungeons[RESOURCE_ID] = {

  onCreateFloor = function(dungeonResId, floorNo)

    local Floor       = require('field.Floor')
    local FloorEntity = require('field.FloorEntity')

    local passableTiles  = "base.tiles.tile00"
    local collisionTiles   = "base.tiles.tile01"
    local fillTiles       = "base.tiles.tile02"

    local newFloor = Floor.new(dungeonResId, floorNo, 512, 512, fillTiles)
    newFloor.name = newFloor.dungeonId .. ' - floor: ' .. floorNo 

    print(newFloor.name .. " onCreateFloor")



    if floorNo ~= 2 then

      newFloor:addRoom(0, 0, 8, 8,  passableTiles, collisionTiles)
      newFloor:addRoom(8, 1, 6, 2,  passableTiles, collisionTiles)
      newFloor:addRoom(15, 0, 4, 4,  passableTiles, collisionTiles)


      newFloor:setTile(8, 2, passableTiles, 1)
      newFloor:setTile(14, 2, passableTiles, 1)
      newFloor:setTile(15, 2, passableTiles, 1)


      --Player
      local playerEntity = FloorEntity.new('base.entities.player', 'Player')
      newFloor:addEntity(playerEntity, newFloor:to1D(2,2))
      newFloor:setPlayerEntity(playerEntity)

      local stairsEntity = FloorEntity.new('base.entities.stairs', 'Stairs')
      stairsEntity:setValue('base.entities.stairs.floorId', dungeonResId)
      stairsEntity:setValue('base.entities.stairs.floorNo', floorNo + 1)
      newFloor:addEntity(stairsEntity, newFloor:to1D(17,2))

      local enemyEntity = FloorEntity.new('base.entities.enemy', 'Enemy')
      enemyEntity:setValue('base.encounterId', 'base.encounters.dungeon1_slime1')
      newFloor:addEntity(enemyEntity, newFloor:to1D(8,2))

      local chestEntity1 = FloorEntity.new('base.entities.chest', 'Chest1')
      chestEntity1:setValue('base.entities.chest.item', 'base.equips.nice-sword')
      newFloor:addEntity(chestEntity1, newFloor:to1D(2,4))
      
    else
      
      newFloor:addRoom(0, 0, 8, 8,  passableTiles, collisionTiles)

      --Player
      local playerEntity = FloorEntity.new('base.entities.player', 'Player')
      newFloor:addEntity(playerEntity, newFloor:to1D(2,2))
      newFloor:setPlayerEntity(playerEntity)
    end




    return newFloor

  end

}
