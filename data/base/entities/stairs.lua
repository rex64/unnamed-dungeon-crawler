data.entities['base.entities.stairs'] = {
  
  onInteract = function(entity, player)
    
    local ShowDialogEvent = require('ui.events.ShowDialogEvent')
    print("stairs - onInteract")
    local newFloorId   = entity:getValue('base.entities.stairs.floorId')
    local newFloorNo   = entity:getValue('base.entities.stairs.floorNo')

    game.eventManager:addEvent(ChangeFloorEvent.new(newFloorId, newFloorNo):debug('main.lua 32'))
  end
  
}
