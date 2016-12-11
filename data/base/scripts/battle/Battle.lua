local BattleConsts    = require('battle.BattleConsts')
local Dialog          = require('ui.Dialog')
local MenuItem        = require('ui.MenuItem')

--************************
--Battle
--************************
Battle = {}
Battle.__index = Battle

function Battle.new()
  local newBattle = {}
  setmetatable(newBattle, Battle)

  newBattle.eventManager = EventManager.new()

  newBattle.commandWindow = nil
  newBattle.battleChars = {}
  newBattle.playerChars = {}
  newBattle.enemyChars  = {}

  newBattle.nextTurnChar = 1

  newBattle.timelineWin1 = Window.new(
    BattleConsts.win1.startX, 
    BattleConsts.win1.startY, 
    BattleConsts.win1.w, 
    BattleConsts.win1.h, 
    false)  
  local newDialog1 = Dialog.new('1')
  newBattle.timelineWin1:addDialog(newDialog1)
  newBattle.timelineWin1:setDismissable(false)
  ui.addWindow(newBattle.timelineWin1)

  newBattle.timelineWin2 = Window.new(
    BattleConsts.win2.startX, 
    BattleConsts.win2.startY, 
    BattleConsts.win2.w, 
    BattleConsts.win2.h, 
    false) 
  local newDialog2 = Dialog.new('2')
  newBattle.timelineWin2:addDialog(newDialog2)
  newBattle.timelineWin2:setDismissable(false)
  ui.addWindow(newBattle.timelineWin2)

  newBattle.timelineWin3 = Window.new(
    BattleConsts.win3.startX, 
    BattleConsts.win3.startY, 
    BattleConsts.win3.w, 
    BattleConsts.win3.h, 
    false) 
  local newDialog3 = Dialog.new('3')
  newBattle.timelineWin3:addDialog(newDialog3)
  newBattle.timelineWin3:setDismissable(false)
  ui.addWindow(newBattle.timelineWin3)

  newBattle.timelineWin4 = Window.new(
    BattleConsts.win4.startX, 
    BattleConsts.win4.startY, 
    BattleConsts.win4.w, 
    BattleConsts.win4.h, 
    false) 
  local newDialog4 = Dialog.new('4')
  newBattle.timelineWin4:addDialog(newDialog4)
  newBattle.timelineWin4:setDismissable(false)
  ui.addWindow(newBattle.timelineWin4)

  return newBattle
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
    self.playerChars[i].userData.statusWin = self.windows[i]

    --TODO: fix lmao
    if i == 1 then self.playerChars[i].userData.statusWinInfo =  BattleConsts.win1 end    
    if i == 2 then self.playerChars[i].userData.statusWinInfo =  BattleConsts.win2 end
    if i == 3 then self.playerChars[i].userData.statusWinInfo =  BattleConsts.win3 end
    if i == 4 then self.playerChars[i].userData.statusWinInfo =  BattleConsts.win4 end


  end  

  --command window
  self.commandWindow = Window.new(34, 160, 36, 4, false)
  local newDialog1 = Dialog.new('0')
  self.commandWindow:addDialog(newDialog1)
  ui.addWindow(self.commandWindow)

  --calc speed

  --set new turn
  self.nextTurnChar = 0
  --self:newTurn()

  --EVENTS
  --1 disable input
  local disableInput = DisableInputEvent.new()

  --2 transition from field
  local transitionFromField = TransitionFromFieldEvent.new()

  --3 move window
  --battle.currentBattle.windows[1].x = 100
  local moveWindow1 = MoveWindowEvent.new(battle.currentBattle.windows[1], BattleConsts.win1.regularX, BattleConsts.win1.regularY, 100)
  local moveWindow2 = MoveWindowEvent.new(battle.currentBattle.windows[2], BattleConsts.win2.regularX, BattleConsts.win2.regularY, 100)
  local moveWindow3 = MoveWindowEvent.new(battle.currentBattle.windows[3], BattleConsts.win3.regularX, BattleConsts.win3.regularY, 100)
  local moveWindow4 = MoveWindowEvent.new(battle.currentBattle.windows[4], BattleConsts.win4.regularX, BattleConsts.win4.regularY, 100)
  local compEvent = CompositeEvent.new()
  compEvent:addEvent(moveWindow1)
  compEvent:addEvent(moveWindow2)
  compEvent:addEvent(moveWindow3)
  compEvent:addEvent(moveWindow4)

  --4 new turn
  local newTurn = NewTurnEvent.new()

  self.eventManager:addEvent(disableInput)
  self.eventManager:addEvent(transitionFromField)
  self.eventManager:addEvent(compEvent) 
  self.eventManager:addEvent(newTurn) 

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

function Battle:endBattle()

  battle.endCurrentBattle()
end

function Battle:newTurn()

  local prevTurnChar = self:getTurnChar(0)

  if self:isPlayer(prevTurnChar) then

    local moveBackWin = MoveWindowEvent.new(
      prevTurnChar.userData.statusWin, 
      prevTurnChar.userData.statusWinInfo.regularX, 
      prevTurnChar.userData.statusWinInfo.regularY, 
      10
    )

    self.eventManager:addEvent(moveBackWin)

  end

  self.nextTurnChar = self.nextTurnChar + 1 
  if self.nextTurnChar > #self.battleChars then
    self.nextTurnChar = 1
  end

  local turnChar = self:getTurnChar(0)

  if self:isPlayer(turnChar) then

    local moveWin = MoveWindowEvent.new(
      turnChar.userData.statusWin, 
      turnChar.userData.statusWinInfo.selectedX, 
      turnChar.userData.statusWinInfo.selectedY, 
      10)

    local playerTurn = PlayerTurnEvent.new(turnChar)

    self.eventManager:addEvent(moveWin)
    self.eventManager:addEvent(playerTurn)


  end

-- se enemy attack
  if self:isEnemy(turnChar) then
    -- print(turnChar.name .. ' attacks ' .. self:getRandomPlayer().name)

    local res = data.enemies[turnChar.id].onTurn(self, turnChar, self.playerChars)

    local winVibration = WindowVibrationEvent.new(res.target.userData.statusWin, 256)

    local newTurn = NewTurnEvent.new()
    
    self.eventManager:addEvent(winVibration)
    self.eventManager:addEvent(newTurn)

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

  self.eventManager:update(nil, 16)

end

function Battle:render()
  ui.renderSprite('base.spritesheets.testbackground', 72, 40) 
  ui.renderSprite('base.spritesheets.enemy_battle_sprite', math.floor(400/2) - 25, math.floor(225/2) - 25)

end

return Battle
