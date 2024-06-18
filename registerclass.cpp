#include <ctime>
#include <iostream>

class registerclass {
 private:
  std::string timestamp;
  std::string typeofsensor;
  float read_value;

 public:
  registerclass(std::string _typeofsensor, float _read_value) {
    if (_typeofsensor != "AIRCUALITY" &&
        _typeofsensor != "ULTRAVIOLETRADIATION" && _typeofsensor != "TRAFFIC") {
      throw std::invalid_argument("Invalid sensor type");
    }
    typeofsensor = _typeofsensor;
    read_value = _read_value;
    std::time_t result = std::time(nullptr);
    timestamp = std::asctime(std::localtime(&result));
  }
}
