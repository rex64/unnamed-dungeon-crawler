--//////////////////////////////////////////////////////////////////////
--************************
--DialogTextAnimProcess
--************************

DialogTextAnimProcess = {}
DialogTextAnimProcess.__index = DialogTextAnimProcess
setmetatable(DialogTextAnimProcess, {__index = Process})

function DialogTextAnimProcess.new(dialogWin)
  local self = setmetatable(Process.new(), DialogTextAnimProcess)

  self.name = 'DialogTextAnimProcess' .. ' - ' .. tostring(desc)
  self.dialogWindow = dialogWin

  return self
end

function DialogTextAnimProcess:update(input, dt)

  print('[Process] DialogTextAnimProcess')
  
  self.dialogWindow:update(dt)
  
  if self.dialogWindow:wasDismissed() == true then
    self.done = true;
  end
  
end

return DialogTextAnimProcess
