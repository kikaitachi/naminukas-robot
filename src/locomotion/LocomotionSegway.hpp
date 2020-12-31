#ifndef NAMINUKAS_BRAIN_LOCOMOTION_SEGWAY_H_
#define NAMINUKAS_BRAIN_LOCOMOTION_SEGWAY_H_

#include "../IMU.hpp"
#include "Locomotion.hpp"
#include "../PIDController.hpp"

/**
 * Segway like balancing on two wheels.
 */
class LocomotionSegway: public Locomotion {
  public:
    LocomotionSegway(hardware::Kinematics& kinematics, IMU& imu);
    std::string name();
    void control_loop();
    void on_start();
    void on_stop();
    void up(bool key_down, std::set<std::string>& modifiers);
    void down(bool key_down, std::set<std::string>& modifiers);
    void left(bool key_down, std::set<std::string>& modifiers);
    void right(bool key_down, std::set<std::string>& modifiers);
    void stop();

  protected:
    hardware::Kinematics& kinematics;
    IMU& imu;
    PIDController speed_controller;
    PIDController pitch_controller;
    float prev_rpm;
    float pos_speed;
    float left_turn_speed, right_turn_speed;
    std::vector<hardware::JointPosition> expected_pos;
    std::vector<hardware::JointPosition> prev_pos;
};

#endif // NAMINUKAS_BRAIN_LOCOMOTION_SEGWAY_H_