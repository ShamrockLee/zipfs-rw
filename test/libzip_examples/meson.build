deps_libzip_example = [
    dep_libzip,
]

exe_libzip_example_no_op = executable(
    'no-op',
    ['no_op.c'],
    dependencies: deps_libzip_example,
)

test('libzip-example-no-op', exe_libzip_example_no_op)

exe_libzip_example_stat = executable(
    'zip-stat',
    ['zip_stat.c'],
    dependencies: deps_libzip_example,
    c_args: [
        '-Wno-stringop-truncation',
    ],
)

exe_libzip_example_cat = executable('zip-cat', [ 'zip_cat.c' ],
  dependencies: deps_libzip_example,
)

exe_test_zip_cat_hello = find_program('./test-zip-cat-hello')

test('shellcheck-test-zip-cat-hello', exe_shellcheck,
args: [ '-x', '-P', meson.current_source_dir(), exe_test_zip_cat_hello.full_path() ],
)

test('libzip-example-cat-hello', exe_test_zip_cat_hello,
args: [
  exe_libzip_example_cat.full_path(),
  sample_hello.full_path(),
],
depends: [
  exe_libzip_example_cat,
  sample_hello,
],
)
