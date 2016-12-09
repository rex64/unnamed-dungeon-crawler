data.skills['base.skills.magic_arrow'] = {

  onSelect = function(turnChar, target)

    target.hp = target.hp - 10
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/100') 

  end

}
