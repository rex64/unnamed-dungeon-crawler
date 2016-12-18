local DialogWindow = require('ui.DialogWindow')
--//////////////////////////////////////////////////////////////////////
--************************
--ShowDialogEvent
--************************

ShowDialogEvent = {}
ShowDialogEvent.__index = ShowDialogEvent
setmetatable(ShowDialogEvent, {__index = Event})

function ShowDialogEvent.new(text)
  local self = setmetatable({}, ShowDialogEvent)

  self.name = 'ShowDialogEvent'
  self.done = false;
  self.text = text

  return self
end

function ShowDialogEvent:update(input, dt)

  print('event - ShowDialogEvent')
  self.done = true;

  --print('Dialog :' .. type(Dialog))

  local newWin = DialogWindow.new(0, 80, 31, 7, self.text)
  ui.addWindow(newWin)
end

return ShowDialogEvent
