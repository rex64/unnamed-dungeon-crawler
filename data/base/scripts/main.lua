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

print(Game);

omar = {
  
  x = 10,
  y = 20
  
}

function foo()
    
    --win
    local win = Window.new(1,1);
    win.menuitems = {}
    
    
    local menuItem1 = MenuItem.new("menu1", 0, 0, 
      function () 
        print('menu1 callback')
      end
    );
    
    local menuItem2 = MenuItem.new("menu2", 0, 16, 
      function () 
        print('menu2 callback')
      end
      );

  --[[
    win:addMenuItem("test1", 0, 0, 
      function () 
        print('menu callback')
      end
      );
    ]]--
    
   -- Window.omar = {};
    --win.trevi = 39;
    --print(win.trevi)
    --print(win.omar)
    
    table.insert(win.menuitems, menuItem1);    
    table.insert(win.menuitems, menuItem2);

    table.insert(ui.windows, win);
    
    --menuItem:onSelect();

end

foo()

print('main - ok');
