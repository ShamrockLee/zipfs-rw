test(
    'shellcheck-prepare-sample-common',
    exe_shellcheck,
    args: ['-x', '-P', meson.current_source_dir()] + files(
        'prepare_sample_common.sh',
    ),
)

foreach _sample_name : ['hello', 'hello-leafonly', 'symlinks', 'special']
    _sample_name_underscored = _sample_name.replace('-', '_')
    _exe_sample = find_program('./gen-sample-' + _sample_name)

    test(
        'shellcheck-gen-sample-' + _sample_name,
        exe_shellcheck,
        args: ['-x', '-P', meson.current_source_dir(), _exe_sample.full_path()],
    )
    set_variable(
        'sample_' + _sample_name_underscored,
        custom_target(
            'sample-' + _sample_name,
            output: 'sample_@0@.zip'.format(_sample_name_underscored),
            input: _exe_sample.full_path(),
            command: [_exe_sample, '@OUTPUT@'],
        ),
    )
endforeach

unset_variable('_sample_name')
unset_variable('_sample_name_underscored')
unset_variable('_exe_sample')
