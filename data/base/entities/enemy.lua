data.entities['data.base.entities.enemy'] = {

  onInteract = function()
    print("enemy - onInteractZ")

    local enemyBattle = Battle.new()
    local playerChar1 = BattleChar.new('playr1')
    local playerChar2 = BattleChar.new('playr2')
    local playerChar3 = BattleChar.new('playr3')
    local playerChar4 = BattleChar.new('playr4')
    
    local enemyChar1 = BattleChar.new('mon1')
    local enemyChar2 = BattleChar.new('mon2')

    enemyBattle:addPlayerChar(playerChar1)
    enemyBattle:addPlayerChar(playerChar2)
    enemyBattle:addPlayerChar(playerChar3)
    enemyBattle:addPlayerChar(playerChar4)
    
    enemyBattle:addEnemyChar(enemyChar1)
    enemyBattle:addEnemyChar(enemyChar2)
    
    battle.setCurrentBattle(enemyBattle)


  end

}
