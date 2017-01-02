data.entities[RESOURCE_ID] = {

  onInteract = function(entity, player)

    print("enemy - onInteractZ")

    local Battle     = require('battle.Battle')
    local BattleChar = require('battle.BattleChar')

    local newBattle = Battle.new()

    local enemyChar1 = BattleChar.newFromId('base.enemies.slime')
    local enemyChar2 = BattleChar.newFromId('base.enemies.slime')

    newBattle:addEnemyChar(enemyChar1)
    newBattle:addEnemyChar(enemyChar2)
    newBattle:addEnemyChar(BattleChar.newFromId('base.enemies.slime'))
    
    newBattle.onBattleWon = function() 

      field.currentFloor:removeEntity(entity)

    end

    battle.setCurrentBattle(newBattle)


  end

}
