data.entities[RESOURCE_ID] = {

  onInteract = function(entity, player)

    print("enemy - onInteractZ")

    local encounterId = entity:getValue('base.encounterId') 
    print(encounterId)
    local newBattle = data.encounters[encounterId].onEncounter()
    
    newBattle.onBattleWon = function() 

      field.currentFloor:removeEntity(entity)

    end

    battle.setCurrentBattle(newBattle)


  end

}
