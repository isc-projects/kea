if not DOXYGEN.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()
make_devel_conf_data = configuration_data()
make_devel_conf_data.set('builddir', current_build_dir)
make_devel_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
configure_file(
    input: 'make-devel.sh.in',
    output: 'make-devel.sh',
    configuration: make_devel_conf_data,
)
make_devel = f'@current_build_dir@/make-devel.sh'
run_target('devel', command: [CD_AND_RUN, current_source_dir, make_devel])
