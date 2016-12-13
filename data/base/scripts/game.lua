local Event           = require('events.Event')
local CompositeEvent  = require('events.CompositeEvent')
local EventManager    = require('events.EventManager')

local OpenMainMenuEvent = require('game.events.OpenMainMenuEvent')
local CloseMenuEvent    = require('game.events.CloseMainMenuEvent')


--GAME stuff
if(game ~= nil) then

  game.eventManager = EventManager.new()


  game.onInput = function(input)

    if input.menu == true then
      if ui.isMainMenuOpen() ~= true then
        game.eventManager:addEvent(OpenMainMenuEvent.new())
      else
        game.eventManager:addEvent(CloseMainMenuEvent.new())

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

    -- battle.update(dt)
    -- field.update(dt)

    game.eventManager:update(nil, dt)

  end

  game.render = function()

  end

end