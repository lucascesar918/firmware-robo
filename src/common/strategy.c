#include "strategy.h"
#include "../hal/robot_hal.h"
#include "pid.h"

static PIDConfig pid_motor_esq;
static PIDConfig pid_motor_dir;
static uint8_t initialized = 0;

void strategy_init(void) {
  // Configura os ganhos do PID (calibrar na prática!)
  pid_motor_esq.kp = 1.5f;
  pid_motor_esq.ki = 0.1f;
  pid_motor_esq.kd = 0.0f;
  pid_reset(&pid_motor_esq);

  pid_motor_dir.kp = 1.5f;
  pid_motor_dir.ki = 0.1f;
  pid_motor_dir.kd = 0.0f;
  pid_reset(&pid_motor_dir);

  initialized = 1;
}

void run_vsss_strategy(void) {
  float bateria;
  float controle_esq, controle_dir;

  if (!initialized)
    strategy_init();

  bateria = hal_get_battery();

  if (bateria < 10.0f) {
    hal_motor_set(0, 0);
    hal_motor_set(1, 0);
    return;
  }

  // Estratégia provisória para teste: andar para frente
  controle_esq = pid_calculate(&pid_motor_esq, 50.0f, 0.0f);
  controle_dir = pid_calculate(&pid_motor_dir, 50.0f, 0.0f);

  hal_motor_set(0, (int8_t)controle_esq); // Motor ID 0
  hal_motor_set(1, (int8_t)controle_dir); // Motor ID 1
}
