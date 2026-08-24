foreach f : FUZZING_HARNESSES
    n = f.name()
    t = executable(
        f'test_@n@',
        'main.cc',
        include_directories: [include_directories('..')] + INCLUDES,
        link_with: [f],
        build_rpath: BUILD_RPATH,
    )
    test(t.name(), t, is_parallel: false, priority: -1)
endforeach
