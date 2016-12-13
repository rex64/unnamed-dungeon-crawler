--GAME stuff
if(game ~= nil) then

  game.onInput = function(input)

    if input.menu == true then
      ui.openMenu()
    end

    -- battle.onInput(input)
    field.onInput(input)
  end

  game.update = function(dt)

    -- battle.update(dt)
    -- field.update(dt)

  end

  game.render = function()

  end

end