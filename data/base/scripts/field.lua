--FIELD stuff

field = {}

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
      engine.onInputUp()
    elseif input.right then
      engine.onInputRight()
    elseif input.down then
      engine.onInputDown()
    elseif input.left then
      engine.onInputLeft()      
    end


  end


  field.update = function(dt)
    
  end

  field.render = function()

  end

end