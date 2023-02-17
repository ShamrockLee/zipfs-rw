deps_libfuse_example = [
    dep_libfuse,
]

exe_libfuse_example_no_op = executable(
    'no-op',
    ['no_op.c'],
    dependencies: deps_libfuse_example,
    include_directories: [inc_config],
)

test('libfuse-example-no-op', exe_libfuse_example_no_op)
