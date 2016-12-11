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
  --newEvent.onDone = function() end;

  
  return newEvent
end

--function Event:update(input, dt) end

function Event:isDone()
  return self.done
end

function Event:onDone() end

--//////////////////////////////////////////////////////////////////////
--************************
--CompositeEvent
--************************

CompositeEvent = {}
CompositeEvent.__index = CompositeEvent

function CompositeEvent.new(name, i)
  local self = setmetatable({}, CompositeEvent)
  self.events = {}

  return self
end

function CompositeEvent:addEvent(e)
  table.insert(self.events, e)
end

function CompositeEvent:update(input, dt) 

  for i, event in ipairs(self.events) do
    if event:isDone() == false then
      event:update(input, dt)
    end

  end

end

function CompositeEvent:isDone()
  local done = true

  for i, event in ipairs(self.events) do

    done = done and event:isDone()

  end

  return done

end

function CompositeEvent:onDone() end


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
      event.onDone()
      table.remove(self.events, 1)
    end
    
    
  end
  

end
