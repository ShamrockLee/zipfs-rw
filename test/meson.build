exe_shellcheck = find_program('shellcheck')

test('shellcheck-prepare-workdir', exe_shellcheck,
args: files('prepare_workdir.sh'),
)

subdir('samples')
subdir('libfuse_examples')
subdir('libtree_examples')
subdir('libzip_examples')
