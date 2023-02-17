project(
    'zipfs-rw',
    'c',
    version: '0.1.0',
    license: 'MIT',
    default_options: [
        'buildtype=debugoptimized',
        'c_std=c11',
        'warning_level=3',
    ],
)

cfg_h = configuration_data()

cfg_h.set('VERSION', meson.project_version())

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
    cfg_h.set('FUSE_USE_VERSION', 25)
endif

cfg_h.set('USE_FUSE3', use_fuse3)

dep_libtree_fetched = dependency('libtree', required: false)

exe_gnu_make = find_program('make', required: false)

is_builtin_libtree = not dep_libtree_fetched.found()

dep_libtree = dep_libtree_fetched

if is_builtin_libtree
    builtin_libtree = custom_target(
        'builtin-libtree',
        output: [
            'libtree.a',
            'libtree.so',
            'libtree.pc',
        ],
        input: files('libtree/Makefile'),
        command: [
            exe_gnu_make,
            '-C', 'libtree',
        ],
    )
    dep_libtree_builtin = declare_dependency(
        compile_args: [
            '-g',
            '-Os',
            '-std=c99',
            '-Wall',
            '-Werror',
            '-Wno-unused-function',
            '-fpic',
        ],
        include_directories: [
            include_directories('libtree'),
        ],
    )
    dep_libtree = dep_libtree_builtin
endif

configure_file(output: 'config.h', configuration: cfg_h)
inc_config = include_directories('.')

inc_optparse = include_directories('optparse')

subdirs = [
    'include',
    'src',
    'test',
]

foreach d : subdirs
    subdir(d)
endforeach
