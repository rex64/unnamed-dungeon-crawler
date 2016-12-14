--events

local Event           = require('events.Event')
local CompositeEvent  = require('events.CompositeEvent')
local EventManager    = require('events.EventManager')

local DisableInputEvent         = require('battle.events.DisableInputEvent')
local TransitionFromFieldEvent  = require('battle.events.TransitionFromFieldEvent')
local MoveWindowEvent           = require('battle.events.MoveWindowEvent')
local NewTurnEvent              = require('battle.events.NewTurnEvent')
local PlayerTurnEvent           = require('battle.events.PlayerTurnEvent')
local WindowVibrationEvent      = require('battle.events.WindowVibrationEvent')

--//////////////////////////////////////////////////////////////////////

battle = {}

if battle ~= nil then

  battle.currentBattle = nil

--[[
  battle.onInput = function (button)

    if battle.weBattle() then battle.currentBattle:onInput(button) end
  end
]]--

  battle.update = function(input, dt) 

    if battle.weBattle() then battle.currentBattle:update(input, dt) end
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
