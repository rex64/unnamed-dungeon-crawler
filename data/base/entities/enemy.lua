data.entities[RESOURCE_ID] = {

  onInteract = function(entity, player)

    print("enemy - onInteractZ")

    local Battle     = require('battle.Battle')
    local BattleChar = require('battle.BattleChar')

    local newBattle = Battle.new()

    newBattle:addEnemyChar(BattleChar.newEnemyFromId('base.enemies.slime'))
    newBattle:addEnemyChar(BattleChar.newEnemyFromId('base.enemies.slime'))
    newBattle:addEnemyChar(BattleChar.newEnemyFromId('base.enemies.slime'))
    
    newBattle.onBattleWon = function() 

      field.currentFloor:removeEntity(entity)

    end

    battle.setCurrentBattle(newBattle)


  end

}
