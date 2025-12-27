#include "../common/strategy.h"
#include <pic16f873.h>
#include <stdint.h>

__code unsigned int __at(_CONFIG) __config = 0x3F32;

extern void hal_hardware_init(void);

void main() {
  hal_hardware_init();

  strategy_init();

  while (1) {
    run_vsss_strategy();
    volatile uint16_t delay = 0;
    while (delay < 1000)
      delay++;
  }
}
