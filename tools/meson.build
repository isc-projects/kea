tools_conf_data = configuration_data()
tools_conf_data.set('prefix', PREFIX)
tools_conf_data.set('sysconfdir', '${prefix}/' + get_option('sysconfdir'))
tools_conf_data.set('localstatedir', '${prefix}/' + get_option('localstatedir'))
tools_conf_data.set('exec_prefix', '${prefix}')
tools_conf_data.set('libdir', '${exec_prefix}/' + get_option('libdir'))
tools_conf_data.set('SEP', '+')
if bison_exe.found()
    tools_conf_data.set('YACC', bison_exe.full_path())
else
    tools_conf_data.set('YACC', 'bison')
endif
if awk_exe.found()
    tools_conf_data.set('AWK', awk_exe.full_path())
else
    tools_conf_data.set('AWK', 'awk')
endif
configure_file(
    input: 'path_replacer.sh.in',
    output: 'path_replacer.sh',
    configuration: tools_conf_data,
)
configure_file(
    input: 'extract_bnf.sh.in',
    output: 'extract_bnf.sh',
    configuration: tools_conf_data,
)
