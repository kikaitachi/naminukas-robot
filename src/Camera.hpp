#ifndef NAMINUKAS_BRAIN_CAMERA_H_
#define NAMINUKAS_BRAIN_CAMERA_H_

#include "Telemetry.hpp"

class PointCloud {
  public:
    PointCloud(telemetry::Items& telemetryItems, std::function<bool()> is_terminated);

  private:
    telemetry::ItemPoints* points_telemetry;
};

#endif  // NAMINUKAS_BRAIN_CAMERA_H_