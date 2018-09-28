#pragma once
#include "Context.h"

class State {
public:
  State();
  ~State();

  virtual void update(Context context) = 0;
  virtual void onEnter() = 0;
  virtual void onLeave() = 0;
};
