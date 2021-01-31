#include "../action/ActionRotate.hpp"
#include "LocomotionWaddle.hpp"

#define ACTION_DURATION_MS 1000
#define TILT_ANGLE 10

LocomotionWaddle::LocomotionWaddle(hardware::Kinematics& kinematics)
    : Locomotion(10), kinematics(kinematics),
    forward({
      ActionRotate(kinematics, {
        { hardware::Joint::left_ankle, initial_ankle_angle + TILT_ANGLE },
        { hardware::Joint::right_ankle, initial_ankle_angle + TILT_ANGLE }
      }, ActionRotate::ABSOLUTE),
      ActionRotate(kinematics, {
        { hardware::Joint::left_ankle, initial_ankle_angle - TILT_ANGLE },
        { hardware::Joint::right_ankle, initial_ankle_angle - TILT_ANGLE }
      }, ActionRotate::ABSOLUTE)
    }, ActionSequential::LOOP_FOREVER) {
}

std::string LocomotionWaddle::name() {
  return "Waddle";
}

void LocomotionWaddle::control_loop() {
  forward.execute();
}

void LocomotionWaddle::on_start() {
  kinematics.set_joint_control_mode(hardware::Joint::left_wheel, hardware::JointControlMode::time, 0, 0, ACTION_DURATION_MS / 2, ACTION_DURATION_MS);
  kinematics.set_joint_control_mode(hardware::Joint::left_ankle, hardware::JointControlMode::time, 0, 0, ACTION_DURATION_MS / 2, ACTION_DURATION_MS);
  kinematics.set_joint_control_mode(hardware::Joint::right_ankle, hardware::JointControlMode::time, 0, 0, ACTION_DURATION_MS / 2, ACTION_DURATION_MS);
  kinematics.set_joint_control_mode(hardware::Joint::right_wheel, hardware::JointControlMode::time, 0, 0, ACTION_DURATION_MS / 2, ACTION_DURATION_MS);
  kinematics.set_joint_position({
    { hardware::Joint::left_ankle, initial_ankle_angle },
    { hardware::Joint::right_ankle, initial_ankle_angle }
  });
  forward.start();
}

void LocomotionWaddle::on_stop() {
  kinematics.set_joint_control_mode(hardware::Joint::left_wheel, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::left_ankle, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::right_ankle, hardware::JointControlMode::off);
  kinematics.set_joint_control_mode(hardware::Joint::right_wheel, hardware::JointControlMode::off);
}

void LocomotionWaddle::up(bool key_down, std::set<std::string>& modifiers) {
  //
}

void LocomotionWaddle::down(bool key_down, std::set<std::string>& modifiers) {
  //
}

void LocomotionWaddle::left(bool key_down, std::set<std::string>& modifiers) {
  //
}

void LocomotionWaddle::right(bool key_down, std::set<std::string>& modifiers) {
  //
}