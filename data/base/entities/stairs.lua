local stairs = {
  
  onInteract = function()
    print("stairs - onInteract")
    local win = Window.new(0, 80, 31, 7)
    local newDialog = Dialog.new('This is a dialog.\nThis is line 2')
    win:addDialog(newDialog)
    win:setDismissable(true)
    ui.addWindow(win)
  end
  
}

data.entities['base.entities.stairs'] = stairs
