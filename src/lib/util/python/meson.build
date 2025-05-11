if not PYTHON.found()
    subdir_done()
endif

configure_file(input: 'const2hdr.py', output: 'const2hdr.py', copy: true)
util_python_conf_data = configuration_data()
util_python_conf_data.set('PYTHON', PYTHON.full_path())
configure_file(
    input: 'gen_wiredata.py.in',
    output: 'gen_wiredata.py',
    configuration: util_python_conf_data,
)
