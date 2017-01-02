local DialogWindow = require('ui.DialogWindow')
--//////////////////////////////////////////////////////////////////////
--************************
--ShowDialogEvent
--************************

ShowDialogEvent = {}
ShowDialogEvent.__index = ShowDialogEvent
setmetatable(ShowDialogEvent, {__index = Event})

function ShowDialogEvent.new(text)
  local self = setmetatable(Event.new(), ShowDialogEvent)

  self.name = 'ShowDialogEvent'
  self.done = false;
  self.text = text
  self.dialogWindow = nil 

  return self
end

function ShowDialogEvent:update(input, dt)

  print('event - ShowDialogEvent')
  --self.done = true;

  --print('Dialog :' .. type(Dialog))

  if self.dialogWindow == nil then 
    self.dialogWindow = DialogWindow.new(0, 80, 31, 7, self.text)
    ui.addWindow(self.dialogWindow)
  elseif self.dialogWindow:wasDismissed() == true then
    self.done = true;
  end  
  
end

return ShowDialogEvent
