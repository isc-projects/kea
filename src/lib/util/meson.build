epoll_event_handler_cc = []
epoll_event_handler_h = []
if HAVE_EPOLL
    epoll_event_handler_cc = 'epoll_event_handler.cc'
    epoll_event_handler_h = 'epoll_event_handler.h'
endif

kqueue_event_handler_cc = []
kqueue_event_handler_h = []
if HAVE_KQUEUE
    kqueue_event_handler_cc = 'kqueue_event_handler.cc'
    kqueue_event_handler_h = 'kqueue_event_handler.h'
endif

kea_util_lib = shared_library(
    'kea-util',
    'boost_time_utils.cc',
    'chrono_time_utils.cc',
    'csv_file.cc',
    'dhcp_space.cc',
    'encode/encode.cc',
    'encode/utf8.cc',
    epoll_event_handler_cc,
    'fd_event_handler.cc',
    'fd_event_handler_factory.cc',
    'filesystem.cc',
    kqueue_event_handler_cc,
    'labeled_value.cc',
    'memory_segment_local.cc',
    'multi_threading_mgr.cc',
    'pid_file.cc',
    'poll_event_handler.cc',
    'ready_check.cc',
    'reconnect_ctl.cc',
    'select_event_handler.cc',
    'state_model.cc',
    'stopwatch.cc',
    'stopwatch_impl.cc',
    'str.cc',
    'versioned_csv_file.cc',
    'watched_thread.cc',
    'watch_socket.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '114.0.0',
)
subdir('io')
subdir('unittests')
LIBS_BUILT_SO_FAR = [kea_util_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
subdir('python')
kea_util_headers = [
    'bigints.h',
    'boost_time_utils.h',
    'buffer.h',
    'chrono_time_utils.h',
    'csv_file.h',
    'dhcp_space.h',
    'doubles.h',
    'encode/encode.h',
    'encode/utf8.h',
    epoll_event_handler_h,
    'fd_event_handler.h',
    'fd_event_handler_factory.h',
    'filesystem.h',
    'io/fd.h',
    'io/pktinfo_utilities.h',
    'io/sockaddr_util.h',
    'hash.h',
    'io.h',
    kqueue_event_handler_h,
    'labeled_value.h',
    'memory_segment.h',
    'memory_segment_local.h',
    'multi_threading_mgr.h',
    'optional.h',
    'pid_file.h',
    'pointer_util.h',
    'poll_event_handler.h',
    'range_utilities.h',
    'readwrite_mutex.h',
    'ready_check.h',
    'reconnect_ctl.h',
    'select_event_handler.h',
    'staged_value.h',
    'state_model.h',
    'stopwatch.h',
    'stopwatch_impl.h',
    'str.h',
    'thread_pool.h',
    'triplet.h',
    'unlock_guard.h',
    'versioned_csv_file.h',
    'watched_thread.h',
    'watch_socket.h',
]
install_headers(kea_util_headers, preserve_path: true, subdir: 'kea/util')
