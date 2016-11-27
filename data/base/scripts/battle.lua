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

  newBattle.timelineWin1 = Window.new(8*(8*0), 100, 8, 4, false)  
  local newDialog1 = Dialog.new('1')
  newBattle.timelineWin1:addDialog(newDialog1)
  newBattle.timelineWin1:setDismissable(false)
  ui.addWindow(newBattle.timelineWin1)

  newBattle.timelineWin2 = Window.new(8*(8*1), 100, 8, 4, false)
  local newDialog2 = Dialog.new('2')
  newBattle.timelineWin2:addDialog(newDialog2)
  newBattle.timelineWin2:setDismissable(false)
  ui.addWindow(newBattle.timelineWin2)

  newBattle.timelineWin3 = Window.new(8*(8*2), 100, 8, 4, false)
  local newDialog3 = Dialog.new('3')
  newBattle.timelineWin3:addDialog(newDialog3)
  newBattle.timelineWin3:setDismissable(false)
  ui.addWindow(newBattle.timelineWin3)

  newBattle.timelineWin4 = Window.new(8*(8*3), 100, 8, 4, false)
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

  self.commandWindow = Window.new(180, 8, 8, 10, false)
  local newDialog1 = Dialog.new('0')
  self.commandWindow:addDialog(newDialog1)
  ui.addWindow(self.commandWindow)

  --calc speed


  self:newTurn()

end

function Battle:endBattle()

  battle.endCurrentBattle()
end

function Battle:newTurn()

  self.commandWindow.dialog.text = self:getTurnChar(0).name
  self.timelineWin4.dialog.text = self:getTurnChar(1).name
  self.timelineWin2.dialog.text = self:getTurnChar(2).name
  self.timelineWin3.dialog.text = self:getTurnChar(3).name
  self.timelineWin1.dialog.text = self:getTurnChar(4).name

end

function Battle:getTurnChar(turnNo)

  local index = self.nextTurnChar + turnNo

  if index > #self.battleChars then
    index = turnNo
  end


  return self.battleChars[index]
end

function Battle:endTurn()
  self.nextTurnChar = self.nextTurnChar + 1 
  if self.nextTurnChar > #self.battleChars then
    self.nextTurnChar = 1
  end

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
  local clock = os.clock
  function sleep(n)  -- seconds
    local t0 = clock()
    while clock() - t0 <= n do end
  end
  sleep(0.5)

-- get turn char
  local turnChar = self:getTurnChar(0)

-- se player menu
  if self:isPlayer(turnChar) then
    local target = self:getRandomEnemy()
    target.hp = target.hp - 10
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/100') 

  end

-- se enemy attack
  if self:isEnemy(turnChar) then
    print(turnChar.name .. ' attacks ' .. self:getRandomPlayer().name)

  end

  if self:youWin() then
    self:endBattle()
  end

  self:endTurn()
  self:newTurn()

end

function Battle:render()
end


--************************
--BattleChar
--************************
BattleChar = {}
BattleChar.__index = BattleChar

function BattleChar.new(name)
  local newBattleChar = {}
  setmetatable(newBattleChar, BattleChar)

  newBattleChar.name = name
  newBattleChar.hp = 100

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
