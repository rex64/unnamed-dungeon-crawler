--//////////////////////////////////////////////////////////////////////
--************************
--OpenMainMenuEvent
--************************

OpenMainMenuEvent = {}
OpenMainMenuEvent.__index = OpenMainMenuEvent
setmetatable(OpenMainMenuEvent, {__index = Event})

function OpenMainMenuEvent.new()
  local self = setmetatable({}, OpenMainMenuEvent)

  self.name = 'OpenMainMenuEvent'
  self.done = false;

  return self
end

function OpenMainMenuEvent:update(input, dt)

  print('event - OpenMainMenuEvent')
  ui.openMenu()
  self.done = true;
end

return OpenMainMenuEvent
