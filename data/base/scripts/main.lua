package.path = package.path 
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?.lua"
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?/?.lua"

.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\lualibs\\?.lua"
.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\lualibs\\?\\?.lua"

package.cpath = package.cpath 
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/?.dylib"
--  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/socket/?.dylib"

.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\bin\\clibs53\\?.dll"
.. ";C:\\Program Files (x86)\\ZeroBraneStudio\\bin\\clibs53\\socket\\?.dll"

require('mobdebug').start()

print("main");


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

  --local newMenuItem = {text=text, callback=callback}

  table.insert(self.menuItems, newMenuItem)
  --return newMenuItem
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

--************************
--Dialog
--************************

Dialog = {}
Dialog.__index = Dialog

function Dialog.new(text)
  local newDialog = {}
  setmetatable(newDialog, Dialog)
  newDialog.text = text

  return newDialog
end


--UI stuff
if(ui ~= nil) then

  ui.UP     = 0
  ui.RIGHT  = 1
  ui.DOWN   = 2
  ui.LEFT   = 3
  ui.OK     = 4
  ui.CANCEL = 5
  ui.ESC    = 6

  ui.windows = {};
  ui.addWindow = function(newWindow)

    table.insert(ui.windows, newWindow)

  end

  ui.update = function(button)

    if #ui.windows == 0 then

      if button == ui.ESC then

        ui.openMenu()
        return true

      end

    else
      local topWindowIndex = #ui.windows;
      local topWindow = ui.windows[topWindowIndex]

      if button == ui.UP then
        topWindow:onUp()

      elseif button == ui.RIGHT then
        topWindow:onRight()

      elseif button == ui.DOWN then
        topWindow:onDown()

      elseif button == ui.LEFT then
        topWindow:onLeft()

      elseif button == ui.OK then
        topWindow:onOk()

      elseif button == ui.CANCEL then
        topWindow:onCancel()
        --[[
        table.remove(ui.windows, topWindowIndex)
        ]]--
      elseif button == ui.ESC then

        ui.closeMenu()

      end

      return true
    end

    return false
  end

  ui.render = function()

    for i, window in ipairs(ui.windows) do

      window:render()

    end

  end

  ui.openMenu = function()

    local win = Window.new(16, 16, 8, 8)

    local menuItem1 = MenuItem.new("equip", function() 

        local win = Window.new(32, 32, 8, 8)

        local menuItem1 = MenuItem.new("lol1", function() print('show equip menu') end)
        local menuItem2 = MenuItem.new("lol2", function() print('show equip menu') end)
        local menuItem3 = MenuItem.new("lol3", function() print('show equip menu') end)

        win:addMenuItem(menuItem1)
        win:addMenuItem(menuItem2)
        win:addMenuItem(menuItem3)

        ui.addWindow(win)

      end
    )
    local menuItem2 = MenuItem.new("status", function() print('show equip menu') end)
    local menuItem3 = MenuItem.new("save", function() print('show save menu') end)
    local menuItem4 = MenuItem.new("quit", function() print('show quit menu') end)


    win:addMenuItem(menuItem1)
    win:addMenuItem(menuItem2)
    win:addMenuItem(menuItem3)
    win:addMenuItem(menuItem4)


    ui.addWindow(win)

  end

  ui.closeMenu = function()
    print('close menu')  
    ui.windows = {}
  end



end




print('main - ok');
