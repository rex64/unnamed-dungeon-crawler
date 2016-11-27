--************************
--Battle
--************************
Battle = {}
Battle.__index = Battle

function Battle.new()
  local newBattle = {}
  setmetatable(newBattle, Battle)

  newBattle.battleChars = {}
  newBattle.nextTurnChar = 1

  return newBattle
end

function Battle:addChar(battleChar)

  table.insert(self.battleChars, battleChar)
end

function Battle:endTurn()
  self.nextTurnChar = self.nextTurnChar + 1 
  if self.nextTurnChar > #newBattle.battleChars then
    self.nextTurnChar = 1
  end

end

function Battle:update()
end

function Battle:render()
end


--************************
--BattleChar
--************************
BattleChar = {}
BattleChar.__index = BattleChar

function BattleChar.new()
  local newBattleChar = {}
  setmetatable(newBattleChar, BattleChar)

  newBattleChar.hp = 100

  return newBattleChar
end

if battle ~= nil then

  battle.currentBattle = nil

  battle.update = function() 

    if battle.weBattle() then battle.currentBattle:update()

    end
  end
  battle.render = function() 

    if battle.weBattle() then battle.currentBattle:render()

    end

    battle.weBattle = function() 

      if currentBattle ~= nil then return true end
      return false
    end

    battle.setCurrentBattle = function(newBattle) 

      battle.currentBattle = newBattle

    end

  end
end
