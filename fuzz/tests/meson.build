if not PASSWORDLESS_SUDO_SET_UP
    subdir_done()
endif

foreach f : FUZZER_EXECUTABLES
    test(
        f.name(),
        SUDO,
        args: [f],
        is_parallel: false,
        priority: -1,
        suite: 'sudo-tests',
    )
endforeach
