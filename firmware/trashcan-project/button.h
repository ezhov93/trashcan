#include "api.h"

class Button {
 public:
  Button() = default;
  void begin() const { pinMode(_pin, INPUT_PULLUP); };
  bool isClicked() {
    update();
    bool tmp = _clicked;
    _clicked = false;
    return tmp;
  }
  void update() {
    int reading = digitalRead(_pin);
    if (reading == HIGH) _timer = millis();
    if ((millis() - _timer) > _debounceDelay)
      if (reading == LOW) _clicked = true;
  }

 private:
  static const int _pin = 3;
  static const int _debounceDelay = 10;
  bool _clicked = false;
  bool _run = false;
  uint32_t _timer;

  DISABLE_COPY(Button);
};
