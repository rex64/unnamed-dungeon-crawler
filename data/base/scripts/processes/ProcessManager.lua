--//////////////////////////////////////////////////////////////////////
--************************
--ProcessManager
--************************
ProcessManager = {}
ProcessManager.__index = ProcessManager

function ProcessManager.new(name, i)
  local newProcessManager = {}
  setmetatable(newProcessManager, ProcessManager)

  newProcessManager.processes = {}

  return newProcessManager
end

function ProcessManager:addProcess(p)
  print('[ProcessManager] added ' .. p:toString())
  table.insert(self.processes, p)
end

function ProcessManager:update(input, dt)

  local i=1
  while i <= #self.processes do

    local process = self.processes[i]
    process:update(dt)

    if process:isDone() then
      table.remove(self.processes, i)
    else
      i = i + 1
    end
  end

end

return ProcessManager
