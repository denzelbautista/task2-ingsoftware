#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <stdexcept>
#include <string>
#include <vector>

class RegisterSN {
 public:
  struct DataSN {
    std::string timestamp;
    std::string type_of_sensor;
    float read;

    DataSN(const std::string& ts, const std::string& type, float r)
        : timestamp(ts), type_of_sensor(type), read(r) {
      if (type != "AIRQUALITY" && type != "ULTRAVIOLETRADIATION" &&
          type != "TRAFFIC") {
        throw std::invalid_argument("Invalid sensor type");
      }
    }
  };

  RegisterSN() {
    sensor_indices = {
        {"AIRQUALITY", 0}, {"ULTRAVIOLETRADIATION", 1}, {"TRAFFIC", 2}};
    best = std::vector<float>(3, -1.0);
    accumulated = std::vector<float>(3, 0.0);
    best_from = std::vector<std::string>(3, "-1");
    current_from = std::vector<std::string>(3, "-1");
    best_to = std::vector<std::string>(3, "-1");
    recording = std::vector<bool>(3, false);
  }

  void register_one(const std::string& timestamp,
                    const std::string& type_of_sensor, float read) {
    data.push_back(DataSN(timestamp, type_of_sensor, read));

    auto it = sensor_indices.find(type_of_sensor);
    if (it == sensor_indices.end()) {
      return;
    }

    int index = it->second;

    if (!recording[index]) {
      recording[index] = true;
      current_from[index] = timestamp;
    }

    accumulated[index] += read;

    if (accumulated[index] > best[index]) {
      best[index] = accumulated[index];
      best_from[index] = current_from[index];
      best_to[index] = timestamp;
    }

    if (accumulated[index] <= 0) {
      accumulated[index] = 0;
      recording[index] = false;
    }
  }

  void register_many(const std::vector<DataSN>& readings) {
    for (const auto& reading : readings) {
      register_one(reading.timestamp, reading.type_of_sensor, reading.read);
    }
  }

  std::string highest_accumulate(const std::string& type_of_sensor) const {
    auto it = sensor_indices.find(type_of_sensor);
    if (it == sensor_indices.end() || best[it->second] == -1.0) {
      return R"({"highest_accumulated_value": -1.0, "from": "-1", "to": "-1"})";
    } else {
      int index = it->second;
      return R"({"highest_accumulated_value": )" + std::to_string(best[index]) +
             R"(, "from": ")" + best_from[index] + R"(", "to": ")" +
             best_to[index] + R"("})";
    }
  }

 private:
  std::vector<DataSN> data;
  std::unordered_map<std::string, int> sensor_indices;
  std::vector<float> best;
  std::vector<float> accumulated;
  std::vector<std::string> best_from;
  std::vector<std::string> current_from;
  std::vector<std::string> best_to;
  std::vector<bool> recording;
};

// python setup.py build_ext --inplace

namespace py = pybind11;

PYBIND11_MODULE(RegisterSN, m) {
  py::class_<RegisterSN::DataSN>(m, "DataSN")
      .def(py::init<const std::string&, const std::string&, float>());

  py::class_<RegisterSN>(m, "RegisterSN")
      .def(py::init<>())
      .def("register_one", &RegisterSN::register_one)
      .def("register_many", &RegisterSN::register_many)
      .def("highest_accumulate", &RegisterSN::highest_accumulate);
}