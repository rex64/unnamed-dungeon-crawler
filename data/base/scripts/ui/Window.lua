--************************
--Window
--************************
Window = {}
Window.__index = Window

function Window.new(x, y, w, h, dismissable)
  local win = {}
  setmetatable(win, Window)
  win.x = x 
  win.y = y 
  win.w = w 
  win.h = h 
  win.margins = {x=12, y=0}
  win.menuItems = {}
  win.dialog = nil
  win.currMenuItem = 1  

  win.dismissable = dismissable
  if type(dismissable) ~= "boolean" then win.dismissable = true end

  return win
end

function Window:addMenuItem(newMenuItem)

  table.insert(self.menuItems, newMenuItem)

end

function Window:resetMenu()

  self.menuItems = {}

end

function Window:addDialog(newDialog)

  self.dialog = newDialog

end

function Window:hasDialog()
  if self.dialog ~= nil then
    return true
  end
  return false
end

function Window:hasMenu()

  if #self.menuItems ~= 0 then
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

function Window:onUp()
  if self:hasMenu() then
    self.currMenuItem = math.max(1, self.currMenuItem - 1) 
  end
end

function Window:onRight()
end

function Window:onDown()
  if self:hasMenu() then
    self.currMenuItem = math.min(#self.menuItems, self.currMenuItem + 1) 

  end
end

function Window:onLeft()
end

function Window:onOk()

  if self:hasMenu() then
    if self.menuItems[self.currMenuItem].callback ~= nil then
      self.menuItems[self.currMenuItem].callback()
    end
  elseif self:hasDialog() then
    if self:isDismissable() then
      self:dismiss()
    end
  end

end

function Window:onCancel()
  if self:isDismissable() then
    self:dismiss()
  end

end

function Window:render()

  ui.renderWindow(self.x, self.y, self.w, self.h)

  if (self.dialog ~= nil) then

    local x = self.x + self.margins.x
    local y = self.y + self.margins.x

    ui.renderMenuItem(self.dialog.text, x, y)

  end

  for i, menuItem in ipairs(self.menuItems) do

    local x = self.x + self.margins.x
    local y = self.y + self.margins.x

    if (self.currMenuItem == i) then
      ui.renderMenuItem('-' .. menuItem.text, x, y +((i-1)* 8));
    else
      ui.renderMenuItem(menuItem.text, x, y +((i-1)* 8));
    end


  end

end

return Window
