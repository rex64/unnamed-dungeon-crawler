
--//////////////////////////////////////////////////////////////////////
--************************
--BattleChar
--************************
BattleChar = {}
BattleChar.__index = BattleChar

function BattleChar.new(name)
  local newBattleChar = {}
  setmetatable(newBattleChar, BattleChar)

  newBattleChar.id      = nil
  newBattleChar.name    = name
  newBattleChar.level   = 1
  newBattleChar.hp      = 1
  newBattleChar.maxHp   = 1
  newBattleChar.mp      = 1
  newBattleChar.maxMp   = 1
  newBattleChar.mp      = 1
  newBattleChar.atk     = 1
  newBattleChar.def     = 1
  newBattleChar.matk    = 1
  newBattleChar.mdef    = 1
  newBattleChar.mnd     = 1
  newBattleChar.spd     = 1
  newBattleChar.lck     = 1

  newBattleChar.userData = {}

  return newBattleChar
end

function BattleChar.newHeroFromId(id)

  local battleCharData = save.getPartyMemberStats(id)
  local newBattleChar = BattleChar.new()

  newBattleChar.id      = id
  newBattleChar.name    = battleCharData.name
  newBattleChar.level   = battleCharData.level
  newBattleChar.hp      = battleCharData.hp
  newBattleChar.maxHp   = battleCharData.hp
  newBattleChar.mp      = battleCharData.mp
  newBattleChar.maxMp   = battleCharData.mp
  newBattleChar.atk     = battleCharData.atk
  newBattleChar.def     = battleCharData.def
  newBattleChar.matk    = battleCharData.matk
  newBattleChar.mdef    = battleCharData.mdef
  newBattleChar.mnd     = battleCharData.mnd
  newBattleChar.spd     = battleCharData.spd
  newBattleChar.lck     = battleCharData.lck

  return newBattleChar
end

function BattleChar.newEnemyFromId(id)

  local battleCharData = data.getEnemyData(id)
  local newBattleChar = BattleChar.new()

  newBattleChar.id      = id
  newBattleChar.name    = battleCharData.name
  newBattleChar.level   = battleCharData.level
  newBattleChar.hp      = battleCharData.hp
  newBattleChar.maxHp   = battleCharData.hp
  newBattleChar.atk     = battleCharData.atk
  newBattleChar.def     = battleCharData.def
  newBattleChar.matk    = battleCharData.matk
  newBattleChar.mdef    = battleCharData.mdef
  newBattleChar.mnd     = battleCharData.mnd
  newBattleChar.spd     = battleCharData.spd
  newBattleChar.lck     = battleCharData.lck

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