data.dungeons[RESOURCE_ID] = {

  onCreateFloor = function(dungeonResId, floorNo)

    print('onCreateFloor resID: ' .. dungeonResId)

    local Floor       = require('field.Floor')
    local FloorEntity = require('field.FloorEntity')

    local newFloor = Floor.new(dungeonResId, floorNo, 16, 9)
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
    newFloor:addEntity(playerEntity, newFloor:to1D(2,1))
    newFloor:setPlayerEntity(playerEntity)

    --Stairs
    local stairsEntity = FloorEntity.new('base.entities.stairs', 'Stairs')
    stairsEntity:setValue('base.entities.stairs.floorId', dungeonResId)
    stairsEntity:setValue('base.entities.stairs.floorNo', floorNo + 1)
    newFloor:addEntity(stairsEntity, newFloor:to1D(3,1))

    --Enemy
    local enemyEntity = FloorEntity.new('base.entities.enemy', 'Enemy')
    newFloor:addEntity(enemyEntity, newFloor:to1D(9,1))
    
    --chest1
    local chestEntity1 = FloorEntity.new('base.entities.chest', 'Chest1')
    chestEntity1:setValue('base.entities.chest.item', 'base.equips.nice-sword')
    newFloor:addEntity(chestEntity1, newFloor:to1D(6,5))
    
    return newFloor

  end

}
