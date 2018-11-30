sources = [
  'fd.h',
  'fd.cc',
  'fd_share.h',
  'fd_share.cc',
  'socketsession.h',
  'socketsession.cc',
  'sockaddr_util.h',
  'pktinfo_utilities.h']

foolib = static_library('kea-util-io',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        #dependencies : glib_dep,
                        install : true)
