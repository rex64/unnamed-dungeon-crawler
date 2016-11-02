EntityType = {

	Player = 0,
	Enemy = 1,
	Other = 2,

}

enemy = {
  
  new = function() return {
    
      type = EntityType.Enemy,
      entityResID = "data.base.spritesheets.enemy"
    
    } 
    end
  
}

test1 = enemy.new()

print(test1.type)
print(test1.entityResID)
