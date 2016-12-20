--//////////////////////////////////////////////////////////////////////
--************************
--EnableInputEvent
--************************

EnableInputEvent = {}
EnableInputEvent.__index = EnableInputEvent
setmetatable(EnableInputEvent, {__index = Event})

function EnableInputEvent.new()
  local self = setmetatable(Event.new(), EnableInputEvent)

  self.name = 'EnableInputEvent'
  self.done = false;

  return self
end

function EnableInputEvent:update(input, dt)

  print('event - enable input')
  self.done = true;
  
  engine.enableInput()
  
end

return EnableInputEvent
