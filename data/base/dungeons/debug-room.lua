data.dungeons[RESOURCE_ID] = {

  onCreateFloor = function(dungeonResId, floorNo)

    print('onCreateFloor resID: ' .. dungeonResId)

    local Floor       = require('field.Floor')
    local FloorEntity = require('field.FloorEntity')

    local newFloor = Floor.new(dungeonResId, 16, 9)
    newFloor.name = newFloor.dungeonId .. ' - floor: ' .. floorNo 

    print(newFloor.name .. " onCreateFloor")

    t0 = "base.tiles.tile00"
    t1 = "base.tiles.tile01"

    newFloor.tileCollisions = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    }

    newFloor.tileSets = {
      t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1,
      t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t0, t1, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t0, t1, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t0, t1, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t1, t1, t1, t0, t0, t0, t0, t0, t0, t1,
      t1, t0, t0, t0, t0, t0, t0, t1, t0, t0, t0, t0, t0, t0, t0, t1,
      t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1,
    }

    --Player
    local playerEntity = FloorEntity.new('base.entities.player', 'Player')
    newFloor:addEntity(playerEntity, 1 + 16)
    newFloor:setPlayerEntity(playerEntity)

    local stairsEntity = FloorEntity.new('base.entities.stairs', 'Stairs')
    newFloor:addEntity(stairsEntity, 1 + 18)

    local enemyEntity = FloorEntity.new('base.entities.enemy', 'Enemy')
    newFloor:addEntity(enemyEntity, 1 + 24)
    
    return newFloor

  end

}
