--//////////////////////////////////////////////////////////////////////
--************************
--FloorEntity
--************************

local FloorConsts = require('field.FloorConsts')

FloorEntity = {}
FloorEntity.__index = FloorEntity

function FloorEntity.new(id, name)
  local self = setmetatable({}, FloorEntity)
  self.id = id
  self.name = name or 'FloorEntity'
  self.floor = nil
  self.tileId = nil
  self.facing = FloorConsts.facing.up

  return self
end

function FloorEntity:onInput(input)
end

function FloorEntity:update(dt) 
end

function FloorEntity:render()
end

function FloorEntity:setValue(key, value)

  if type(key) ~= 'string' then error('the key must be a string') end
  if type(value) ~= 'string' and type(value) ~= 'number' then error('the value must be a string or a number') end

  if self.userdata == nil then self.userdata = {} end

  self.userdata[key] = value

end

function FloorEntity:getValue(key)

  if type(key) ~= 'string' then error('the key must be a string') end

  if self.userdata == nil then self.userdata = {} end

  return self.userdata[key]

end


return FloorEntity
