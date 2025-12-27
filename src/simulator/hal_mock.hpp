#ifndef HAL_MOCK_HPP
#define HAL_MOCK_HPP

#include <cstdint>
#include <string>

class MockRobot {
public:
  MockRobot(std::string ip, int port);
  ~MockRobot() = default;
};

extern "C" {
void hal_init();
void hal_motor_set(uint8_t motor_id, int8_t power);
}

#endif
