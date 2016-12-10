--************************
--Battle
--************************
Battle = {}
Battle.__index = Battle

function Battle.new()
  local newBattle = {}
  setmetatable(newBattle, Battle)

  newBattle.commandWindow = nil
  newBattle.battleChars = {}
  newBattle.playerChars = {}
  newBattle.enemyChars  = {}

  newBattle.nextTurnChar = 1

  newBattle.timelineWin1 = Window.new(8, 8, 8, 4, false)  
  local newDialog1 = Dialog.new('1')
  newBattle.timelineWin1:addDialog(newDialog1)
  newBattle.timelineWin1:setDismissable(false)
  ui.addWindow(newBattle.timelineWin1)

  newBattle.timelineWin2 = Window.new(320, 8, 8, 4, false)
  local newDialog2 = Dialog.new('2')
  newBattle.timelineWin2:addDialog(newDialog2)
  newBattle.timelineWin2:setDismissable(false)
  ui.addWindow(newBattle.timelineWin2)

  newBattle.timelineWin3 = Window.new(8, 100, 8, 4, false)
  local newDialog3 = Dialog.new('3')
  newBattle.timelineWin3:addDialog(newDialog3)
  newBattle.timelineWin3:setDismissable(false)
  ui.addWindow(newBattle.timelineWin3)

  newBattle.timelineWin4 = Window.new(320, 100, 8, 4, false)
  local newDialog4 = Dialog.new('4')
  newBattle.timelineWin4:addDialog(newDialog4)
  newBattle.timelineWin4:setDismissable(false)
  ui.addWindow(newBattle.timelineWin4)

  return newBattle
end

function Battle:addPlayerChar(battleChar)

  table.insert(self.playerChars, battleChar)
  self:addChar(battleChar)
end

function Battle:addEnemyChar(battleChar)

  table.insert(self.enemyChars, battleChar)
  self:addChar(battleChar)
end

function Battle:addChar(battleChar)

  table.insert(self.battleChars, battleChar)
end

function Battle:init()

  self.windows = {
    self.timelineWin1,
    self.timelineWin2,
    self.timelineWin3,
    self.timelineWin4
  }
  
  --dedup enemy names
  
  --get Heroes info
  local partySize = save.getCurrentPartySize()
  for i = 1, partySize do
    local partyMemberName = save.getPartyMemberName(i)
    local playerChar = BattleChar.new(partyMemberName, i)
    self:addPlayerChar(playerChar)

    self.windows[i].dialog.text = self.playerChars[i].name
  end  

  --command window
  self.commandWindow = Window.new(34, 160, 36, 4, false)
  local newDialog1 = Dialog.new('0')
  self.commandWindow:addDialog(newDialog1)
  ui.addWindow(self.commandWindow)

  --calc speed

  --set new turn
  self.nextTurnChar = 0
  self:newTurn()

end

function Battle:endBattle()

  battle.endCurrentBattle()
end

function Battle:newTurn()
  self.nextTurnChar = self.nextTurnChar + 1 
  if self.nextTurnChar > #self.battleChars then
    self.nextTurnChar = 1
  end

  local turnChar = self:getTurnChar(0)

  if self:isPlayer(turnChar) then
    self:onPlayerTurn(turnChar)
  end

-- se enemy attack
  if self:isEnemy(turnChar) then
    -- print(turnChar.name .. ' attacks ' .. self:getRandomPlayer().name)

    data.enemies[turnChar.id].onTurn(self, turnChar, self.playerChars)

    self:newTurn()

  end

  if self:youWin() then
    self:endBattle()
  end

end

function Battle:onPlayerTurn(turnChar)
  
  --local turnChar = self:getTurnChar(0)

  if self:isPlayer(turnChar) then

    local heroSkills = save.getHeroSkills(turnChar.index)

    self.commandWindow:resetMenu()
    for i,v in ipairs(heroSkills) do

      local skillName = save.getSkillName(v)
      local skillMenuItem = MenuItem.new(skillName, 

        function() 

          --if singleTarget
          local singleTargetWin = Window.new(160, 30, 6, 4, false)

          for h, target in ipairs(self.enemyChars) do

            local skillMenuItem2 = MenuItem.new(target.name, 

              function() 
                data.skills[v].onSelect(turnChar, target)
                singleTargetWin:dismiss()
                self:newTurn()
              end

            )
            singleTargetWin:addMenuItem(skillMenuItem2)
          end
          ui.addWindow(singleTargetWin)
        end

      )
      self.commandWindow:addMenuItem(skillMenuItem)
    end
  end

end

function Battle:getTurnChar(turnNo)

  local index = self.nextTurnChar + turnNo

  if index > #self.battleChars then
    index = turnNo
  end


  return self.battleChars[index]
end

function Battle:getRandomPlayer()
  local rando = math.random(#self.playerChars)
  return self.playerChars[rando]
end

function Battle:getRandomEnemy()
  local rando = math.random(#self.enemyChars)
  return self.enemyChars[rando]
end

function Battle:isPlayer(char)

  for i, e in ipairs(self.playerChars) do

    if (char == e) then return true end

  end

  return false

end

function Battle:isEnemy(char)

  for i, e in ipairs(self.enemyChars) do

    if (char == e) then return true end

  end

  return false

end

function Battle:youWin()

  for i, enemy in ipairs(self.enemyChars) do

    if (enemy.hp > 0) then return false end
  end
  return true

end

function Battle:update()
--  print('curr battle update')

--TEMP
--[[
  local clock = os.clock
  function sleep(n)  -- seconds
    local t0 = clock()
    while clock() - t0 <= n do end
  end
  sleep(0.5)
]]--

-- get turn char
-- local turnChar = self:getTurnChar(0)

end

function Battle:render()
  ui.renderSprite('base.spritesheets.testbackground', 72, 40) 
  ui.renderSprite('base.spritesheets.enemy_battle_sprite', math.floor(400/2) - 25, math.floor(225/2) - 25)

end


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
  newBattleChar.index = i
  newBattleChar.hp = 100
  newBattleChar.strength = 100
  newBattleChar.speed = 100
  newBattleChar.vitality = 100
  newBattleChar.intelligence = 100
  newBattleChar.mind = 100

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

if battle ~= nil then

  battle.currentBattle = nil

  battle.onInput = function (button)

    if battle.weBattle() then battle.currentBattle:onInput(button) end
  end

  battle.update = function() 

    if battle.weBattle() then battle.currentBattle:update() end
  end

  battle.render = function() 

    if battle.weBattle() then battle.currentBattle:render()    end
  end

  battle.weBattle = function() 

    if battle.currentBattle ~= nil then return true end
    return false
  end

  battle.setCurrentBattle = function(newBattle) 

    battle.currentBattle = newBattle
    battle.currentBattle:init()

  end

  battle.endCurrentBattle = function() 

    ui.windows = {}

    battle.currentBattle = nil

  end

end
