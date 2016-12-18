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

  local self = Window.new(x, y, w, h, false)
  self = setmetatable(self, DialogWindow)

  self.name = 'DialogWindow'

  self:addDialog(Dialog.new(text))

  return self
end

function DialogWindow:onInput(input)

  if input.ok == true then
    self:dismiss()
  end
  
end

function DialogWindow:render()
  
  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  self.dialog:render(x, y)

end

function DialogWindow:addDialog(newDialog)

  newDialog.win = self
  self.dialog = newDialog

end

return DialogWindow
