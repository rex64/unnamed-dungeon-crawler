data.entities['data.base.entities.enemy'] = {

  onInteract = function()
    print("enemy - onInteract")

    local enemyBattle = Battle.new()
    local playerChar1 = BattleChar.new()
    local playerChar2 = BattleChar.new()
    local playerChar3 = BattleChar.new()
    local playerChar4 = BattleChar.new()
    local enemyChar1 = BattleChar.new()
    local enemyChar2 = BattleChar.new()

  



    enemyBattle:addChar(playerChar1)
    enemyBattle:addChar(playerChar2)
    enemyBattle:addChar(playerChar3)
    enemyBattle:addChar(playerChar4)
    enemyBattle:addChar(enemyChar1)
    enemyBattle:addChar(enemyChar2)
    
    battle.setCurrentBattle(enemyBattle)


  end

}
