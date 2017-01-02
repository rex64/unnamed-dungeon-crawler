data.skills['base.skills.self_faint'] = {

  onSelect = function(turnChar, target)

    local dmg   = turnChar.hp
    turnChar.hp = turnChar.hp - dmg

    return {      
      dialogText = turnChar.name .. ' attacks ' .. turnChar.name .. ' => ' .. dmg .. ' damage',
      target = target
    }

  end

}
