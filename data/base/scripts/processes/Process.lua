--//////////////////////////////////////////////////////////////////////
--************************
--Process
--************************

Process = {}
Process.__index = Process

function Process.new(name, i)
  local self = {}
  setmetatable(self, Process)

  self.done = false;  
  self.name = 'Process'
  self.debugString = ''

  return newProcess
end

--function Process:update(input, dt) end

function Process:isDone()
  return self.done
end

function Process:onDone() end

function Process:debug(debugString) 
  self.debugString = debugString
  return self
end

function Process:toString() 

  if self.debugString == nil then 
   
    print('NO') 
     return self.name .. ' - ' --.. self.debugString
  else
    return self.name .. ' - ' .. self.debugString

  end

end

return Process
