#ifndef ROBOT_HAL_H
#define ROBOT_HAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
  #endif

  void hal_hardware_init(void);
  void hal_motor_set(uint8_t id, int8_t speed);
  void hal_kick(float power);
  float hal_get_battery(void);

#ifdef__cplusplus
}
#endif

#endif
