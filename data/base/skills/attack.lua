data.skills['base.skills.attack'] = {

  onSelect = function(turnChar, target)

    local dmg = 10
    target.hp = target.hp - dmg

    return {      
      dialogText = turnChar.name .. ' attacks ' .. target.name .. ' => ' .. dmg .. ' damage',
      target = target
    }

  end

}
