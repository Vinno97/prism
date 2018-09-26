#pragma once
#include "Context.h"

class State {
public:
  State();
  ~State();

  virtual void update(Context context);
  virtual void onEnter();
  virtual void onLeave();

private:
	Context context;
};
