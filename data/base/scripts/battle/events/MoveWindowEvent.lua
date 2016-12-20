--//////////////////////////////////////////////////////////////////////
--************************
--MoveWindowEvent
--************************

MoveWindowEvent = {}
MoveWindowEvent.__index = MoveWindowEvent
setmetatable(MoveWindowEvent, {__index = Event})

function MoveWindowEvent.new(win, targetX, targetY, duration)
  local self = setmetatable(Event.new(), MoveWindowEvent)

  self.name = 'MoveWindowEvent'
  self.done = false;

  self.win = win

  self.oldX = win.x
  self.oldY = win.y

  self.currentX = win.x
  self.currentY = win.y

  self.targetX = targetX
  self.targetY = targetY

  self.duration = duration
  self.currTimer = 0

  return self
end

function MoveWindowEvent:update(input, dt)

  self.currTimer = math.min(self.currTimer + dt, self.duration)

  local lerp = function(a, b, t)
    return a * (1-t) + (b*t)
  end

  local t = self.currTimer / self.duration

  --X
  self.currentX = lerp(self.oldX, self.targetX, t)
  self.win.x = math.floor(self.currentX)

  --Y
  self.currentY = lerp(self.oldY, self.targetY, t)
  self.win.y = math.floor(self.currentY)

  if (self.currTimer == self.duration) then
    self.done = true;
  end


  --print('event - move window')

end

return MoveWindowEvent
