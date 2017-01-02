--//////////////////////////////////////////////////////////////////////
--************************
--ArbitraryFunctionEvent
--************************

ArbitraryFunctionEvent = {}
ArbitraryFunctionEvent.__index = ArbitraryFunctionEvent
setmetatable(ArbitraryFunctionEvent, {__index = Event})

function ArbitraryFunctionEvent.new(func, desc)
  local self = setmetatable(Event.new(), ArbitraryFunctionEvent)

  self.name = 'ArbitraryFunctionEvent' .. ' - ' .. tostring(desc)
  self.done = false
  self.func = func

  return self
end

function ArbitraryFunctionEvent:update(input, dt)

  print('event - ArbitraryFunctionEvent')
  self.done = true
  self.func()
  
end

return ArbitraryFunctionEvent
