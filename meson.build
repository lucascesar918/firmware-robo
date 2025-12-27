project('robo_vsss', ['c', 'cpp'],
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
    'c_std=c99',
  ],
)

subdir('src/common')

if meson.is_cross_build()
  # meson setup build-robot --cross-file cross_pic.txt
  message('>>> Configurando para robô (PIC16F873 - C Puro/Bare Metal) <<<')
  subdir('src/firmware')
else
  # meson setup build-pc
  message('>>> Configurando para simulador (grSim - C++ Híbrido) <<<')
  subdir('src/simulator')
endif
