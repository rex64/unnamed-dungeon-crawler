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

return DisableInputEvent
