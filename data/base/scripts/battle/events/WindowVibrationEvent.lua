--//////////////////////////////////////////////////////////////////////
--************************
--WindowVibrationEvent
--************************

WindowVibrationEvent = {}
WindowVibrationEvent.__index = WindowVibrationEvent
setmetatable(WindowVibrationEvent, {__index = Event})

function WindowVibrationEvent.new(win, duration)
  local self = setmetatable({}, WindowVibrationEvent)

  self.name = 'WindowVibrationEvent'
  self.done = false;

  self.win = win

  self.oldY = win.y

  self.currentY = win.y

  self.duration = duration
  self.currTimer = 0

  return self
end

return WindowVibrationEvent
