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

return NewTurnEvent
