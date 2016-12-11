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

return TransitionFromFieldEvent
