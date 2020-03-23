#include <Servo.h>
#include "api.h"

class Cap {
 public:
  Cap() = default;

  void begin() const {
    _servo.attach(_servoPin);
    open();
    close();
  }

  void open() const {
#ifdef DEBUG
    Serial.println("open");
#else
    _servo.write(_openAngle);
#endif
    delay(1000);
    _open = true;
  }

  void close() {
#ifdef DEBUG
    Serial.println("close");
#else
    _servo.write(_closeAangle);
#endif
    delay(1000);
    _open = false;
  }

  bool isOpen() const { return _open; }

 private:
  static const int _servoPin = 2;
  static const int _openAngle = 170;
  static const int _closeAangle = 0;
  Servo _servo;
  mutable bool _open = false;

  DISABLE_COPY(Cap);
};
