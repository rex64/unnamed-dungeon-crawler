local Event           = require('events.Event')
local CompositeEvent  = require('events.CompositeEvent')
local EventManager    = require('events.EventManager')

local Process         = require('processes.Process')
local ProcessManager  = require('processes.ProcessManager')


local OpenMainMenuEvent = require('game.events.OpenMainMenuEvent')
local CloseMenuEvent    = require('game.events.CloseMainMenuEvent')

local MessageLog        = require('game.MessageLog')

--GAME stuff

game = {}

if(game ~= nil) then

  game.paused = false

  game.eventManager = EventManager.new()
  game.processManager = ProcessManager.new()

  game.messageLog = MessageLog.new()

  game.onInput = function(input)

    if input.pause == true then   
      game.paused = not game.paused
    end

    if game.paused then   
      return;
    end

    if input.menu == true then
      if ui.isMainMenuOpen() ~= true then
        game.eventManager:addEvent(OpenMainMenuEvent.new())
--      else
--        game.eventManager:addEvent(CloseMainMenuEvent.new())

      end

    end

    if ui.isMainMenuOpen() == true then

      ui.onInput(input)
    else

      field.onInput(input)

    end

    -- battle.onInput(input)

  end

  game.update = function(dt)

    if game.paused then   
      return;
    end

    game.processManager:update(nil, dt)
    ui.update(dt) 
    battle.update(dt) 
    field.update(dt)
    game.messageLog:update(dt)

    game.eventManager:update(nil, dt)

  end

  game.render = function()

    field.render()
    game.messageLog:render()
    battle.render()
    ui.render()

    if game.paused then
      engine.renderWindow(0, 0, 8, 3)
      engine.renderTextLine('PAUSE', 16, 16);
    end
    --engine.renderTextLine('11110123456789abcdefghijklmnopqrstuvwxyz', 0, 0);
  end

  game.wasOkPressedThisFrame = function(input)

    if input.ok == true and input.ok_prevframe == false then 
      return true 
    else 
      return false
    end

  end


end