local Window       = require('ui.Window')
local ChoiceMenu   = require('ui.ChoiceMenu')

--//////////////////////////////////////////////////////////////////////
--************************
--EquipWindow
--************************

EquipWindow = {}
EquipWindow.__index = EquipWindow
setmetatable(EquipWindow, {__index = Window})

function EquipWindow.new(x, y, w, h)

  local self = Window.new(x, y, w, h, false)
  self = setmetatable(self, EquipWindow)

  self.name = 'EquipWindow'

  self.currHeroIndex = 1
  self:setHero(self.currHeroIndex)

  return self
end

function EquipWindow:onInput(input)


  if input.right == true and self.pickerChoiceMenu == nil then

    self.currHeroIndex = self.currHeroIndex + 1

    if self.currHeroIndex > 4 then self.currHeroIndex = 1 end

    self:setHero(self.currHeroIndex)

  elseif input.left == true and self.pickerChoiceMenu == nil then

    self.currHeroIndex = self.currHeroIndex - 1

    if self.currHeroIndex < 1 then self.currHeroIndex = 4 end

    self:setHero(self.currHeroIndex)

  else

    if self.pickerChoiceMenu ~= nil then
      self.pickerChoiceMenu:onInput(input)
    else
      self.equipsChoiceMenu:onInput(input)
    end

  end


end

function EquipWindow:render()

  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  --HERO NAME & LEVEL
  engine.renderTextLine('Name',         x,      y)
  engine.renderTextLine(self.heroName,  x+8*6,  y)

  self.equipsChoiceMenu:render(x, y+8*2)

  if self.pickerChoiceMenu ~= nil then
    self.pickerChoiceMenu:render(x+8*20, y+8*2)
  end


--[[
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
  engine.renderTextLine('Skills', x+8*12,  y+8*10)

  for i, skillName in ipairs(self.heroSkills) do


    engine.renderTextLine(skillName, x+8*12,  y+8*(11+i))

  end
]]--

end

function EquipWindow:setHero(heroIndex)

  self.pickerChoiceMenu = nil

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
  --self.heroCurrentExp = tostring(partyMemberCurrentTotalExp)
  --self.heroExpToNextLevel = tostring(expToNextLevel)

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

  self.equipsChoiceMenu = ChoiceMenu.new()
  self.equipsChoiceMenu:addMenuItem(MenuItem.new('Weapon ' .. self.heroEquips.weapon, function() 

        self.pickerChoiceMenu = ChoiceMenu.new()

        for i, weaponId in ipairs(save.getInventoryWeapons()) do

          local weaponName = save.getEquipName(weaponId)
          self.pickerChoiceMenu:addMenuItem(MenuItem.new(weaponName, function() 
                save.swapEquip(partyMemberId, weaponId) 
                self:setHero(self.currHeroIndex)
              end))

        end




      end))
  self.equipsChoiceMenu:addMenuItem(MenuItem.new('Head ' .. self.heroEquips.head, function() end))
  self.equipsChoiceMenu:addMenuItem(MenuItem.new('Body ' .. self.heroEquips.body, function() end))
  self.equipsChoiceMenu:addMenuItem(MenuItem.new('Accessory ' .. self.heroEquips.accessory, function() end))



  --SKILLS
  --[[
  local heroSkills = save.getHeroSkills(partyMemberId)
  self.heroSkills = {}
  for i, skillId in ipairs(heroSkills) do
    table.insert(self.heroSkills, save.getSkillName(skillId)  )
  end 
  ]]--
end

return EquipWindow
