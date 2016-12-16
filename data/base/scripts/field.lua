--FIELD stuff

field = {}

if(field ~= nil) then

  field.currentFloor = nil

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

    if field.currentFloor ~= nil then
      field.currentFloor:onInput(input)
    end





  end


  field.update = function(dt)

  end

  field.render = function()
    if field.currentFloor ~= nil then
      field.currentFloor:render()

    end
  end

  field.setCurrentFloor = function(floor)
    field.currentFloor = floor
  end

end