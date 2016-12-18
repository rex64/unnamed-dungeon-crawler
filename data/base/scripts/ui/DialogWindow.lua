local Window = require('ui.Window')
local Dialog = require('ui.Dialog')

--//////////////////////////////////////////////////////////////////////
--************************
--DialogWindow
--************************

DialogWindow = {}
DialogWindow.__index = DialogWindow
setmetatable(DialogWindow, {__index = Window})

function DialogWindow.new(x, y, w, h, text)
  
  local self = setmetatable({}, DialogWindow)

  self.x = x 
  self.y = y 
  self.w = w 
  self.h = h 
  self.margins = {x=12, y=0}

  self.choiceMenu = nil
  self.dialog = nil

  self.dismissable = false

  self.name = 'DialogWindow'
  
  self:addDialog(Dialog.new(text))

  return self
end

function DialogWindow:onInput(input)
  
end

return DialogWindow
