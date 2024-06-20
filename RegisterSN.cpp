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

  void register_one(const std::string& timestamp,
                    const std::string& type_of_sensor, float read) {
    data.push_back(DataSN(timestamp, type_of_sensor, read));
  }

  void register_many(const std::vector<DataSN>& readings) {
    for (const auto& reading : readings) {
      data.push_back(reading);
    }
  }

  std::string highest_accumulate(const std::string& type_of_sensor) {
    float best = -1.0, accumulated = 0.0;
    std::string best_from, best_to, current_from;
    bool recording = false;

    for (const auto& entry : data) {
      if (entry.type_of_sensor == type_of_sensor) {
        if (!recording) {
          recording = true;
          current_from = entry.timestamp;
        }

        accumulated += entry.read;

        if (accumulated > best) {
          best = accumulated;
          best_from = current_from;
          best_to = entry.timestamp;
        }

        if (accumulated <= 0) {
          accumulated = 0;
          recording = false;
        }
      }
    }

    if (best == -1.0) {
      return R"({"highest_accumulated_value": -1.0, "from": "-1", "to": "-1"})";
    } else {
      return R"({"highest_accumulated_value": )" + std::to_string(best) +
             R"(, "from": ")" + best_from + R"(", "to": ")" + best_to + R"("})";
    }
  }

 private:
  std::vector<DataSN> data;
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