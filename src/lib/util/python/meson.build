if not python_exe.found()
    subdir_done()
endif

configure_file(input: 'const2hdr.py', output: 'const2hdr.py', copy: true)
util_python_conf_data = configuration_data()
util_python_conf_data.set('PYTHON', PYTHON)
configure_file(
    input: 'gen_wiredata.py.in',
    output: 'gen_wiredata.py',
    configuration: util_python_conf_data,
)
