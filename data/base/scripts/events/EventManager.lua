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
  print('added ' .. e:toString())
  table.insert(self.events, e)
end

function EventManager:update(input, dt)

  if #self.events > 0 then

    local event = self.events[1]
    event:update(input, dt)

    if event:isDone() then
      print('done ' .. event:toString())
      event.onDone()
      table.remove(self.events, 1)
    end


  end


end

return EventManager
