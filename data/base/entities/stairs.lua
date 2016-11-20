local stairs = {
  
  onInteract = function()
    print("stairs - onInteract")
    table.remove(ui.windows)
  end
  
}

data.entities['data.base.entities.stairs'] = stairs
