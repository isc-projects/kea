project('kea', 'cpp',
        version : '1.5',
        default_options : ['warning_level=3', 'cpp_std=c++14'])

conf_data = configuration_data()
conf_data.set_quoted('VERSION', '1.5')
conf_data.set('TEST_DATA_TOPBUILDDIR', '/tmp/kea-gtest')
configure_file(#input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

configuration_inc = include_directories('.')
lib_inc = include_directories('src/lib')
gtest_inc = include_directories('/usr/src/googletest/googletest/include')

#kea_version_h = custom_target('kea_version_h',
#                              output : 'kea_version.h',
#                              command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])
vcs_tag(input : 'kea_version.h.in',
        output : 'kea_version.h',
        replace_string : '@KEA_SRCID@')



subdir('src/lib/asiolink')
subdir('src/lib/cc')
subdir('src/lib/cryptolink')
subdir('src/lib/dhcp')
subdir('src/lib/dns')
subdir('src/lib/exceptions')
subdir('src/lib/log')
subdir('src/lib/mysql')
subdir('src/lib/stats')
subdir('src/lib/util')
subdir('src/lib/util/io')
subdir('src/lib/util/threads')

subdir('src/lib/log/compiler')
subdir('src/lib/config')        # depends on compiler
subdir('src/lib/database')      # depends on compiler
subdir('src/lib/dhcp_ddns')     # depends on compiler
subdir('src/lib/dhcpsrv')       # depends on compiler
subdir('src/lib/hooks')         # depends on compiler
subdir('src/lib/http')          # depends on compiler
subdir('src/lib/process')       # depends on compiler

# subdir('src/lib/util/threads/tests') TODO: fix setting gtest paths in config.h

#executable('kea',
#           'src/lib/util/signal_set.cc',
#           include_directories : configuration_inc,
#           install : true)
