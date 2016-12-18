data.entities['base.entities.stairs'] = {
  
  onInteract = function()
    
    local ShowDialogEvent = require('ui.events.ShowDialogEvent')
    print("stairs - onInteract")
    game.eventManager:addEvent(ShowDialogEvent.new('This is a dialog.'))
  end
  
}
