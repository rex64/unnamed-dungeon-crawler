require('mobdebug').on()
--//////////////////////////////////////////////////////////////////////
--************************
--Floor
--************************

local FloorConsts = require('field.FloorConsts')

Floor = {}
Floor.__index = Floor

function Floor.new(dungeonId, floorNo, width, height, fillTile, name)

  local self = setmetatable({}, Floor)

  self.dungeonId = dungeonId
  self.floorNo = floorNo
  self.width = width
  self.height = height
  self.name = name or 'Floor'
  self.entities = {}
  self.tilesEntities = {}
  self.player = nil
  self.tileCollisions = {}
  self.tileSets = {}
  self.interactableEntity = nil

  for i = 1, width * height do table.insert(self.tileCollisions, 0) end
  for i = 1, width * height do table.insert(self.tileSets, fillTile) end 

  return self
end

function Floor:onInput(input)

  if self.player ~= nil then

    if input.up or input.right or input.down or input.left then

      self:onPlayerMove(input)

    elseif input.ok then
      if (self.interactableEntity ~= nil) then
        data.entities[self.interactableEntity.id].onInteract(self.interactableEntity, self.player)
      end
    elseif input.cancel then

    end

  end

end

function Floor:update(dt) 
end

function Floor:render()
  self:renderTiles()
  self:renderEntities()

  if (self.interactableEntity ~= nil) then
    engine.renderTextLine('you can interact with ' .. self.interactableEntity.name, 0, 0);
  end

end

function Floor:onPlayerMove(input)

  local playerPos = self:toXY(self.player.tileId)

  if input.up then

    playerPos.y = playerPos.y - 1
    self.player.facing = FloorConsts.facing.up

  elseif input.right then

    playerPos.x = playerPos.x + 1
    self.player.facing = FloorConsts.facing.right

  elseif input.down then

    playerPos.y = playerPos.y + 1
    self.player.facing = FloorConsts.facing.down

  elseif input.left then

    playerPos.x = playerPos.x - 1
    self.player.facing = FloorConsts.facing.left

  end

  --collisions checking
  if self:checkIfTileIsWalkable(self:to1D(playerPos.x, playerPos.y)) then

    self:moveEntity(self.player, self:to1D(playerPos.x, playerPos.y))

  end

  --check interactable entities
  do
    local entityPos = self:toXY(self.player.tileId)

    if self.player.facing == FloorConsts.facing.up    then entityPos.y = entityPos.y - 1 end
    if self.player.facing == FloorConsts.facing.right then entityPos.x = entityPos.x + 1 end
    if self.player.facing == FloorConsts.facing.down  then entityPos.y = entityPos.y + 1 end
    if self.player.facing == FloorConsts.facing.left  then entityPos.x = entityPos.x - 1 end

    local tileEntityIndex = self:to1D(entityPos.x, entityPos.y)

    if self.tilesEntities[tileEntityIndex] ~= nil then
      print ('you can interact with ' .. self.tilesEntities[tileEntityIndex].name)
      self.interactableEntity = self.tilesEntities[tileEntityIndex]

    else
      self.interactableEntity = nil
    end


  end



end

function Floor:renderEntities()

  local cameraOffsetX = 0
  local cameraOffsetY = 0 

  if self.player ~= nil then

    local playerPos = self:toXY(self.player.tileId)

    cameraOffsetX = (-16 * playerPos.x) + (16*7)
    cameraOffsetY = (-16 * playerPos.y) + (16*4)

  end


  for i, entity in ipairs(self.entities) do

    local entityPos = self:toXY(entity.tileId)

    engine.renderSpriteSheet(
      engine.getEntitySpriteId(entity.id),
      entityPos.x * 16 + cameraOffsetX,
      entityPos.y * 16 + cameraOffsetY,
      entity.facing
    )


  end

end

function Floor:renderTiles()

  local cameraOffsetX = 0
  local cameraOffsetY = 0 

  if self.player ~= nil then

    local playerPos = self:toXY(self.player.tileId)

    cameraOffsetX = (-16 * playerPos.x) + (16*7)
    cameraOffsetY = (-16 * playerPos.y) + (16*4)

  end

  for i, tileResId in ipairs(self.tileSets) do

    local index = i - 1

    local tilePos = self:toXY(index)

    engine.renderTile(tileResId, tilePos.x * 16 + cameraOffsetX, tilePos.y * 16 + cameraOffsetY)

  end


end

function Floor:addEntity(entity, tileId)
  entity.floor = self
  table.insert(self.entities, entity)
  entity.tileId = tileId
  self.tilesEntities[tileId] = entity
end

function Floor:removeEntity(entity)

  local entityTileId = entity.tileId
  local entityIndex = nil
  

  for i, e in ipairs(self.entities) do

    if (e == entity) then entityIndex = i end

  end

  if (entityIndex ~= nil) then

    table.remove(self.entities, entityIndex)
  end
  
  self.tilesEntities[entityTileId] = nil

end

function Floor:moveEntity(entity, tileId)

  --remove entity from old tile
  self.tilesEntities[entity.tileId] = nil

  --add entity to new tile
  entity.tileId = tileId
  self.tilesEntities[tileId] = entity

  local xy = self:toXY(entity.tileId)
  print(entity.name .. ' moves to ' .. entity.tileId .. ' - x:' .. xy.x .. ' y:' .. xy.y)

end


function Floor:setPlayerEntity(entity)
  self.player = entity
end

function Floor:toXY(tileId)

  local x = math.floor(tileId % self.width)
  local y = math.floor( (tileId / self.width) % self.height )

  return {x = x, y = y}


end

function Floor:to1D(x, y)

  return math.floor(x + self.width * y)

end

function Floor:checkIfTileIsWalkable(tileId)

  local tileIndex       = tileId + 1
  local tileEntityIndex = tileId


  if self.tileCollisions[tileIndex] == 1 and self.tilesEntities[tileEntityIndex] == nil then
    return true
  end


  return false

end

function Floor:setTile(x, y, tileSprite, collision)

  local index = self:to1D(x, y)

  self.tileCollisions[index+1] = collision
  self.tileSets[index+1] = tileSprite

end

function Floor:addRoom(x, y, w, h, tilePass, tileCollision)

  for j = y, y + h do

    for i = x, x + w do

      if j == y         then self:setTile(i, j, tileCollision, 0)
      elseif j == (y + h) then self:setTile(i, j, tileCollision, 0)
      elseif i == x     then self:setTile(i, j, tileCollision, 0) 
      elseif i == x + w then self:setTile(i, j, tileCollision, 0)
      else self:setTile(i, j, tilePass, 1)
      end
      --
    end


  end


end

return Floor
