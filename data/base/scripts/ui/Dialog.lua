--************************
--Dialog
--************************

Dialog = {}
Dialog.__index = Dialog

function Dialog.new(text)
  local self = setmetatable({}, Dialog)
  self.text = text
  
  self:setAnimated(16*2)

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

function Dialog:setAnimationSpeed(speed)
  self.speed = speed
end

function Dialog:isAnimationEnded()

  local charsNo = math.floor(self.totalTime / self.speed)
  
  if charsNo >= string.len(self.completeText) then return true end
  
  return false

end


return Dialog
