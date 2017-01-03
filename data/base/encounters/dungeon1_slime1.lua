data.encounters[RESOURCE_ID] = {

  onEncounter = function()

    local Battle     = require('battle.Battle')
    local BattleChar = require('battle.BattleChar')

    local newBattle = Battle.new()

    newBattle:addEnemyChar(BattleChar.newEnemyFromId('base.enemies.slime'))
    
    return newBattle

  end

}
