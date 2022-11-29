project('zipfs-rw', 'c',
  version: '0.1.0',
  license: 'MIT',
  default_options: [
    'buildtype=debugoptimized',
    'c_std=c11',
    'warning_level=3',
  ],
)

cfg_h = configuration_data()

dep_libzip = dependency('libzip')
dep_libfuse2 = dependency('fuse', version: '<3.0.0', required: false)
dep_libfuse3 = dependency('fuse3', version: '>=3.0.0', required: false)

use_fuse3 = false

if dep_libfuse3.found()
  dep_libfuse = dep_libfuse3
  use_fuse3 = true
  cfg_h.set('FUSE_USE_VERSION', 30)
else
  dep_libfuse = dep_libfuse2
endif

cfg_h.set('USE_FUSE3', use_fuse3)

configure_file(output: 'config.h', configuration: cfg_h)
inc_config = include_directories('.')

subdirs = [
  'test',
]

foreach d: subdirs
  subdir(d)
endforeach
