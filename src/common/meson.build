common_sources = files('strategy.c', 'pid.c')

lib_common = static_library('common_logic',
  sources             : common_sources,
  include_directories : include_directories('../hal')
)

common_dep = declare_dependency(
  link_with           : lib_common,
  include_directories : include_directories('.')
)
