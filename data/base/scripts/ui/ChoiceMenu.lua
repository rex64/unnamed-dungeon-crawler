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

function ChoiceMenu:onInput(input)

  if input.down then

    self.currMenuItem = math.min(#self.menuItems, self.currMenuItem + 1) 

  elseif input.up then
    self.currMenuItem = math.max(1, self.currMenuItem - 1) 
  elseif input.ok then
    if self.menuItems[self.currMenuItem].callback ~= nil then
      self.menuItems[self.currMenuItem].callback()
    end
  end



  --[[
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
  ]]--
end

function ChoiceMenu:update(dt)

end

function ChoiceMenu:render(x, y)

  for i, menuItem in ipairs(self.menuItems) do

    if (self.currMenuItem == i) then
      engine.renderTextLine('-' .. menuItem.text, x, y +((i-1)* 8));
    else
      engine.renderTextLine(menuItem.text, x, y +((i-1)* 8));
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
