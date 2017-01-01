--FIELD stuff

field = {}

if(field ~= nil) then

  field.currentFloor = nil

  field.onInput = function(input)

    if battle.weBattle() then 
      return 
    end

    if field.currentFloor ~= nil then
      field.currentFloor:onInput(input)
    end

  end


  field.update = function(dt)
    if field.currentFloor ~= nil then field.currentFloor:update(dt) end
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