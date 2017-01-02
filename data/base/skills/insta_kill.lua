data.skills['base.skills.insta_kill'] = {

  onSelect = function(turnChar, target)

    local dmg = target.hp
    target.hp = target.hp - target.hp

    return {      
      dialogText = turnChar.name .. ' attacks ' .. target.name .. ' => ' .. dmg .. ' damage',
      target = target
    }

  end

}
