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
  newEvent.debugString = ''
  --newEvent.onDone = function() end;


  return newEvent
end

--function Event:update(input, dt) end

function Event:isDone()
  return self.done
end

function Event:onDone() end

function Event:debug(debugString) 
  self.debugString = debugString
  return self
end

function Event:toString() 

  if self.debugString == nil then 
   
    print('NO') 
     return self.name .. ' - ' --.. self.debugString
  else
    return self.name .. ' - ' .. self.debugString

  end


end

return Event