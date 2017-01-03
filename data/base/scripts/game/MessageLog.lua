--//////////////////////////////////////////////////////////////////////
--************************
--MessageLog
--************************
MessageLog = {}
MessageLog.__index = MessageLog

function MessageLog.new()

  self = setmetatable({}, MessageLog)
  self.messageQueue  = {}
  self.messageActive = {}
  self.timer = 0

  self:addMessage('Message1!!!')
  self:addMessage('Message2!!!')
  self:addMessage('Message3!!!')
  self:addMessage('Message4 YO!!!')

  return self
end

--function MessageLog:onInput(input)
--end

function MessageLog:update(dt)

  if #self.messageQueue == 0 and #self.messageActive == 0 then
    self.timer = 0
    return
  elseif #self.messageQueue ~= 0 and #self.messageActive == 0 then
    local msg = table.remove(self.messageQueue, 1)
    table.insert(self.messageActive, msg)

  end

  if #self.messageQueue ~= 0 and self.timer >= 1000 then

    local msg = table.remove(self.messageQueue, 1)
    table.insert(self.messageActive, msg)
    self.timer = self.timer + dt
    self.timer = 0

  end

  local toBeRemoved = nil
  for i, msg in ipairs(self.messageActive) do
    msg.timer = msg.timer + dt
    if msg.timer >= 6000 then
      toBeRemoved = i
    end

  end

  if toBeRemoved ~= nil then
    table.remove(self.messageActive, toBeRemoved)
  end

  self.timer = self.timer + dt

end

function MessageLog:render()

  local x = 73
  local bottom = 178
  local offset = 7

  for i, msg in ipairs(self.messageActive) do
    engine.renderTextLine(msg.text, x,  bottom - offset * (#self.messageActive - i ), false, 1);

  end


--  engine.renderTextLine('Message1!!!', x,  bottom - offset * 3, false, 1);
--  engine.renderTextLine('Message2.', x,  bottom - offset * 2, false, 1);
--  engine.renderTextLine('Message3.', x, bottom - offset * 1, false, 1);
--  engine.renderTextLine('Message4.', x, bottom - offset * 0, false, 1);

end 

function MessageLog:addMessage(text)

  local msg = {text = text, timer = 0}
  table.insert(self.messageQueue, msg )

end

return MessageLog
