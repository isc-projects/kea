sources = [
  'observation.h',
  'observation.cc',
  'context.h',
  'context.cc',
  'stats_mgr.h',
  'stats_mgr.cc']

foolib = static_library('kea-stats',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        #dependencies : glib_dep,
                        install : true)
