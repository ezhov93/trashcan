#include "api.h"

class Sensor {
 public:
  Sensor() = default;

  void begin() const {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_trigPin, LOW);
    distance();
  }
  float distance() const {  // cm
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(_trigPin, LOW);
    float duration = pulseIn(_echoPin, HIGH);
    return (duration / 2) / 29.1;  // получаем расстояние с датчика
  }
  float averaging() const {
    static const float avgs = 3.f;
    float avg = 0;
    for (size_t i = 0; i < avgs; i++) avg += distance();
    return avg / avgs;
  }

 private:
  static const int _trigPin = 11;
  static const int _echoPin = 12;

  DISABLE_COPY(Sensor);
};
