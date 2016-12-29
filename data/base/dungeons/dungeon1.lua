data.dungeons[RESOURCE_ID] = {

  onCreateFloor = function(dungeonResId, floorNo)

    local Floor       = require('field.Floor')
    local FloorEntity = require('field.FloorEntity')

    local passableTiles  = "base.tiles.tile00"
    local collisionTiles   = "base.tiles.tile01"
    local fillTiles       = "base.tiles.tile02"

    local newFloor = Floor.new(dungeonResId, 64, 64, fillTiles)
    newFloor.name = newFloor.dungeonId .. ' - floor: ' .. floorNo 

    print(newFloor.name .. " onCreateFloor")

    newFloor:addRoom(0, 0, 16, 16,  passableTiles, collisionTiles)
    newFloor:addRoom(16, 6, 8, 2,  passableTiles, collisionTiles)
    newFloor:addRoom(24, 4, 4, 4,  passableTiles, collisionTiles)


    newFloor:setTile(16, 7, passableTiles, 1)
    newFloor:setTile(24, 7, passableTiles, 1)

    --Player
    local playerEntity = FloorEntity.new('base.entities.player', 'Player')
    newFloor:addEntity(playerEntity, newFloor:to1D(1,1))
    newFloor:setPlayerEntity(playerEntity)

    local stairsEntity = FloorEntity.new('base.entities.stairs', 'Stairs')
    newFloor:addEntity(stairsEntity, newFloor:to1D(26,6))

    return newFloor

  end

}
