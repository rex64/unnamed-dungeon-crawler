--//////////////////////////////////////////////////////////////////////
--************************
--QuitGameEvent
--************************

QuitGameEvent = {}
QuitGameEvent.__index = QuitGameEvent
setmetatable(QuitGameEvent, {__index = Event})

function QuitGameEvent.new()
  local self = setmetatable({}, QuitGameEvent)

  self.name = 'QuitGameEvent'
  self.done = false;

  return self
end

function QuitGameEvent:update(input, dt)

  print('event - QuitGameEvent')
  engine.quitGame()
  self.done = true;
end

return QuitGameEvent
