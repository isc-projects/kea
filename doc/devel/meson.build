if not doxygen_exe.found()
    subdir_done()
endif

make_devel_conf_data = configuration_data()
make_devel_conf_data.set('builddir', meson.current_build_dir())
make_devel_conf_data.set('srcdir', meson.current_source_dir())
make_devel_conf_data.set('PACKAGE_VERSION', project_version)
make_devel = configure_file(
    input: 'make-devel.sh.in',
    output: 'make-devel.sh',
    configuration: make_devel_conf_data,
)
run_target('make-devel', command: [make_devel])
