--//////////////////////////////////////////////////////////////////////
--************************
--WindowVibrationEvent
--************************

WindowVibrationEvent = {}
WindowVibrationEvent.__index = WindowVibrationEvent
setmetatable(WindowVibrationEvent, {__index = Event})

function WindowVibrationEvent.new(win, duration)
  local self = setmetatable(Event.new(), WindowVibrationEvent)

  self.name = 'WindowVibrationEvent'
  self.done = false;

  self.win = win

  self.oldY = win.y

  self.currentY = win.y

  self.duration = duration
  self.currTimer = 0

  return self
end

function WindowVibrationEvent:update(input, dt)

  self.currTimer = math.min(self.currTimer + dt, self.duration)

  self.currentY = math.sin(self.currTimer)
  self.win.y = self.oldY + math.floor(self.currentY)

  if (self.currTimer == self.duration) then
    
    self.win.y = self.oldY
    self.done = true;
  end
end

return WindowVibrationEvent
