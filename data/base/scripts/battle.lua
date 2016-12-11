--//////////////////////////////////////////////////////////////////////
--************************
--Battle consts
--************************
if battle ~= nil then

  battle.win1 = {
    w = 8, 
    h = 4,
    startX    = 0,
    startY    = 0,
    regularX  = 8,
    regularY  = 8,
    selectedX = 16,
    selectedY = 8
  } 

  battle.win2 = {
    w = 8, 
    h = 4,
    startX    = 0,
    startY    = 0,
    regularX  = 320,
    regularY  = 8,
    selectedX = 300,
    selectedY = 8
  } 

  battle.win3 = {
    w = 8, 
    h = 4,
    startX    = 0,
    startY    = 0,
    regularX  = 8,
    regularY  = 100,
    selectedX = 16,
    selectedY = 100
  } 

  battle.win4 = {
    w = 8, 
    h = 4,
    startX    = 0,
    startY    = 0,
    regularX  = 320,
    regularY  = 100,
    selectedX = 300,
    selectedY = 100
  } 

end

--//////////////////////////////////////////////////////////////////////
--************************
--Battle Events
--************************

--//////////////////////////////////////////////////////////////////////
--************************
--DisableInputEvent
--************************

DisableInputEvent = {}
DisableInputEvent.__index = DisableInputEvent
setmetatable(DisableInputEvent, {__index = Event})

function DisableInputEvent.new()
  local self = setmetatable({}, DisableInputEvent)

  self.name = 'DisableInputEvent'
  self.done = false;

  return self
end

function DisableInputEvent:update(input, dt)

  print('event - disable input')
  self.done = true;
end

--//////////////////////////////////////////////////////////////////////
--************************
--TransitionFromFieldEvent
--************************

TransitionFromFieldEvent = {}
TransitionFromFieldEvent.__index = TransitionFromFieldEvent
setmetatable(TransitionFromFieldEvent, {__index = Event})


function TransitionFromFieldEvent.new()
  local self = setmetatable({}, TransitionFromFieldEvent)

  self.name = 'TransitionFromFieldEvent'
  self.done = false;

  return self
end

function TransitionFromFieldEvent:update(input, dt)

  print('event - Transition From Field')
  self.done = true;
end

--//////////////////////////////////////////////////////////////////////
--************************
--MoveWindowEvent
--************************

MoveWindowEvent = {}
MoveWindowEvent.__index = MoveWindowEvent
setmetatable(MoveWindowEvent, {__index = Event})

function MoveWindowEvent.new(win, targetX, targetY, duration)
  local self = setmetatable({}, MoveWindowEvent)

  self.name = 'MoveWindowEvent'
  self.done = false;

  self.win = win

  self.oldX = win.x
  self.oldY = win.y

  self.currentX = win.x
  self.currentY = win.y

  self.targetX = targetX
  self.targetY = targetY

  self.duration = duration
  self.currTimer = 0

  return self
end

function MoveWindowEvent:update(input, dt)

  self.currTimer = math.min(self.currTimer + dt, self.duration)

  local lerp = function(a, b, t)
    return a * (1-t) + (b*t)
  end

  local t = self.currTimer / self.duration

  --X
  self.currentX = lerp(self.oldX, self.targetX, t)
  self.win.x = math.floor(self.currentX)

  --Y
  self.currentY = lerp(self.oldY, self.targetY, t)
  self.win.y = math.floor(self.currentY)

  if (self.currTimer == self.duration) then
    self.done = true;
  end


  --print('event - move window')

end

--//////////////////////////////////////////////////////////////////////
--************************
--NewTurnEvent
--************************

NewTurnEvent = {}
NewTurnEvent.__index = NewTurnEvent
setmetatable(NewTurnEvent, {__index = Event})


function NewTurnEvent.new()
  local self = setmetatable({}, NewTurnEvent)

  self.name = 'NewTurnEvent'
  self.done = false;

  return self
end

function NewTurnEvent:update(input, dt)

  print('event - NewTurnEvent')
  battle.currentBattle:newTurn()
  self.done = true;
