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
  self.displayCursor = false

  self:addDialog(Dialog.new(text))

  self:setDismissable(true)

  return self
end

function DialogWindow:onInput(input)

  if game.wasOkPressedThisFrame(input) == true and self:isDismissable() and self.dialog:isAnimationEnded() then
    self:dismiss()
  elseif game.wasOkPressedThisFrame(input) and self.dialog:isAnimationEnded() == false then
    self.dialog:setAnimationSpeed(1)
  end


end

function DialogWindow:update(dt)

  self.dialog:update(dt)

  if self.dialog:isAnimationEnded() then

    if self.timer == nil then self.timer = 0 end
    if self.displayCursor == nil then self.displayCursor = false end

    if self.timer >= 100 then
      self.displayCursor = not self.displayCursor
      self.timer = 0
    end

    self.timer = self.timer + dt

  end

end

function DialogWindow:render()

  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  self.dialog:render(x, y)

  if self.displayCursor then
    engine.renderTextLine('O', x, y - 4)
  end

end

function DialogWindow:addDialog(newDialog)

  newDialog.win = self
  self.dialog = newDialog

end

return DialogWindow
