sources = [
  'sync.h',
  'sync.cc',
  'thread.h',
  'thread.cc',
  'watched_thread.h',
  'watched_thread.cc']

foolib = static_library('kea-threads',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        #dependencies : glib_dep,
                        install : true)
