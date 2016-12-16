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

return FloorEntity
