if not TESTS_OPT.enabled()
    subdir_done()
endif

kea_util_unittests_lib = static_library(
    'kea-util-unittests',
    'check_valgrind.cc',
    'fork.cc',
    'interprocess_util.cc',
    'newhook.cc',
    'resource.cc',
    'run_all.cc',
    'testdata.cc',
    'wiredata.cc',
    dependencies: [GTEST_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
)
