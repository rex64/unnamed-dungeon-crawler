--//////////////////////////////////////////////////////////////////////
--************************
--FloorEntity
--************************

FloorEntity = {}
FloorEntity.__index = FloorEntity

function FloorEntity.new(id, name)
  local self = setmetatable({}, FloorEntity)
  self.id = id
  self.name = name or 'FloorEntity'
  self.floor = nil
  self.tileId = nil

  return self
end

function FloorEntity:onInput(input)
end

function FloorEntity:update(dt) 
end

function FloorEntity:render()
end

--function FloorEntity:setEntityTile(tileId)
--  self.tileId = tileId
--end


return FloorEntity