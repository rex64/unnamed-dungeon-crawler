data.skills['base.skills.magic_blast'] = {

  onSelect = function(turnChar, target)

    target.hp = target.hp - 10
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/100') 
    
    return {
      
      dialogText = 'test dialog'
      
      
      }

  end

}
