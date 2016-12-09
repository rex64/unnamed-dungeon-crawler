data.entities['base.entities.enemy'] = {

  onInteract = function()
    print("enemy - onInteractZ")

    local newBattle = Battle.new()
    --local playerChar1 = BattleChar.new('playr1', 1)
    --local playerChar2 = BattleChar.new('playr2', 2)
    --local playerChar3 = BattleChar.new('playr3', 3)
    --local playerChar4 = BattleChar.new('playr4', 4)
    
    local enemyChar1 = BattleChar.new('mon1')
    local enemyChar2 = BattleChar.new('mon2')

    --enemyBattle:addPlayerChar(playerChar1)
    --enemyBattle:addPlayerChar(playerChar2)
    --enemyBattle:addPlayerChar(playerChar3)
    --enemyBattle:addPlayerChar(playerChar4)
    
    newBattle:addEnemyChar(enemyChar1)
    --enemyBattle:addEnemyChar(enemyChar2)
    
    battle.setCurrentBattle(newBattle)


  end

}
