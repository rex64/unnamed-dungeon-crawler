local Window = require('ui.Window')
local ChoiceMenu = require('ui.ChoiceMenu')

--//////////////////////////////////////////////////////////////////////
--************************
--ChoiceWindow
--************************

ChoiceWindow = {}
ChoiceWindow.__index = ChoiceWindow
setmetatable(ChoiceWindow, {__index = Window})

function ChoiceWindow.new(x, y, w, h, newChoiceMenu)

  local self = Window.new(x, y, w, h, false)
  self = setmetatable(self, ChoiceWindow)

  self.name = 'ChoiceWindow'

  self:addChoiceMenu(newChoiceMenu)

  return self
end

function ChoiceWindow:onInput(input)

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

  elseif input.cancel then
    if self:isDismissable() then
      self:dismiss()
    end
  end

end

function ChoiceWindow:render()

  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  self.choiceMenu:render(x, y)


end

function ChoiceWindow:addChoiceMenu(newChoiceMenu)

  newChoiceMenu.win = self
  self.choiceMenu = newChoiceMenu

end

function ChoiceWindow:addMenuItem(newMenuItem)

  self.choiceMenu:addMenuItem(newMenuItem)

end


return ChoiceWindow
