sources = [
  'run_unittests.cc',
  'thread_unittest.cc',
  'lock_unittest.cc',
  'condvar_unittest.cc',
  'watched_thread_unittest.cc']

foolib = static_library('kea-threads',
                        sources,
                        include_directories : [lib_inc, configuration_inc, gtest_inc],
                        #dependencies : glib_dep,
                        install : true)
