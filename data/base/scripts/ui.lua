local MenuItem     = require('ui.MenuItem')
local ChoiceMenu   = require('ui.ChoiceMenu')
local ChoiceWindow = require('ui.ChoiceWindow')
local StatusWindow = require('ui.StatusWindow')
local EquipWindow  = require('ui.EquipWindow')


ui = {}

--UI stuff
if(ui ~= nil) then

--[[
  ui.UP     = 0
  ui.RIGHT  = 1
  ui.DOWN   = 2
  ui.LEFT   = 3
  ui.OK     = 4
  ui.CANCEL = 5
  ui.ESC    = 6
]]--

  ui.windows = {};
  ui.addWindow = function(newWindow)

    table.insert(ui.windows, newWindow)

  end

  ui.onInput = function(input)

    local topWindowIndex = #ui.windows;
    local topWindow = ui.windows[topWindowIndex]

    topWindow:onInput(input)

  end

  ui.update = function() end

  ui.render = function()

    for i, window in ipairs(ui.windows) do

      window:render()

    end

  end

  ui.openMenu = function()

    local menuItem1 = MenuItem.new("Items", function() end)
    local menuItem2 = MenuItem.new("Skills", function() end)
    local menuItem3 = MenuItem.new("Equip", function() 
        local win = EquipWindow.new(0, 0, 49, 27)
        ui.addWindow(win)
        
        end)

    --StatusWindow
    local menuItem4 = MenuItem.new("Status", function() 
        local win = StatusWindow.new(0, 0, 49, 27)
        ui.addWindow(win)

      end)

    local menuItem5 = MenuItem.new("Config", function() print('show Config menu') end)
    local menuItem6 = MenuItem.new("Quit", function() print('show quit menu') end)

    local choiceMenu = ChoiceMenu.new()

    choiceMenu:addMenuItem(menuItem1)
    choiceMenu:addMenuItem(menuItem2)
    choiceMenu:addMenuItem(menuItem3)
    choiceMenu:addMenuItem(menuItem4)
    choiceMenu:addMenuItem(menuItem5)
    choiceMenu:addMenuItem(menuItem6)

    local win = ChoiceWindow.new(180, 8, 8, 8, choiceMenu)
    win:setDismissable(true)
    ui.addWindow(win)

  end

  ui.closeMenu = function()
    print('close menu')  
    ui.windows = {}
  end

  ui.isMainMenuOpen = function()
    if #ui.windows ~= 0 then 
      return true
    else
      return false
    end
  end

end