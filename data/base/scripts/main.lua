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

print(omar);
print(omar.x);
print(omar.y);

t0 = "data.base.tiles.tile00"
t1 = "data.base.tiles.tile01"

a = {
  t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t0, t1,
  t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1, t1,
}

for i,v in ipairs(a) do 
  field.setTile(i-1, v)
end