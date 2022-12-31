deps_libzip_example = [
  dep_libzip,
]

exe_libzip_example_no_op = executable('no-op', [ 'no_op.c' ],
  dependencies: deps_libzip_example,
)

test('libzip-example-no-op', exe_libzip_example_no_op)

exe_libzip_example_stat = executable('zip-stat', [ 'zip_stat.c' ],
  dependencies: deps_libzip_example,
)

exe_libzip_example_cat = executable('zip-cat', [ 'zip_cat.c' ],
  dependencies: deps_libzip_example,
)
