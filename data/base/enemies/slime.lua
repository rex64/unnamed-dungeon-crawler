data.enemies['base.enemies.slime'] = {

  onTurn = function(battle, enemy, playerParty)
    --print(enemy.name .. " - onTurn - slime looks confused")
    local randoTarget = battle:getRandomPlayer()
    randoTarget.hp = randoTarget.hp - 5
    print(enemy.name .. ' attacks ' .. randoTarget.name .. ' ' .. randoTarget.hp .. '/' .. randoTarget.maxHp )


  end

}
