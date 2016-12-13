--FIELD stuff
if(field ~= nil) then

  field.onInput = function(input)


    --[[
    
    	if (ScriptManager::manager->weBattle()) { //TODO: hack
//
//		return true;
//	}
]]--

    if battle.weBattle() then 
      return 
    end
--[[
    //
    //	if (e->key.keysym.sym == SDLK_ESCAPE) {
      //
      //		MenuManager::manager->setVisible(true);
      //		ScriptManager::manager->doString("ui.openMenu()"); //TODO: lol
      //
      //		return true;
      //	}

    ]]--


    if input.up then
      field.onInputUp()
    elseif input.right then
      field.onInputRight()
    elseif input.down then
      field.onInputDown()
    elseif input.left then
      field.onInputLeft()      
    end


  end


  field.update = function(dt)
    
  end

  field.render = function()

  end

end