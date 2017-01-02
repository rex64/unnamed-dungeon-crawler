local BattleConsts             = require('battle.BattleConsts')
local Dialog                   = require('ui.Dialog')
local DialogWindow             = require('ui.DialogWindow')
local MenuItem                 = require('ui.MenuItem')
local ChoiceMenu               = require('ui.ChoiceMenu')
local EnableInputEvent         = require('battle.events.EnableInputEvent')
local HeroStatusWindow         = require('ui.heroStatusWindow')
local ArbistraryFunctionEvent  = require('battle.events.ArbitraryFunctionEvent')
local ShowDialogEvent          = require('ui.events.ShowDialogEvent')

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


  --1
  newBattle.timelineWin1 = HeroStatusWindow.new(
    BattleConsts.win1.startX, 
    BattleConsts.win1.startY, 
    BattleConsts.win1.w, 
    BattleConsts.win1.h, 
    '1')
  ui.addWindow(newBattle.timelineWin1)

  --2
  newBattle.timelineWin2 = HeroStatusWindow.new(
    BattleConsts.win2.startX, 
    BattleConsts.win2.startY, 
    BattleConsts.win2.w, 
    BattleConsts.win2.h, 
    '1')
  ui.addWindow(newBattle.timelineWin2)

  --3
  newBattle.timelineWin3 = HeroStatusWindow.new(
    BattleConsts.win3.startX, 
    BattleConsts.win3.startY, 
    BattleConsts.win3.w, 
    BattleConsts.win3.h,
    '1')
  ui.addWindow(newBattle.timelineWin3)

  --4
  newBattle.timelineWin4 = HeroStatusWindow.new(
    BattleConsts.win4.startX, 
    BattleConsts.win4.startY, 
    BattleConsts.win4.w, 
    BattleConsts.win4.h,
    '1')
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
    local partyMemberId = save.getPartyMemberId(i)
    local partyMemberName = save.getPartyMemberName(partyMemberId)

    --TODO: fix
    local playerChar = BattleChar.new(partyMemberName, i)
    playerChar.id = partyMemberId 

    self:addPlayerChar(playerChar)

    --self.windows[i].dialog.text = self.playerChars[i].name
    self.windows[i]:setHero(playerChar)
    self.playerChars[i].userData.statusWin = self.windows[i]

    --TODO: fix lmao
    if i == 1 then self.playerChars[i].userData.statusWinInfo = BattleConsts.win1 end    
    if i == 2 then self.playerChars[i].userData.statusWinInfo = BattleConsts.win2 end
    if i == 3 then self.playerChars[i].userData.statusWinInfo = BattleConsts.win3 end
    if i == 4 then self.playerChars[i].userData.statusWinInfo = BattleConsts.win4 end


  end  

  self.commandWindow = ChoiceWindow.new(32, 160, 36, 7, ChoiceMenu.new())
  self.commandWindow:setDismissable(false)
  ui.addWindow(self.commandWindow)

  --calc speed

  --set new turn
  self.nextTurnChar = 0
  --self:newTurn()

  --EVENTS
  --1 disable input
  local disableInput = DisableInputEvent.new():debug('battle.lua - ' .. debug.getinfo(1).currentline)

  --2 transition from field
  local transitionFromField = TransitionFromFieldEvent.new():debug('battle.lua - ' .. debug.getinfo(1).currentline)

  --3 move window
  --battle.currentBattle.windows[1].x = 100
  local moveWindow1 = MoveWindowEvent.new(battle.currentBattle.windows[1], BattleConsts.win1.regularX, BattleConsts.win1.regularY, 100)
  local moveWindow2 = MoveWindowEvent.new(battle.currentBattle.windows[2], BattleConsts.win2.regularX, BattleConsts.win2.regularY, 100)
  local moveWindow3 = MoveWindowEvent.new(battle.currentBattle.windows[3], BattleConsts.win3.regularX, BattleConsts.win3.regularY, 100)
  local moveWindow4 = MoveWindowEvent.new(battle.currentBattle.windows[4], BattleConsts.win4.regularX, BattleConsts.win4.regularY, 100)
  local compEvent = CompositeEvent.new():debug('battle.lua - ' .. debug.getinfo(1).currentline)
  compEvent:addEvent(moveWindow1)
  compEvent:addEvent(moveWindow2)
  compEvent:addEvent(moveWindow3)
  compEvent:addEvent(moveWindow4)

  --4 new turn
  local newTurn = NewTurnEvent.new():debug('battle.lua - ' .. debug.getinfo(1).currentline)

  self.eventManager:addEvent(disableInput)
  self.eventManager:addEvent(transitionFromField)
  self.eventManager:addEvent(compEvent) 
  self.eventManager:addEvent(newTurn)   
  --self.eventManager:addEvent(enableInput) 

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

    local enableInput = EnableInputEvent.new():debug('battle.lua - ' .. debug.getinfo(1).currentline)

    self.eventManager:addEvent(moveWin)
    self.eventManager:addEvent(playerTurn)

    self.eventManager:addEvent(enableInput)

  end

