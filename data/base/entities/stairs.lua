data.entities['base.entities.stairs'] = {
  
  onInteract = function(entity, player)
    
    local ShowDialogEvent = require('ui.events.ShowDialogEvent')
    print("stairs - onInteract")
    --game.eventManager:addEvent(ShowDialogEvent.new('This is a dialog.'))
    game.eventManager:addEvent(ChangeFloorEvent.new('base.dungeons.dungeon1', field.currentFloor.floorNo + 1):debug('main.lua 32'))
  end
  
}
