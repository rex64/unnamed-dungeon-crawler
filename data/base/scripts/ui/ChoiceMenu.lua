--************************
--ChoiceMenu
--************************
ChoiceMenu = {}
ChoiceMenu.__index = ChoiceMenu

function ChoiceMenu.new(text, callback)
  local self = setmetatable({}, ChoiceMenu)
  
  self.menuItems = {}
  self.currMenuItem = 1 
  
  self.win = nil
  
  return self
end

function ChoiceMenu:update(input, dt)
  
end

function ChoiceMenu:render(x, y)
  
  for i, menuItem in ipairs(self.menuItems) do

    if (self.currMenuItem == i) then
      ui.renderMenuItem('-' .. menuItem.text, x, y +((i-1)* 8));
    else
      ui.renderMenuItem(menuItem.text, x, y +((i-1)* 8));
    end

  end
  
end

function ChoiceMenu:addMenuItem(newMenuItem)

  table.insert(self.menuItems, newMenuItem)

end

function ChoiceMenu:resetMenu()

  self.menuItems = {}

end

return ChoiceMenu
