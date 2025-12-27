#include "pid.h"

float pid_calculate(PIDConfig *pid, float setpoint, float measured) {
  float error;
  float output;

  error = setpoint - measured;
  output = (pid->kp * error);

  pid->integral += error;
  output += (pid->ki * pid->integral);

  if (output > 100.0f) output = 100.0f;
  if (output < -100.0f) output = -100.0f;

  return output;
}

void pid_reset(PIDConfig *pid) {
  pid->integral = 0.0f;
  pid->prev_error = 0.0f;
}
