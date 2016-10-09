package.path = package.path 
  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?.lua"
  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/lualibs/?/?.lua"

package.cpath = package.cpath 
  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/?.dylib"
  .. ";/Applications/ZeroBraneStudio.app/Contents/ZeroBraneStudio/bin/clibs53/socket/?.dylib"

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