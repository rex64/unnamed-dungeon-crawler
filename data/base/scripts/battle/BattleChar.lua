
--//////////////////////////////////////////////////////////////////////
--************************
--BattleChar
--************************
BattleChar = {}
BattleChar.__index = BattleChar

function BattleChar.new(name, i)
  local newBattleChar = {}
  setmetatable(newBattleChar, BattleChar)

  newBattleChar.id = nil
  newBattleChar.name = name
  newBattleChar.hp = 100
  newBattleChar.maxHp = 100
  newBattleChar.mp = 100
  newBattleChar.maxMp = 100
  newBattleChar.index = i
  newBattleChar.strength = 100
  newBattleChar.speed = 100
  newBattleChar.vitality = 100
  newBattleChar.intelligence = 100
  newBattleChar.mind = 100

  newBattleChar.userData = {}

  return newBattleChar
end

function BattleChar.newFromId(id)

  local battleCharData = data.getEnemyData(id)
  local newBattleChar = BattleChar.new()

  newBattleChar.id            = id
  newBattleChar.name          = battleCharData.name
  newBattleChar.hp            = battleCharData.hp
  newBattleChar.maxHp         = battleCharData.hp
  newBattleChar.strength      = battleCharData.strength
  newBattleChar.speed         = battleCharData.speed
  newBattleChar.vitality      = battleCharData.vitality
  newBattleChar.intelligence  = battleCharData.intelligence
  newBattleChar.mind          = battleCharData.mind

  return newBattleChar
end

function BattleChar:removeHp(value)
  self.hp = math.max(0, self.hp - value)
end

function BattleChar:addHp(value)
  self.hp = math.min(self.maxHp, self.hp + value)
end

function BattleChar:isDead()
  if self.hp < 1 then return true end
end

return BattleChar