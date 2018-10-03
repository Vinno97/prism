#pragma once
#include "State.h"

class MenuState : public State {
 public:
  MenuState();
  ~MenuState();

  void onUpdate(Context context) override;
  void onEnter() override;
  void onLeave() override;
};
