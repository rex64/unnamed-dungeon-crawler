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

return PlayerTurnEvent
