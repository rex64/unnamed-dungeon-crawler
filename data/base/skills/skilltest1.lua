data.skills[RESOURCE_ID] = {

  onSelect = function(turnChar, target)

    local targetDmg = target.hp - 10
    target.hp = target.hp - targetDmg
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/' .. target.maxHp) 

    return {

      dialogText = turnChar.name .. ' - ' .. target.name .. ' - ' .. targetDmg .. ' damage'      

    }

  end

}
