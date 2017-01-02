local Window = require('ui.Window')
local Dialog = require('ui.Dialog')

--//////////////////////////////////////////////////////////////////////
--************************
--HeroStatusWindow
--************************

HeroStatusWindow = {}
HeroStatusWindow.__index = HeroStatusWindow
setmetatable(HeroStatusWindow, {__index = Window})

function HeroStatusWindow.new(x, y, w, h, battleChar)

  local self = Window.new(x, y, w, h, false)
  self = setmetatable(self, HeroStatusWindow)

  self.name = 'HeroStatusWindow'

  self.battleChar = battleChar

  return self
end

function HeroStatusWindow:onInput(input)



end

function HeroStatusWindow:render()

  Window.render(self)

  local x = self.x + self.margins.x
  local y = self.y + self.margins.x

  engine.renderTextLine(self.battleChar.name, x, y)
  engine.renderTextLine(self.battleChar.hp .. '/' .. self.battleChar.maxHp .. ' HP', x, y + 8 * 2)
  engine.renderTextLine(self.battleChar.mp .. '/' .. self.battleChar.maxMp .. ' MP', x, y + 8 * 3)


end

function HeroStatusWindow:setHero(newHero)
  self.battleChar = newHero
end

return HeroStatusWindow
