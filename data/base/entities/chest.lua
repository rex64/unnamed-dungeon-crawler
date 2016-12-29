data.entities['base.entities.chest'] = {
  
  onInteract = function(entity, player)
    
    local ShowDialogEvent = require('ui.events.ShowDialogEvent')
    
    local newEquipId   = entity:getValue('base.entities.chest.item')
    local newEquipName = save.getEquipName(newEquipId)
    
    print("chest - onInteract")   
    
    
    save.addEquipToInventory(newEquipId)
    
    game.eventManager:addEvent(ShowDialogEvent.new('You found a ' .. newEquipName))
    
    field.currentFloor:removeEntity(entity)
    
  end
  
}
