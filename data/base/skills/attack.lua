data.skills[RESOURCE_ID] = {

  onSelect = function(turnChar, target)

--  var levelDifference = Math.max(attackerLevel - defenderLevel);
--  var atkDefDiff = Math.max(0, attackerATK - defenderDEF);

--  var percentage = 10 + levelDifference * 5 + (atkDefDiff / 2) ;

--  var dmg = defenderHP * percentage / 100 + (attackerLevel / 2);


--  return  Math.max(1, Math.floor(dmg));

    local levelDifference = math.max(0, turnChar.level - target.level);
    local atkDefDiff = math.max(0, turnChar.atk - target.def);

    local percentage = 10 + levelDifference * 5 + (atkDefDiff / 2) ;

    local dmg = math.max(1, math.floor(target.def * percentage / 100 + (turnChar.level / 2))); 

    target.hp = target.hp - dmg

    return {      
      dialogText = turnChar.name .. ' attacks ' .. target.name .. ' => ' .. dmg .. ' damage',
      target = target
    }

  end

}
