data.skills['base.skills.skilltest1'] = {

  onSelect = function(turnChar, target)

    target.hp = target.hp - 10
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/' .. target.maxHp) 

  end

}
