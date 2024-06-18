#include <ctime>
#include <iostream>
#include <vector>

class registerclass {
 private:
  std::string timestamp;
  std::string typeofsensor;
  float read_value;

 public:
  registerclass() {
    timestamp = "";
    typeofsensor = "";
    read_value = 0;
  }

  void register_one(std::string _timestamp, std::string _typeofsensor,
                    float _read_value) {
    if (_typeofsensor != "AIRCUALITY" &&
        _typeofsensor != "ULTRAVIOLETRADIATION" && _typeofsensor != "TRAFFIC") {
      throw std::invalid_argument("Invalid sensor type");
    }
    timestamp = _timestamp;
    typeofsensor = _typeofsensor;
    read_value = _read_value;
  }
};

void register_many(vector<registerclass> &registers) {}