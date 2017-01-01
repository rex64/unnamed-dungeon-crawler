--************************
--Dialog
--************************

Dialog = {}
Dialog.__index = Dialog

function Dialog.new(text)
  local self = setmetatable({}, Dialog)
  self.text = text
  
  self:setAnimated(100)

  return self
end

function Dialog:update(dt)

  if self.isAnimated == true then
  
    self.totalTime = self.totalTime + dt
    local charsNo = math.floor(self.totalTime / self.speed)
    self.text = string.sub(self.completeText, 1, charsNo)
  
  end
  

end

function Dialog:render(x, y)
  
  engine.renderTextLine(self.text, x, y)
  
end

function Dialog:setAnimated(speed)

  self.totalTime = 0
  self.speed = speed
  self.completeText = self.text
  self.text = ''
  self.isAnimated = true

end

return Dialog
