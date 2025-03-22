if not TESTS_OPT.enabled() or not NETCONF_DEP.found()
    subdir_done()
endif

kea_yang_testutils_lib = static_library(
    'kea-yang-testutils',
    'translator_test.cc',
    include_directories: [include_directories('.')] + INCLUDES,
)
