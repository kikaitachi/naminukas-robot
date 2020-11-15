#ifndef NAMINUKAS_BRAIN_DYNAMIXEL_KINEMATICS_H_
#define NAMINUKAS_BRAIN_DYNAMIXEL_KINEMATICS_H_

#include "DynamixelUtil.hpp"
#include "Hardware.hpp"

class DynamixelKinematics: public hardware::Kinematics {
  public:
    DynamixelKinematics();
    ~DynamixelKinematics();
    void set_joint_control_mode(hardware::Joint joint, hardware::JointControlMode mode, double max_acceleration, double max_rpm, double millis);
    void set_joint_position(hardware::Joint joint, double degrees);
    void set_joint_speed(std::vector<hardware::JointSpeed> speeds);
    double get_joint_position(hardware::Joint joint);

  private:
    DynamixelConnection* dynamixel_connection;
    DynamixelXM430W350* dynamixel_XM430W350;
};

#endif  // NAMINUKAS_BRAIN_DYNAMIXEL_KINEMATICS_H_