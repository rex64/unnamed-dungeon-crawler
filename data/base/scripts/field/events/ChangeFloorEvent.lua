--//////////////////////////////////////////////////////////////////////
--************************
--ChangeFloorEvent
--************************

ChangeFloorEvent = {}
ChangeFloorEvent.__index = ChangeFloorEvent
setmetatable(ChangeFloorEvent, {__index = Event})

function ChangeFloorEvent.new(floorId, floorNo)
  local self = setmetatable({}, ChangeFloorEvent)

  self.name = 'ChangeFloorEvent'
  self.done = false;
  
  self.floorId = floorId
  self.floorNo = floorNo

  return self
end

function ChangeFloorEvent:update(input, dt)

  print('event - ChangeFloorEvent: ' .. self.floorId .. ' no: ' .. self.floorNo)
  self.done = true;
  
  local newFloor = data.dungeons[self.floorId].onCreateFloor(self.floorNo)
  field.setCurrentFloor(newFloor)
end

return ChangeFloorEvent
