data.entities[RESOURCE_ID] = {

  onInteract = function(entity, player)

    print("enemy - onInteractZ")

    local encounterId  = entity:getValue('base.encounterId') 
    local encounterExp = entity:getValue('base.encounterExp') 

    local newBattle = data.encounters[encounterId].onEncounter()
    newBattle.exp   = encounterExp

    newBattle.onBattleWon = function(battle) 

      for i, partyMember in ipairs(battle.playerChars) do

        local levelBeforeBattle = save.getPartyMemberLevel(partyMember.id)
        local expBeforeBattle   = save.getPartyMemberExp(partyMember.id)

        local expAfterBattle = expBeforeBattle + battle.exp
        save.setPartyMemberExp(partyMember.id, expAfterBattle)

        local levelAfterBattle = save.getPartyMemberLevel(partyMember.id)

        if levelAfterBattle > levelBeforeBattle then
          print(partyMember.name .. ' LEVEL UP! ' .. levelAfterBattle)
        end
      end

      field.currentFloor:removeEntity(entity)

    end

    battle.setCurrentBattle(newBattle)


  end

}
