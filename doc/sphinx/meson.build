if not python_exe.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()

sphinxbuilddir = './_build'
abs_sphinxbuilddir = f'@current_build_dir@/_build'

sphinxopts = ['-v', '-E', '-a', '-W', f'-c @current_source_dir@']

static_sources = [
    'static/kea-imageonly-100bw.png',
    'static/kea-logo-100x70.png',
    'static/kea-logo-200.png',
    'static/kea.css',
]

# ARM
rst_arm_sources = [
    'index.rst',
    'manpages.rst',
    'umls.rst',
    'debug-messages.rst',
    'kea-messages.rst',
]

list = run_command('grabber.sh', current_source_dir, 'arm', 'rst', check: true)
rst_arm_sources += list.stdout().strip().split('\n')

list = run_command(
    'grabber.sh',
    current_source_dir,
    'grammar',
    'rst',
    check: true,
)
rst_arm_sources = list.stdout().strip().split('\n')

main_sources = rst_arm_sources + ['conf.py'] + static_sources

# mans
list = run_command('grabber.sh', current_source_dir, 'man', 'rst', check: true)
rst_man_sources = list.stdout().strip().split('\n')

man8s = []
foreach file : rst_man_sources
    man8 = file.replace('.rst', '')
    man8s += [man8]
endforeach

man_sources = rst_man_sources + ['conf.py']

api_dir = f'@TOP_SOURCE_DIR@/src/share/api'
list = run_command('grabber.sh', '/', api_dir, 'json', check: true)
api_files = list.stdout().strip().split('\n')

list = run_command('grabber.sh', '/', TOP_SOURCE_DIR, 'mes', check: true)
mes_files = list.stdout().strip().split('\n')

list = run_command('grabber.sh', current_source_dir, 'uml', 'uml', check: true)
umls = list.stdout().strip().split('\n')

list = run_command('grabber.sh', current_source_dir, 'uml', 'png', check: true)
pngs = list.stdout().strip().split('\n')

list = run_command('grabber.sh', current_source_dir, 'uml', 'svg', check: true)
svgs = list.stdout().strip().split('\n')

list = run_command('grabber.sh', current_source_dir, 'uml', 'atxt', check: true)
txts = list.stdout().strip().split('\n')

make_conf_data = configuration_data()
make_conf_data.set('builddir', meson.current_build_dir())
make_conf_data.set('srcdir', meson.current_source_dir())
make_conf_data.set('sphinxbuilddir', sphinxbuilddir)
make_conf_data.set('abs_sphinxbuilddir', abs_sphinxbuilddir)
make_conf_data.set('PYTHON', python_exe.full_path())
make_conf_data.set('TOP_SOURCE_DIR', TOP_SOURCE_DIR)
if pdflatex_exe.found()
    make_conf_data.set('HAVE_PDFLATEX', 'yes')
    pdflatex = pdflatex_exe.full_path()
else
    make_conf_data.set('HAVE_PDFLATEX', 'no')
    pdflatex = 'false'
endif
make_conf_data.set('PDFLATEX_AND_OPTS', pdflatex + ' -interaction nonstopmode')
make_conf_data.set('SPHINXBUILD', sphinx_exe.full_path())
make_conf_data.set('sphinxopts', ' '.join(sphinxopts))
if plantuml_exe.found()
    make_conf_data.set('HAVE_PLANTUML', 'yes')
    plantuml = plantuml_exe.full_path()
else
    make_conf_data.set('HAVE_PLANTUML', 'no')
    plantuml = 'false'
endif
make_conf_data.set('PLANTUML', plantuml)
make_conf_data.set('umls', ' '.join(umls))
make_conf_data.set('svgs', ' '.join(svgs))
if xmllint_exe.found()
    make_conf_data.set('HAVE_XMLLINT', 'yes')
else
    make_conf_data.set('HAVE_XMLLINT', 'no')
endif
tumls = ['uml/tkey.uml', 'uml/update.uml']
make_conf_data.set('tumls', ' '.join(tumls))
make_conf_data.set('txts', ' '.join(txts))
if pip_compile_exe.found()
    make_conf_data.set('HAVE_PIP_COMPILE', 'yes')
else
    make_conf_data.set('HAVE_PIP_COMPILE', 'no')
endif
make_conf_data.set('man8s', ' '.join(man8s))
make_conf_data.set('PREFIX', PREFIX)
docdir = f'@PREFIX@/@DATADIR@/kea'
make_conf_data.set('docdir', docdir)
make_conf_data.set('INSTALL', install_exe.full_path())
mandir = get_option('mandir')
mandir8 = f'@PREFIX@/@mandir@/man8/'
make_conf_data.set('mandir8', mandir8)

if sphinx_exe.found()
    make_doc = configure_file(
        input: 'make-doc.sh.in',
        output: 'make-doc.sh',
        configuration: make_conf_data,
    )
    run_target('make-doc', command: [make_doc])
endif
regen_doc = configure_file(
    input: 'regen-doc.sh.in',
    output: 'regen-doc.sh',
    configuration: make_conf_data,
)
make_install = configure_file(
    input: 'make-install.sh.in',
    output: 'make-install.sh',
    configuration: make_conf_data,
)
run_target('regen-doc', command: [regen_doc])
meson.add_install_script(make_install)
