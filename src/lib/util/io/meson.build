kea_util_io_lib = library('kea-util-io',
  'fd.cc',
  'fd.h',
  'pktinfo_utilities.h',
  'sockaddr_util.h',
  include_directories: [include_directories('.')] + includes,
  link_with: libs_built_so_far,
)
libs_built_so_far = [kea_util_io_lib] + libs_built_so_far
