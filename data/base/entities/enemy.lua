data.entities['base.entities.enemy'] = {

  onInteract = function(entity, player)
    
    print("enemy - onInteractZ")
    
    local Battle     = require('battle.Battle')
    local BattleChar = require('battle.BattleChar')


    local newBattle = Battle.new()
    
    local enemyChar1 = BattleChar.newFromId('base.enemies.slime')
    local enemyChar2 = BattleChar.newFromId('base.enemies.slime')
    
    newBattle:addEnemyChar(enemyChar1)
    newBattle:addEnemyChar(enemyChar2)
    
    battle.setCurrentBattle(newBattle)


  end

}
