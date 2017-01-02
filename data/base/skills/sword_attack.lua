data.skills['base.skills.sword_attack'] = {

  onSelect = function(turnChar, target)

    target.hp = target.hp - 10
    print(turnChar.name .. ' attacks ' .. target.name .. ' hp:' .. target.hp .. '/100') 
    
    return {
      
      dialogText = 'test dialog'
      
      
      }

  end

}
