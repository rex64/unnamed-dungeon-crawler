data.dungeons['data.base.dungeons.dungeon1'] = {
  
  onCreateFloor = function(floorNo)
  
    print("dungeon1 - onCreateFloor - FloorNo:" .. floorNo)

    t0 = "base.tiles.tile00"
    t1 = "base.tiles.tile01"

    a = {
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

    EntityType = {

      Player = 0,
      Enemy = 1,
      Other = 2,

    }

    for i,v in ipairs(a) do 
      if v == 0 then
        field.setTile(i-1, t1, v)
      else
        field.setTile(i-1, t0, v)
      end
    end

    --Player
    local playerID = field.addEntity(EntityType.Player, 'base.entities.player')
    field.setEntityTile(playerID, 1 + 16)

    local stairsID = field.addEntity(EntityType.Other, 'base.entities.stairs')
    field.setEntityTile(stairsID, 1 + 18)

    local enemyID = field.addEntity(EntityType.Enemy, 'base.entities.enemy')
    field.setEntityTile(enemyID, 1 + 24)
  end
  
}
