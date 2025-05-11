current_source_dir = meson.current_source_dir()
fuzz_test_scripts = run_command(
    GRABBER,
    current_source_dir,
    'test_fuzz_*.sh',
    check: true,
)
fuzz_test_scripts = fuzz_test_scripts.stdout().strip().split('\n')

foreach st : fuzz_test_scripts
    bt = configure_file(input: st, output: st, copy: true)
    test(st, bt)
endforeach
