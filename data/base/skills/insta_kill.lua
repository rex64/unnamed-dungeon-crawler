data.skills[RESOURCE_ID] = {

  onSelect = function(turnChar, target)

    local dmg = target.hp
    target.hp = target.hp - target.hp

    return {      
      dialogText = turnChar.name .. ' attacks ' .. target.name .. ' => ' .. dmg .. ' damage',
      target = target
    }

  end

}
