# Copy corp to build directory so that tests can find it.
current_source_dir = meson.current_source_dir()
command = run_command(GRABBER, current_source_dir, '*', check: true)
foreach j : command.stdout().strip().split('\n')
    configure_file(input: j, output: j, copy: true)
endforeach
