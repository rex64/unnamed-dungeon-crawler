#pragma once
union SDL_Event;

class IInputReceiver
{
public:
  virtual bool onInput(SDL_Event* e) = 0;
  virtual ~IInputReceiver() { }
  int priority;

};
