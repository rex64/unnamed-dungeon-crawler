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

function Window.new(x, y, w, h)
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
        topWindow.currMenuItem = math.max(1, topWindow.currMenuItem - 1) 

      elseif button == ui.RIGHT then

      elseif button == ui.DOWN then
        topWindow.currMenuItem = math.min(#topWindow.menuItems, topWindow.currMenuItem + 1) 

      elseif button == ui.LEFT then

      elseif button == ui.OK then
        if topWindow.menuItems[topWindow.currMenuItem].callback ~= nil then
          topWindow.menuItems[topWindow.currMenuItem].callback()
        end

      elseif button == ui.CANCEL then
        table.remove(ui.windows, topWindowIndex)

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
