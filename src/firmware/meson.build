firmware_sources = files('main.c', 'hal_real.c')

elf = executable('vsss_robot',
  firmware_sources,
  dependencies        : common_dep,
  include_directories : include_directories('../hal'),
  name_suffix         : 'ihx',
)
