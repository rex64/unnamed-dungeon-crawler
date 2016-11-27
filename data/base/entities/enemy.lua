data.entities['data.base.entities.enemy'] = {

  onInteract = function()
    print("enemy - onInteractZ")

    local enemyBattle = Battle.new()
    local playerChar1 = BattleChar.new('player1')
    local playerChar2 = BattleChar.new('player2')
    local playerChar3 = BattleChar.new('player3')
    local playerChar4 = BattleChar.new('player4')
    local enemyChar1 = BattleChar.new('monster1')
    local enemyChar2 = BattleChar.new('monster1')

  



    enemyBattle:addChar(playerChar1)
    enemyBattle:addChar(playerChar2)
    enemyBattle:addChar(playerChar3)
    enemyBattle:addChar(playerChar4)
    enemyBattle:addChar(enemyChar1)
    enemyBattle:addChar(enemyChar2)
    
    battle.setCurrentBattle(enemyBattle)


  end

}
