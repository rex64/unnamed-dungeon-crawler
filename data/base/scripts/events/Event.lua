--//////////////////////////////////////////////////////////////////////
--************************
--Event
--************************

Event = {}
Event.__index = Event

function Event.new(name, i)
  local newEvent = {}
  setmetatable(newEvent, Event)

  newEvent.done = false;  
  newEvent.name = 'Event'
  --newEvent.onDone = function() end;


  return newEvent
end

--function Event:update(input, dt) end

function Event:isDone()
  return self.done
end

function Event:onDone() end

return Event