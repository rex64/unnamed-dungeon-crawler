--//////////////////////////////////////////////////////////////////////
--************************
--ChangeFloorEvent
--************************

ChangeFloorEvent = {}
ChangeFloorEvent.__index = ChangeFloorEvent
setmetatable(ChangeFloorEvent, {__index = Event})

function ChangeFloorEvent.new(floorId, floorNo)
  local self = setmetatable(Event.new(), ChangeFloorEvent)

  self.name = 'ChangeFloorEvent'
  --self.done = false;

  self.floorId = floorId
  self.floorNo = floorNo

  return self
end

function ChangeFloorEvent:update(input, dt)

  print('event - ChangeFloorEvent: ' .. self.floorId .. ' no: ' .. self.floorNo)
  self.done = true;

  if data.dungeons[self.floorId] ~= nil then
    local newFloor = data.dungeons[self.floorId].onCreateFloor(self.floorId, self.floorNo)
    field.setCurrentFloor(newFloor)
  else
    print('floor: ' .. self.floorId .. ' doesn\'t exists')
  end


end

return ChangeFloorEvent
