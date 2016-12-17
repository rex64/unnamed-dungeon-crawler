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

  self.choiceMenu = nil
  self.dialog = nil

  self.dismissable = dismissable
  if type(dismissable) ~= "boolean" then self.dismissable = true end

  return self
end

function Window:onInput(input)

  if input.up then
    if self:hasChoiceMenu() then
      self.choiceMenu.currMenuItem = math.max(1, self.choiceMenu.currMenuItem - 1) 
    end
  elseif input.right then
    if self:hasChoiceMenu() then
      self.choiceMenu.currMenuItem = math.min(#self.choiceMenu.menuItems, self.choiceMenu.currMenuItem + 1) 

    end
  elseif input.down then
    if self:hasChoiceMenu() then
      self.choiceMenu.currMenuItem = math.min(#self.choiceMenu.menuItems, self.choiceMenu.currMenuItem + 1) 

    end
  elseif input.left then
  elseif input.ok then
    if self.choiceMenu.menuItems[self.choiceMenu.currMenuItem].callback ~= nil then
      self.choiceMenu.menuItems[self.choiceMenu.currMenuItem].callback()
    end
  elseif self:hasDialog() then
    if self:isDismissable() then
      self:dismiss()
    end
  elseif input.cancel then
    if self:isDismissable() then
      self:dismiss()
    end
  end
  
end

function Window:update(dt)

end

function Window:render()

  engine.renderWindow(self.x, self.y, self.w, self.h)

  if self.dialog ~= nil then
    
    local x = self.x + self.margins.x
    local y = self.y + self.margins.x

    self.dialog:render(x, y)
  end

  if self.choiceMenu ~= nil then

    local x = self.x + self.margins.x
    local y = self.y + self.margins.x

    self.choiceMenu:render(x, y)
  end

end 

function Window:addDialog(newDialog)

  newDialog.win = self
  self.dialog = newDialog

end

function Window:hasDialog()
  if self.dialog ~= nil then
    return true
  end
  return false
end

function Window:addChoiceMenu(newChoiceMenu)

  newChoiceMenu.win = self
  self.choiceMenu = newChoiceMenu

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

end


function Window:isDismissable()
  return self.dismissable
end

function Window:setDismissable(dis)
  self.dismissable = dis
end

return Window
