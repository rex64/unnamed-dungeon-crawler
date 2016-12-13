--//////////////////////////////////////////////////////////////////////
--************************
--CloseMainMenuEvent
--************************

CloseMainMenuEvent = {}
CloseMainMenuEvent.__index = CloseMainMenuEvent
setmetatable(CloseMainMenuEvent, {__index = Event})

function CloseMainMenuEvent.new()
  local self = setmetatable({}, CloseMainMenuEvent)

  self.name = 'CloseMainMenuEvent'
  self.done = false;

  return self
end

function CloseMainMenuEvent:update(input, dt)

  print('event - CloseMainMenuEvent')
  ui.closeMenu()
  self.done = true;
end

return CloseMainMenuEvent
