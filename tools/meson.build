tools_conf_data = configuration_data()
tools_conf_data.set('prefix', PREFIX)
tools_conf_data.set('sysconfdir', '${prefix}/' + SYSCONFDIR)
tools_conf_data.set('localstatedir', '${prefix}/' + LOCALSTATEDIR)
tools_conf_data.set('exec_prefix', '${prefix}')
tools_conf_data.set('libdir', '${exec_prefix}/' + LIBDIR)
tools_conf_data.set('SEP', '+')
if BISON.found()
    tools_conf_data.set('YACC', BISON.full_path())
else
    tools_conf_data.set('YACC', 'bison')
endif
if AWK.found()
    tools_conf_data.set('AWK', AWK.full_path())
else
    tools_conf_data.set('AWK', 'awk')
endif
PATH_REPLACER = configure_file(
    input: 'path_replacer.sh.in',
    output: 'path_replacer.sh',
    configuration: tools_conf_data,
)
configure_file(
    input: 'extract_bnf.sh.in',
    output: 'extract_bnf.sh',
    configuration: tools_conf_data,
)
