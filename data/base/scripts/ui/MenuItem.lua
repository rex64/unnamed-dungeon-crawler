--************************
--MenuItem
--************************
MenuItem = {}
MenuItem.__index = MenuItem

function MenuItem.new(text, callback)
  local self = setmetatable({}, MenuItem)
  self.text = text
  self.callback = callback  

  return self
end

return MenuItem
