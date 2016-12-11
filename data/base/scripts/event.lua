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
  
  return newEvent
end

--function Event:update(input, dt) end

function Event:isDone()
  return self.done
end


--//////////////////////////////////////////////////////////////////////
--************************
--EventManager
--************************
EventManager = {}
EventManager.__index = EventManager

function EventManager.new(name, i)
  local newEventManager = {}
  setmetatable(newEventManager, EventManager)

  newEventManager.events = {}

  return newEventManager
end

function EventManager:addEvent(e)
  table.insert(self.events, e)
end

function EventManager:update(input, dt)

  if #self.events > 0 then
  
    local event = self.events[1]
    event:update(input, dt)
    
    if event:isDone() then
        table.remove(self.events, 1)
    end
    
    
  end
  

end
