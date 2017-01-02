data.enemies['base.enemies.slime'] = {

  onTurn = function(battle, enemy, playerParty)
    --print(enemy.name .. " - onTurn - slime looks confused")
    local randoTarget = battle:getRandomPlayer()
    --randoTarget.hp = randoTarget.hp - 5
    --print(enemy.name .. ' attacks ' .. randoTarget.name .. ' ' .. randoTarget.hp .. '/' .. randoTarget.maxHp )

    return data.skills['base.skills.attack'].onSelect(enemy, randoTarget)

--    return {   
--      target = randoTarget,
--      dialogText = enemy.name .. ' attacks ' .. randoTarget.name .. ' ' .. randoTarget.hp .. '/' .. randoTarget.maxHp    
--    }

  end

}
