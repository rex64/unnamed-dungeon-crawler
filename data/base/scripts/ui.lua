local Window      = require('ui.Window')
local MenuItem    = require('ui.MenuItem')
local ChoiceMenu  = require('ui.ChoiceMenu')

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

  ui.onInput = function(button)

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

      elseif button == ui.ESC then

        ui.closeMenu()

      end

      return true
    end

    return false
  end

  ui.update = function() end

  ui.render = function()

    for i, window in ipairs(ui.windows) do

      window:render()

    end

  end

  ui.openMenu = function()

    local win = Window.new(180, 8, 8, 8)

    local menuItem1 = MenuItem.new("Item", function() 

        local win = Window.new(32, 32, 8, 8)

        local menuItem1 = MenuItem.new("lol1", function() print('show equip menu') end)
        local menuItem2 = MenuItem.new("lol2", function() print('show equip menu') end)
        local menuItem3 = MenuItem.new("lol3", function() print('show equip menu') end)

        local choiceMenu = ChoiceMenu.new()

        choiceMenu:addMenuItem(menuItem1)
        choiceMenu:addMenuItem(menuItem2)
        choiceMenu:addMenuItem(menuItem3)

        win:addChoiceMenu(choiceMenu)

        ui.addWindow(win)

      end
    )
    local menuItem2 = MenuItem.new("Equip", function() print('show Equip menu') end)
    local menuItem3 = MenuItem.new("Status", function() print('show Status menu') end)
    local menuItem4 = MenuItem.new("Config", function() print('show Config menu') end)
    local menuItem5 = MenuItem.new("Quit", function() print('show quit menu') end)

    local choiceMenu = ChoiceMenu.new()

    choiceMenu:addMenuItem(menuItem1)
    choiceMenu:addMenuItem(menuItem2)
    choiceMenu:addMenuItem(menuItem3)
    choiceMenu:addMenuItem(menuItem4)

    win:addChoiceMenu(choiceMenu)

    ui.addWindow(win)

  end

  ui.closeMenu = function()
    print('close menu')  
    ui.windows = {}
  end

end