-- se enemy attack
  if self:isEnemy(turnChar) then
    -- print(turnChar.name .. ' attacks ' .. self:getRandomPlayer().name)

    local res = data.enemies[turnChar.id].onTurn(self, turnChar, self.playerChars)

    local winVibration = WindowVibrationEvent.new(res.target.userData.statusWin, 256)

    local newTurn = NewTurnEvent.new()

    self.eventManager:addEvent(winVibration)
    self.eventManager:addEvent(EnableInputEvent.new())
    self.eventManager:addEvent(ShowDialogEvent.new(res.dialogText))
    self.eventManager:addEvent(DisableInputEvent.new())
    self.eventManager:addEvent(newTurn)

  end

  if self:youWin() then
    self:endBattle()
  end

end

function Battle:onPlayerTurn(turnChar)

  --local turnChar = self:getTurnChar(0)

  if self:isPlayer(turnChar) then

    local heroSkills = save.getHeroSkills(turnChar.id)

    self.commandWindow.choiceMenu:resetMenu()

    for i, skillId in ipairs(heroSkills) do

      local skillName = save.getSkillName(skillId)
      local skillMenuItem = MenuItem.new(skillName, 

        function() 

          --if singleTarget
          local singleTargetWin = ChoiceWindow.new(180, 130, 12, 6, ChoiceMenu.new())

          for h, target in ipairs(self:getAliveEnemies()) do

            local skillMenuItem2 = MenuItem.new(target.name .. ' ' .. target.hp .. '/' .. target.maxHp .. ' HP', 

              function() 
                
                local skillResult = data.skills[skillId].onSelect(turnChar, target)
                
                local funcEvent1 = ArbistraryFunctionEvent.new(function() data.skills[skillId].onSelect(turnChar, target) end, 'skill - onSelect')
                local funcEvent2 = ArbistraryFunctionEvent.new(function() singleTargetWin:dismiss() end, 'single target win dismiss')
                local funcEvent3 = ArbistraryFunctionEvent.new(function() self:newTurn() end, 'newTurn func')
                
                
                self.eventManager:addEvent(funcEvent1)
                self.eventManager:addEvent(funcEvent2)
                self.eventManager:addEvent(ShowDialogEvent.new(skillResult.dialogText))
                self.eventManager:addEvent(funcEvent3)
                
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

function Battle:getAliveEnemies()

  local enemiesAlive = {}

  for i, enemy in ipairs(self.enemyChars) do

    if self:isAlive(enemy) then 
      table.insert(enemiesAlive, enemy) 
    end

  end

  return enemiesAlive

end


function Battle:isAlive(char)

  if (char.hp > 0) then return true end

  return false

end

function Battle:youWin()

  for i, enemy in ipairs(self.enemyChars) do

    if (enemy.hp > 0) then return false end
  end
  return true

end

function Battle:update(dt)

  self.eventManager:update(nil, 16)

end

function Battle:render()

  engine.renderSprite('base.spritesheets.testbackground', 0, 0) 

  local enemyAlive = self:getAliveEnemies()

  local numeroDiDivisioni = math.floor(256 / #enemyAlive)

  for i, enemy in ipairs(enemyAlive) do
    engine.renderSprite(
      'base.spritesheets.enemy_battle_sprite', 
      math.floor(numeroDiDivisioni * i ) - math.floor(numeroDiDivisioni / 2) - 16, 
      math.floor(144/2) - 25
    )
  end



end

return Battle
