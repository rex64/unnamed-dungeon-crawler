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

--UI stuff
if(ui ~= nil) then
  
  ui.UP     = 0
  ui.RIGHT  = 1
  ui.DOWN   = 2
  ui.LEFT   = 3
  ui.OK     = 4
  ui.CANCEL = 5
  
  ui.windows = {};
  ui.addWindow = function(x, y, w, h)
  
    local newWindow = {x=x, y=y, w=w, h=h}
    newWindow.margins = {x=12, y=0}
    newWindow.menuItems = {}
    newWindow.currMenuItem = 1    
      
    newWindow.addMenuItem = function(text, callback)
    
      local newMenuItem = {text=text, callback=callback}
      
      table.insert(newWindow.menuItems, newMenuItem)
      return newMenuItem
    end
    
      
    table.insert(ui.windows, newWindow)
    return newWindow
  
  end
  
  ui.update = function(button)
  
    print('ui update')
    
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
    end
  
  end

  ui.render = function()
    
    for i, window in ipairs(ui.windows) do
      ui.renderWindow(window.x, window.y, window.w, window.h)
      
      for i, menuItem in ipairs(window.menuItems) do
        
        local x = window.x + window.margins.x
        local y = window.y + window.margins.x
        
        if (window.currMenuItem == i) then
          ui.renderMenuItem('-' .. menuItem.text, x, y +((i-1)* 8));
        else
          ui.renderMenuItem(menuItem.text, x, y +((i-1)* 8));
        end
        
        
      end
      
    end
  
  end

  ui.openMenu = function()
  
    local win2 = ui.addWindow(16, 16, 8, 8)

    win2.addMenuItem("equip", function() print('show equip menu') end)
    win2.addMenuItem("status", function() print('show equip menu') end)
    win2.addMenuItem("close", function() ui.closeMenu() end)
  
  end

  ui.closeMenu = function()
    print('close menu')
  
  
  end
  
  

end




print('main - ok');
