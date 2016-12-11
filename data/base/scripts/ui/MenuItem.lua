--************************
--MenuItem
--************************
MenuItem = {}
MenuItem.__index = MenuItem

function MenuItem.new(text, callback)
  local menuItem = {}
  setmetatable(menuItem, MenuItem)
  menuItem.text = text
  menuItem.callback = callback  

  return menuItem
end

return MenuItem
