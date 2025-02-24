if not PYTHON.found()
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
make_conf_data.set('PYTHON', PYTHON.full_path())
make_conf_data.set('TOP_SOURCE_DIR', TOP_SOURCE_DIR)
if PDFLATEX.found()
    make_conf_data.set('HAVE_PDFLATEX', 'yes')
    pdflatex = PDFLATEX.full_path()
else
    make_conf_data.set('HAVE_PDFLATEX', 'no')
    pdflatex = 'false'
endif
make_conf_data.set('PDFLATEX_AND_OPTS', pdflatex + ' -interaction nonstopmode')
make_conf_data.set('SPHINXBUILD', SPHINX.full_path())
make_conf_data.set('sphinxopts', ' '.join(sphinxopts))
if PLANTUML.found()
    make_conf_data.set('HAVE_PLANTUML', 'yes')
    plantuml = PLANTUML.full_path()
else
    make_conf_data.set('HAVE_PLANTUML', 'no')
    plantuml = 'false'
endif
make_conf_data.set('PLANTUML', plantuml)
make_conf_data.set('umls', ' '.join(umls))
make_conf_data.set('svgs', ' '.join(svgs))
if XMLLINT.found()
    make_conf_data.set('HAVE_XMLLINT', 'yes')
else
    make_conf_data.set('HAVE_XMLLINT', 'no')
endif
tumls = ['uml/tkey.uml', 'uml/update.uml']
make_conf_data.set('tumls', ' '.join(tumls))
make_conf_data.set('txts', ' '.join(txts))
if PIP_COMPILE.found()
    make_conf_data.set('HAVE_PIP_COMPILE', 'yes')
else
    make_conf_data.set('HAVE_PIP_COMPILE', 'no')
endif
make_conf_data.set('man8s', ' '.join(man8s))
make_conf_data.set('PREFIX', PREFIX)
docdir = f'@PREFIX@/@DATADIR@/kea'
make_conf_data.set('docdir', docdir)
make_conf_data.set('INSTALL', INSTALL.full_path())
mandir = get_option('mandir')
mandir8 = f'@PREFIX@/@mandir@/man8/'
make_conf_data.set('mandir8', mandir8)

if SPHINX.found()
    make_doc = configure_file(
        input: 'make-doc.sh.in',
        output: 'make-doc.sh',
        configuration: make_conf_data,
    )
    run_target('doc', command: [make_doc])
endif
make_install = configure_file(
    input: 'make-install.sh.in',
    output: 'make-install.sh',
    configuration: make_conf_data,
)
make_mes_doc = configure_file(
    input: 'make-mes-doc.sh.in',
    output: 'make-mes-doc.sh',
    configuration: make_conf_data,
)
make_uml = configure_file(
    input: 'make-uml.sh.in',
    output: 'make-uml.sh',
    configuration: make_conf_data,
)
make_update_python_dependencies = configure_file(
    input: 'make-update-python-dependencies.sh.in',
    output: 'make-update-python-dependencies.sh',
    configuration: make_conf_data,
)
run_target('mes-doc', command: [make_mes_doc])
run_target('uml', command: [make_uml])
run_target(
    'update-python-dependencies',
    command: [make_update_python_dependencies],
)
meson.add_install_script(make_install)
