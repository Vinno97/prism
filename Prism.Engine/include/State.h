#pragma once
#include "Context.h"

class State {
 public:
  State();
  virtual ~State();

  virtual void onUpdate(Context context);
  virtual void onEnter();
  virtual void onLeave();
};
