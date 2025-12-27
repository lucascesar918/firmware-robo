#include "../common/strategy.h"
#include "hal_mock.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  std::string ip = "127.0.0.1";
  int port = 20011;

  std::cout << "--- Simulador VSSS Iniciado ---" << std::endl;

  while (true) {
    run_strategy();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  return 0;
}
