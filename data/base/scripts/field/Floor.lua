require('mobdebug').on()
--//////////////////////////////////////////////////////////////////////
--************************
--Floor
--************************

Floor = {}
Floor.__index = Floor

function Floor.new(dungeonId, width, height, name)

  local self = setmetatable({}, Floor)

  self.dungeonId = dungeonId
  self.width = width
  self.height = height
  self.name = name or 'Floor'
  self.entities = {}
  self.tilesEntities = {}
  self.player = nil
  self.tileCollisions = nil
  self.tileSets = nil

  return self
end

function Floor:onInput(input)


  if self.player ~= nil then

    local playerPos = self:toXY(self.player.tileId)

    if input.up then

      playerPos.y = playerPos.y - 1

    elseif input.right then

      playerPos.x = playerPos.x + 1

    elseif input.down then

      playerPos.y = playerPos.y + 1

    elseif input.left then

      playerPos.x = playerPos.x - 1

    elseif input.ok then

    elseif input.cancel then

    end

    if self:checkIfTileIsWalkable(self:to1D(playerPos.x, playerPos.y)) then
      self:moveEntity(self.player, self:to1D(playerPos.x, playerPos.y))
    end

    --self.player:setEntityTile(self:to1D(playerPos.x, playerPos.y))

  end

end

function Floor:update(dt) 
end

function Floor:render()
  self:renderTiles()
  self:renderEntities()
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

--[[
for (auto kv : StageManager::manager->currStage->entities) {
	
		if (Entity *entity = kv.second) {

			int x = entity->tileId % StageManager::manager->currStage->arrayWidth;
			int y = (entity->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

			//Player-->Game
			SDL_Rect pos = { x * 16 + cameraOffsetX, y * 16 + cameraOffsetY, 16, 16 };
			SDL_Rect rez{ 0 + (16 * entity->facing),0 (16 * entity->facing),16,16 };

			std::string spriteID = ((FieldEntityData*)(ResourceManager::manager->entityDatas[entity->entityDataID]->data))->spritesheet;

			SDL_BlitSurface(ResourceManager::manager->getSprite(spriteID), &rez, game, &pos);
			
		};
	}
]]--

    local entityPos = self:toXY(entity.tileId)



    engine.renderSprite(
      engine.getEntitySpriteId(entity.id),
      entityPos.x * 16 + cameraOffsetX,
      entityPos.y * 16 + cameraOffsetY
    )


  end

end

function Floor:renderTiles()

  --[[
  int cameraOffsetX = 0;
	int cameraOffsetY = 0;
  
  ]]--

  local cameraOffsetX = 0
  local cameraOffsetY = 0 

--[[
	if (Entity *player = StageManager::manager->currStage->player) {
	
		Point playerPos = StageManager::manager->currStage->toXY(player->tileId);

		cameraOffsetX = (-16 * playerPos.x) + (16*7);
		cameraOffsetY = (-16 * playerPos.y) + (16*4);
	}
  
  ]]--

  if self.player ~= nil then

    local playerPos = self:toXY(self.player.tileId)

    cameraOffsetX = (-16 * playerPos.x) + (16*7)
    cameraOffsetY = (-16 * playerPos.y) + (16*4)

  end

  --[[
	//render tiles
	for (size_t i = 0; i < StageManager::manager->currStage->arrayWidth * StageManager::manager->currStage->arrayHeight; i++)
	{
		int x = i % StageManager::manager->currStage->arrayWidth;
		int y = (i / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

		

		SDL_Rect pos = { x * 16 + cameraOffsetX, y * 16 + cameraOffsetY, 16, 16 };

		SDL_BlitSurface(
			ResourceManager::manager->getTile(StageManager::manager->currStage->getTile(i).tileResID),
			NULL,
			game,
			&pos
		);
	}
  ]]--

  for i, tileResId in ipairs(self.tileSets) do

    local index = i - 1

    local tilePos = self:toXY(index)

    --local tilePos = {x=1, y=1}

    engine.renderTile(tileResId, tilePos.x * 16 + cameraOffsetX, tilePos.y * 16 + cameraOffsetY)

  end


end

function Floor:addEntity(entity, tileId)
  entity.floor = self
  table.insert(self.entities, entity)
  entity.tileId = tileId
  self.tilesEntities[tileId] = entity
end

function Floor:moveEntity(entity, tileId)

  --remove entity from old tile
  self.tilesEntities[entity.tileId] = nil

  --add entity to new tile
  entity.tileId = tileId
  self.tilesEntities[tileId] = entity

  print(entity.name .. ' moves to ' .. entity.tileId)
  --self.tilesEntities[tileId] = entity
  --table.insert(self.entities, entity)
end


function Floor:setPlayerEntity(entity)
  self.player = entity
end

function Floor:toXY(tileId)
  --[[
  int x = i % arrayWidth;
	int y = (i / arrayWidth) % arrayHeight;

	return Point{ x,y };
  ]]--

  local x = math.floor(tileId % self.width)
  local y = math.floor( (tileId / self.width) % self.height )

  return {x = x, y = y}


end

function Floor:to1D(x, y)

--[[
  int Stage::to1D(int x, int y) {
      
    return x + arrayWidth*y;
  }
]]--

  return math.floor(x + self.width * y)

end

function Floor:checkIfTileIsWalkable(tileId)
  --[[
    //TODO: http://stackoverflow.com/questions/17153038/unordered-map-insert-with-void-as-value-is-not-working-properly
	if (getTile(tileID).tileType == Floor && tileEntities[tileID] == nullptr) {
		return true;
	}

	return false;
    ]]--

  local tileIndex       = tileId + 1
  local tileEntityIndex = tileId


--  if self.tileCollisions[tileIndex] == 1 and self.tilesEntities[tileIndex] == nil then
  if self.tileCollisions[tileIndex] == 1 and self.tilesEntities[tileEntityIndex] == nil then
    return true
  end
  
  --local blockingEntity = self.tilesEntities[tileEntityIndex]
  --print(blockingEntity.name .. ' blocks ' .. tileIndex)

  return false

end

return Floor