--************************
--Dialog
--************************

Dialog = {}
Dialog.__index = Dialog

function Dialog.new(text)
  local newDialog = {}
  setmetatable(newDialog, Dialog)
  newDialog.text = text

  return newDialog
end

return Dialog
