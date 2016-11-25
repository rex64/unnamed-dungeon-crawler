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
    local menuItem = MenuItem.new("test1", 0, 0, 
      function () 
        print('menu callback')
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
    win.trevi = {};
    local a = win.trevi;
    
    table.insert(win.menuitems, menuItem);
    table.insert(ui.windows, win);
    
    --menuItem:onSelect();

end

foo()

print('main - ok');
