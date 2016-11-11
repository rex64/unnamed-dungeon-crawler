local stairs = {
  
  name = 'stairs',
  sprite = 'data.base.spritesheets.stairs',
  
  onInteract = function()
    print("stairs - onInteract")
  end
  
}

data.entities['data.base.entities.stairs'] = stairs
