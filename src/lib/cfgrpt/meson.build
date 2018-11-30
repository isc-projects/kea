sources = [
  'config_report.cc',
  'config_report.h',
  'cfgrpt.cc']

http_messages_ch = custom_target('http_messages.[ch]',
                                 output : ['http_messages.cc',
                                           'http_messages.h'],
                                 input : 'http_messages.mes',
                                 command : [kea_msg_compiler, '-d', meson.current_build_dir(), '@INPUT@'])
report_file = $(abs_top_builddir)/config.report

config_report.cc: $(report_file)
	${SHELL} $(top_srcdir)/tools/mk_cfgrpt.sh $(report_file) $(top_builddir)/src/lib/cfgrpt/config_report.cc


http_lib = static_library('cfgrpt',
                          sources,
                          include_directories : [lib_inc, configuration_inc],
                          install : true)
