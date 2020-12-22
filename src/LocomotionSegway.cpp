#include "LocomotionSegway.hpp"
#include "Logger.hpp"

LocomotionSegway::LocomotionSegway(hardware::Kinematics& kinematics, IMU& imu)
    : Locomotion(200), kinematics(kinematics), imu(imu) {
  //
}

std::string LocomotionSegway::name() {
  return "Segway";
}

void LocomotionSegway::control_loop() {
  std::vector<hardware::JointPosition> curr_pos = kinematics.get_joint_position({
    hardware::Joint::left_wheel,
    hardware::Joint::right_wheel
  });
  float pitch = imu.get_pitch();
  float error = pitch - expected_pitch;
  float p = 2.5;
  float d = 0;
  float input = error * p + (error - prev_error) * d;
  //logger::debug("curr_pos: [%f %f], input: %f", curr_pos[0].degrees, curr_pos[1].degrees, input);
  kinematics.set_joint_position({
    { hardware::Joint::left_wheel, curr_pos[0].degrees - input },
    { hardware::Joint::right_wheel, curr_pos[1].degrees + input }
  });
  prev_error = error;
}

void LocomotionSegway::on_start() {
  kinematics.set_joint_control_mode(hardware::Joint::left_wheel, hardware::JointControlMode::position);
  kinematics.set_joint_control_mode(hardware::Joint::left_ankle, hardware::JointControlMode::position, 200);
  kinematics.set_joint_control_mode(hardware::Joint::right_ankle, hardware::JointControlMode::position, 200);
  kinematics.set_joint_control_mode(hardware::Joint::right_wheel, hardware::JointControlMode::position);
  kinematics.set_joint_position({
    { hardware::Joint::left_ankle, initial_ankle_angle - 90 },
    { hardware::Joint::right_ankle, initial_ankle_angle + 90 },
  });
  prev_error = 0;
}

void LocomotionSegway::on_stop() {
  kinematics.set_joint_control_mode(hardware::Joint::left_wheel, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::left_ankle, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::right_ankle, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::right_wheel, hardware::JointControlMode::off);
}

void LocomotionSegway::up(bool key_down) {
  // TODO: implement
}

void LocomotionSegway::down(bool key_down) {
  // TODO: implement
}
