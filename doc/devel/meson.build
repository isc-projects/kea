if not DOXYGEN.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()
make_devel_conf_data = configuration_data()
make_devel_conf_data.set('builddir', current_build_dir)
make_devel_conf_data.set('srcdir', current_source_dir)
make_devel_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
make_devel_conf_data.set('TOP_SOURCE_DIR', TOP_SOURCE_DIR)
make_devel = configure_file(
    input: 'make-devel.sh.in',
    output: 'make-devel.sh',
    configuration: make_devel_conf_data,
)
run_target('devel', command: make_devel)
