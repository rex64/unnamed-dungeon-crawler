--************************
--Window
--************************
Window = {}
Window.__index = Window

function Window.new(x, y, w, h, dismissable)
  local self = setmetatable({}, Window)
  self.x = x 
  self.y = y 
  self.w = w 
  self.h = h 
  self.margins = {x=12, y=0}

  --self.choiceMenu = nil
  --self.dialog = nil

  self.dismissable = dismissable
  if type(dismissable) ~= "boolean" then self.dismissable = false end

  self.dismissed = false

  return self
end

function Window:onInput(input)


end

function Window:update(dt)

end

function Window:render()

  engine.renderWindow(self.x, self.y, self.w, self.h)

end 

function Window:hasDialog()
  if self.dialog ~= nil then
    return true
  end
  return false
end

function Window:hasChoiceMenu()

  if self.choiceMenu ~= nil then
    return true
  end
  return false
end

function Window:dismiss()

  local winIndex = nil

  for i, win in ipairs(ui.windows) do

    if (win == self) then winIndex = i end

  end

  if (winIndex ~= nil) then

    table.remove(ui.windows, winIndex)
  end

  self.dismissed = true

end


function Window:isDismissable()
  return self.dismissable
end

function Window:wasDismissed()
  return self.dismissed
end

function Window:setDismissable(dis)
  self.dismissable = dis
end

return Window
