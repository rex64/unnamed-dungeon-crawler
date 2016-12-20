--//////////////////////////////////////////////////////////////////////
--************************
--CompositeEvent
--************************

CompositeEvent = {}
CompositeEvent.__index = CompositeEvent
setmetatable(CompositeEvent, {__index = Event})

function CompositeEvent.new(name, i)
  local self = setmetatable(Event.new(), CompositeEvent)

  self.events = {}
  self.name = 'CompositeEvent'

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

  if done then 
--    print('CompositeEvent:isDone ') 
  end
  
  return done

end

function CompositeEvent:onDone() 
--  print('CompositeEvent:OnDone')
end

return CompositeEvent