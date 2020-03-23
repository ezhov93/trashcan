#include "api.h"
#include "button.h"
#include "cap.h"
#include "sensor.h"

// #define DEBUG 0

class Trashcan {
 public:
  Trashcan() = default;

  void init() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("System start");
#endif
    _button.begin();
    _sensor.begin();
    _cap.begin();
    delay(3000);
    _sensor.averaging();
    _calibDistantion = _sensor.averaging() * 0.9f;
  }

  void update() {
    buttonTask();
    sensorTask();
  }

 private:
  Cap _cap;
  Sensor _sensor;
  Button _button;
  float _calibDistantion = 0.f;
  int _timer = 0;

  void buttonTask() {
    if (_button.isClicked()) {
      if (!_cap.isOpen()) {
        _cap.open();
        while (!_button.isClicked()) continue;
        _cap.close();
      } else
        _cap.close();
      return;
    }
  }

  void sensorTask() {
    static int maxHeight = 60;
    static int minHeight = 5;
    static const int capTime = 3000;
    if (!_cap.isOpen()) {
      float distance = _sensor.averaging();
#ifdef DEBUG
      Serial.print("Distance: ");
      Serial.println(distance);
      delay(500);
#endif
      if ((distance > minHeight) && (distance < maxHeight) &&
          (distance < _calibDistantion)) {
        _timer = millis();
        _cap.open();
      }
    } else {
      if (millis() - _timer >= capTime) _cap.close();
    }
  }

  DISABLE_COPY(Trashcan);
};
