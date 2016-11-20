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
    
    table.insert(ui.windows, MyLib.MakeObj(1,1))
    table.insert(ui.windows, MyLib.MakeObj(8,8))
    table.insert(ui.windows, MyLib.MakeObj(8,16))
    table.insert(ui.windows, MyLib.MakeObj(16,8))


end

foo()

print('main - ok');