end

--//////////////////////////////////////////////////////////////////////
--************************
--PlayerTurnEvent
--************************

PlayerTurnEvent = {}
PlayerTurnEvent.__index = PlayerTurnEvent
setmetatable(PlayerTurnEvent, {__index = Event})


function PlayerTurnEvent.new(turnPlayer)
  local self = setmetatable({}, PlayerTurnEvent)

  self.name = 'PlayerTurnEvent'
  self.done = false
  self.turnPlayer = turnPlayer

  return self
end

function PlayerTurnEvent:update(input, dt)

  print('event - PlayerTurnEvent')
  battle.currentBattle:onPlayerTurn(self.turnPlayer)

  self.done = true;
end

--//////////////////////////////////////////////////////////////////////
--************************
--WindowVibrationEvent
--************************

WindowVibrationEvent = {}
WindowVibrationEvent.__index = WindowVibrationEvent
setmetatable(WindowVibrationEvent, {__index = Event})

function WindowVibrationEvent.new(win, duration)
  local self = setmetatable({}, WindowVibrationEvent)

  self.name = 'WindowVibrationEvent'
  self.done = false;

  self.win = win

  self.oldY = win.y

  self.currentY = win.y

  self.duration = duration
  self.currTimer = 0

  return self
end

function WindowVibrationEvent:update(input, dt)

  self.currTimer = math.min(self.currTimer + dt, self.duration)

  self.currentY = math.sin(self.currTimer)
  self.win.y = self.oldY + math.floor(self.currentY)

  if (self.currTimer == self.duration) then
    
    self.win.y = self.oldY
    self.done = true;
  end
end


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
    battle.win1.startX, 
    battle.win1.startY, 
    battle.win1.w, 
    battle.win1.h, 
    false)  
  local newDialog1 = Dialog.new('1')
  newBattle.timelineWin1:addDialog(newDialog1)
  newBattle.timelineWin1:setDismissable(false)
  ui.addWindow(newBattle.timelineWin1)

  newBattle.timelineWin2 = Window.new(
    battle.win2.startX, 
    battle.win2.startY, 
    battle.win2.w, 
    battle.win2.h, 
    false) 
  local newDialog2 = Dialog.new('2')
  newBattle.timelineWin2:addDialog(newDialog2)
  newBattle.timelineWin2:setDismissable(false)
  ui.addWindow(newBattle.timelineWin2)

  newBattle.timelineWin3 = Window.new(
    battle.win3.startX, 
    battle.win3.startY, 
    battle.win3.w, 
    battle.win3.h, 
    false) 
  local newDialog3 = Dialog.new('3')
  newBattle.timelineWin3:addDialog(newDialog3)
  newBattle.timelineWin3:setDismissable(false)
  ui.addWindow(newBattle.timelineWin3)

  newBattle.timelineWin4 = Window.new(
    battle.win4.startX, 
    battle.win4.startY, 
    battle.win4.w, 
    battle.win4.h, 
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
    if i == 1 then self.playerChars[i].userData.statusWinInfo =  battle.win1 end    
    if i == 2 then self.playerChars[i].userData.statusWinInfo =  battle.win2 end
    if i == 3 then self.playerChars[i].userData.statusWinInfo =  battle.win3 end
    if i == 4 then self.playerChars[i].userData.statusWinInfo =  battle.win4 end


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
  local moveWindow1 = MoveWindowEvent.new(battle.currentBattle.windows[1], battle.win1.regularX, battle.win1.regularY, 100)
  local moveWindow2 = MoveWindowEvent.new(battle.currentBattle.windows[2], battle.win2.regularX, battle.win2.regularY, 100)
  local moveWindow3 = MoveWindowEvent.new(battle.currentBattle.windows[3], battle.win3.regularX, battle.win3.regularY, 100)
  local moveWindow4 = MoveWindowEvent.new(battle.currentBattle.windows[4], battle.win4.regularX, battle.win4.regularY, 100)
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
  newBattleChar.index = i
  newBattleChar.hp = 100
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


--//////////////////////////////////////////////////////////////////////

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
