--//////////////////////////////////////////////////////////////////////
--************************
--DisableInputEvent
--************************

DisableInputEvent = {}
DisableInputEvent.__index = DisableInputEvent
setmetatable(DisableInputEvent, {__index = Event})

function DisableInputEvent.new()
  local self = setmetatable(Event.new(), DisableInputEvent)

  self.name = 'DisableInputEvent'
  self.done = false;

  return self
end

function DisableInputEvent:update(input, dt)

  print('event - disable input')
  self.done = true;
  
  engine.disableInput()
  
end

return DisableInputEvent
