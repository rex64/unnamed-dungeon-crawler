data = {}
field = {}
field.setTile = function (id, value)
  print('id: ' .. id ..' value:' .. value)
end

a = {
  1, 1, 1, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0
}

for i,v in ipairs(a) do 
  field.setTile(i-1, v)
end