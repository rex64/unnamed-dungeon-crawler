#pragma once
union SDL_Event;

class IRenderable
{
public:
  virtual bool onRender() = 0;
  virtual ~IRenderable() { }

};
