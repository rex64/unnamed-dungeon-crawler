local Window = require('ui.Window')

--//////////////////////////////////////////////////////////////////////
--************************
--StatusWindow
--************************

StatusWindow = {}
StatusWindow.__index = StatusWindow
setmetatable(StatusWindow, {__index = Window})

function StatusWindow.new(x, y, w, h)

  local self = Window.new(x, y, w, h, false)
  self = setmetatable(self, StatusWindow)

  self.name = 'StatusWindow'
  
  --[[
  --HERO NAME & LEVEL
  self.heroName = '-1'
  self.heroLevel = '-1'
  
  --HERO STATS
  self.heroHp = '-1'
  self.heroMp = '-1'
  self.heroAtk = '-1'
  self.heroDef = '-1'
  self.heroMatk = '-1'
  self.heroMdef = '-1'
  self.heroMnd = '-1'
  self.heroSpd = '-1'
  self.heroLck = '-1'
  
  --HERO SKILLS
  self.heroEquips = {
    weapon    = '-1',
    head      = '-1',
    body      = '-1',
    accessory = '-1',
  }
  ]]--
  self.heroSkills = {}
  
  self.currHeroIndex = 1
  self:setHero(self.currHeroIndex)
  
  return self
end

function StatusWindow:onInput(input)

--[[
  if input.ok == true then
    self:dismiss()
  end
  ]]--
end

function StatusWindow:render()
  
  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  --HERO NAME & LEVEL
  engine.renderTextLine('Name',         x,      y)
  engine.renderTextLine(self.heroName,  x+8*6,  y)
  
  --HERO LEVEL
  engine.renderTextLine('Level',         x,      y+8*2)
  engine.renderTextLine(self.heroLevel,  x+8*6,  y+8*2)
  
  --HERO STATS
  --self.heroHp = ''
  engine.renderTextLine('Hp',            x,       y+8*4)
  engine.renderTextLine(self.heroHp,     x+8*6,   y+8*4)
  
  --self.heroMp = ''
  engine.renderTextLine('Mp',            x,       y+8*5)
  engine.renderTextLine(self.heroMp,     x+8*6,   y+8*5)
  
  --self.heroAtk = ''
  engine.renderTextLine('Atk',            x,       y+8*6)
  engine.renderTextLine(self.heroAtk,     x+8*6,   y+8*6)
  
  --self.heroDef = ''
  engine.renderTextLine('Def',            x,       y+8*7)
  engine.renderTextLine(self.heroDef,     x+8*6,   y+8*7)
  
  --self.heroMatk = ''
  engine.renderTextLine('M.Atk',            x,       y+8*8)
  engine.renderTextLine(self.heroMatk,     x+8*6,   y+8*8)
  
  --self.heroMdef = ''
  engine.renderTextLine('M.Def',            x,       y+8*9)
  engine.renderTextLine(self.heroMdef,     x+8*6,   y+8*9)
  
  --self.heroMnd = ''
  engine.renderTextLine('Mnd',            x,       y+8*10)
  engine.renderTextLine(self.heroMnd,     x+8*6,   y+8*10)
  
  --self.heroSpd = ''
  engine.renderTextLine('Spd',            x,       y+8*11)
  engine.renderTextLine(self.heroSpd,     x+8*6,   y+8*11)
  
  --self.heroLck = ''
  engine.renderTextLine('Lck',            x,       y+8*12)
  engine.renderTextLine(self.heroLck,     x+8*6,   y+8*12)
  
  --Total EXP
  engine.renderTextLine('Total EXP',              x,       y+8*15)
  engine.renderTextLine(self.heroCurrentExp,     x+8*6,   y+8*16)
  
  --To Next Level EXP
  engine.renderTextLine('To Next Level',         x,       y+8*18)
  engine.renderTextLine(self.heroExpToNextLevel,     x+8*6,   y+8*19)
  
  --HERO EQUIPS
  --HERO LEVEL
  engine.renderTextLine('Equip',  x+8*12,     y+8*2)
  
  engine.renderTextLine('Weapon', x+8*12,     y+8*4)  
  engine.renderTextLine(self.heroEquips.weapon, x+8*20,     y+8*4)
  
  engine.renderTextLine('Head', x+8*12,       y+8*5)
  engine.renderTextLine(self.heroEquips.head, x+8*20,     y+8*5)
  
  engine.renderTextLine('Body', x+8*12,       y+8*6)
  engine.renderTextLine(self.heroEquips.body, x+8*20,     y+8*6)
  
  engine.renderTextLine('Accessory', x+8*12,  y+8*7)
  engine.renderTextLine(self.heroEquips.accessory, x+8*20,     y+8*7)

  --HERO SKILLS
  --self.heroSkills = {}

end

function StatusWindow:setHero(heroIndex)

    local partyMemberId     = save.getPartyMemberId(heroIndex)
    local partyMemberName   = save.getPartyMemberName(partyMemberId)
    

    local partyMemberStats              = save.getPartyMemberStats(partyMemberId)
    local partyMemberCurrentTotalExp    = save.partyMemberCurrentTotalExp(partyMemberId)
    local expToNextLevel                = engine.getExpToLevel(partyMemberStats.level+1) - partyMemberCurrentTotalExp;
    
    local partyMemberEquip  = save.getPartyMemberEquip(partyMemberId)

    --NAME
    self.heroName   = partyMemberName
    
    --LEVEL
    self.heroLevel  = tostring(partyMemberStats.level)
  
    --EXP
    self.heroCurrentExp = tostring(partyMemberCurrentTotalExp)
    self.heroExpToNextLevel = tostring(expToNextLevel)
  
    --STATS
    self.heroHp   = tostring(partyMemberStats.hp)
    self.heroMp   = tostring(partyMemberStats.mp)
    self.heroAtk  = tostring(partyMemberStats.atk)
    self.heroDef  = tostring(partyMemberStats.def)
    self.heroMatk = tostring(partyMemberStats.matk)
    self.heroMdef = tostring(partyMemberStats.mdef)
    self.heroMnd  = tostring(partyMemberStats.mnd)
    self.heroSpd  = tostring(partyMemberStats.spd)
    self.heroLck  = tostring(partyMemberStats.lck)
    
    --HERO EQUIPS
    self.heroEquips = {
      weapon    = tostring(partyMemberEquip.weapon),
      head      = tostring(partyMemberEquip.head),
      body      = tostring(partyMemberEquip.body),
      accessory = tostring(partyMemberEquip.accessory),
    }
    
end

return StatusWindow
