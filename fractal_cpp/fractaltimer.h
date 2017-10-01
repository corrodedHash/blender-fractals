#pragma once

#include <chrono>
#include <iostream>

class FractalTimer {
  std::chrono::steady_clock::time_point itcom_begin;
  std::chrono::steady_clock::time_point com_begin;
  std::chrono::steady_clock::time_point cp_begin;
  std::chrono::steady_clock::time_point all_begin;

public:
  long it_diff = 0;
  long com_diff = 0;

  long rot_diff = 0;
  long move_diff = 0;
  long draw_diff = 0;
  long face_diff = 0;
  long endf_diff = 0;
  long push_diff = 0;
  long pop_diff = 0;
  long cp_diff = 0;
  long all_diff = 0;

  void itcom_start() { itcom_begin = std::chrono::steady_clock::now(); }
  long itcom_end() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now() - itcom_begin)
        .count();
  }

  void com_start() { com_begin = std::chrono::steady_clock::now(); }
  long com_end() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now() - com_begin)
        .count();
  }

  void cp_start() { cp_begin = std::chrono::steady_clock::now(); }
  long cp_end() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now() - cp_begin)
        .count();
  }
  void all_start() { all_begin = std::chrono::steady_clock::now(); }
  long all_end() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now() - all_begin)
        .count();
  }
  void print() {
    std::cout << "Rotation: " << rot_diff << "\n";
    std::cout << "Move: " << move_diff << "\n";
    std::cout << "Draw: " << draw_diff << "\n";
    std::cout << "Face: " << face_diff << "\n";
    std::cout << "Endface: " << endf_diff << "\n";
    std::cout << "Push: " << push_diff << "\n";
    std::cout << "Pop: " << pop_diff << "\n";
    std::cout << "Commands: "
              << rot_diff + move_diff + draw_diff + face_diff + endf_diff +
                     push_diff + pop_diff
              << std::endl;
    std::cout << "Iterate: " << it_diff << "\n";
    std::cout << "Copy: " << cp_diff << "\n";
    std::cout << "All: " << all_diff << "\n";
    std::cout << "Total: "
              << rot_diff + move_diff + draw_diff + face_diff + endf_diff +
                     push_diff + pop_diff + it_diff + cp_diff
              << std::endl;
  }
};