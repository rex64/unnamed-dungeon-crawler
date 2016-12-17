--************************
--Dialog
--************************

Dialog = {}
Dialog.__index = Dialog

function Dialog.new(text)
  local self = setmetatable({}, Dialog)
  self.text = text

  return self
end

function Dialog:render(x, y)
  
  engine.renderTextLine(self.text, x, y)
  
end

return Dialog
