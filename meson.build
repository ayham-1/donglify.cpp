project('donglify', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++23'])

incdir = include_directories('include/')

exe = executable('donglify', 
  'src/donglify.cpp',
  'src/execute.cpp',
  'src/disk.cpp',
  'src/state.cpp',
  'src/cmds/initialize_partitions.cpp',
  install : true, include_directories: incdir)

test('basic', exe)
