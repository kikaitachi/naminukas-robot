#ifndef NAMINUKAS_BRAIN_ROBOT_H_
#define NAMINUKAS_BRAIN_ROBOT_H_

#include "Camera.hpp"
#include "Hardware.hpp"
#include "IMU.hpp"
#include "Locomotion.hpp"
#include "Model.hpp"
#include "Telemetry.hpp"

class Robot {
  public:
    Robot(telemetry::Items& telemetryItems, IMU& imu, hardware::Kinematics& kinematics, PointCloud& camera);
    ~Robot();

  private:
    IMU& imu;
    hardware::Kinematics& kinematics;
    telemetry::Items& telemetryItems;
    telemetry::ItemString* mode;
    Locomotion* current_locomotion_mode;
    Model* model;

    void add_locomotion(Locomotion* locomotion, std::string key);
};

#endif  // NAMINUKAS_BRAIN_ROBOT_H_
