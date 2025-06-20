if not PYTHON.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()

sphinxbuilddir = './_build'
abs_sphinxbuilddir = current_build_dir / '_build'

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

list = run_command(GRABBER, current_source_dir / 'arm', '*.rst', check: true)
rst_arm_sources += list.stdout().strip().split('\n')

list = run_command(GRABBER, current_source_dir / 'grammar', '*.rst', check: true)
rst_arm_sources += list.stdout().strip().split('\n')

main_sources = rst_arm_sources + ['conf.py'] + static_sources

# mans
list = run_command(GRABBER, current_source_dir / 'man', '*.rst', check: true)
rst_man_sources = list.stdout().strip().split('\n')

man8s = []
foreach file : rst_man_sources
    man8 = file.replace('.rst', '')
    man8s += [man8]
endforeach

man_sources = rst_man_sources + ['conf.py']

api_dir = TOP_SOURCE_DIR / 'src/share/api'
list = run_command(GRABBER, api_dir, '*.json', check: true)
api_files = list.stdout().strip().split('\n')

list = run_command(GRABBER, TOP_SOURCE_DIR, '*.mes', check: true)
mes_files = list.stdout().strip().split('\n')

list = run_command(GRABBER, current_source_dir / 'uml', '*.uml', check: true)
umls = list.stdout().strip().split('\n')

list = run_command(GRABBER, current_source_dir / 'uml', '*.png', check: true)
pngs = list.stdout().strip().split('\n')

list = run_command(GRABBER, current_source_dir / 'uml', '*.svg', check: true)
svgs = list.stdout().strip().split('\n')

list = run_command(GRABBER, current_source_dir / 'uml', '*.atxt', check: true)
txts = list.stdout().strip().split('\n')

doc_conf = configuration_data()
doc_conf.set('builddir', meson.current_build_dir())
doc_conf.set('srcdir', meson.current_source_dir())
doc_conf.set('sphinxbuilddir', sphinxbuilddir)
doc_conf.set('abs_sphinxbuilddir', abs_sphinxbuilddir)
doc_conf.set('PYTHON', PYTHON.full_path())
doc_conf.set('TOP_SOURCE_DIR', TOP_SOURCE_DIR)
if PDFLATEX.found()
    doc_conf.set('HAVE_PDFLATEX', 'yes')
    pdflatex = PDFLATEX.full_path()
else
    doc_conf.set('HAVE_PDFLATEX', 'no')
    pdflatex = 'false'
endif
doc_conf.set('PDFLATEX_AND_OPTS', pdflatex + ' -interaction nonstopmode')
if SPHINX.found()
    doc_conf.set('SPHINXBUILD', SPHINX.full_path())
else
    doc_conf.set('SPHINXBUILD', 'false')
endif
doc_conf.set('sphinxopts', ' '.join(sphinxopts))
if PLANTUML.found()
    doc_conf.set('HAVE_PLANTUML', 'yes')
    doc_conf.set('PLANTUML', PLANTUML.full_path())
else
    doc_conf.set('HAVE_PLANTUML', 'no')
    doc_conf.set('PLANTUML', 'false')
endif
doc_conf.set('umls', ' '.join(umls))
doc_conf.set('svgs', ' '.join(svgs))
if XMLLINT.found()
    doc_conf.set('HAVE_XMLLINT', 'yes')
else
    doc_conf.set('HAVE_XMLLINT', 'no')
endif
tumls = ['tkey.uml', 'update.uml']
doc_conf.set('tumls', ' '.join(tumls))
doc_conf.set('txts', ' '.join(txts))
if PIP_COMPILE.found()
    doc_conf.set('HAVE_PIP_COMPILE', 'yes')
    doc_conf.set('PIP_COMPILE', PIP_COMPILE.full_path())
else
    doc_conf.set('HAVE_PIP_COMPILE', 'no')
    doc_conf.set('PIP_COMPILE', 'pip-compile')
endif
doc_conf.set('man8s', ' '.join(man8s))
doc_conf.set('PREFIX', PREFIX)
docdir = DATADIR / 'doc/kea'
doc_conf.set('docdir', docdir)
doc_conf.set('INSTALL', INSTALL.full_path())
mandir8 = MANDIR / 'man8'
doc_conf.set('mandir8', mandir8)

make_doc = configure_file(
    input: 'make-doc.sh.in',
    output: 'make-doc.sh',
    configuration: doc_conf,
)
install_docs = configure_file(
    input: 'install-docs.sh.in',
    output: 'install-docs.sh',
    configuration: doc_conf,
)
make_mes_doc = configure_file(
    input: 'make-mes-doc.sh.in',
    output: 'make-mes-doc.sh',
    configuration: doc_conf,
)
make_uml = configure_file(
    input: 'make-uml.sh.in',
    output: 'make-uml.sh',
    configuration: doc_conf,
)
make_update_python_dependencies = configure_file(
    input: 'update-python-dependencies.sh.in',
    output: 'update-python-dependencies.sh',
    configuration: doc_conf,
)

run_target('doc', command: [make_doc])
run_target('mes-doc', command: [make_mes_doc])
run_target('uml', command: [make_uml])
run_target(
    'update-python-dependencies',
    command: [make_update_python_dependencies],
)

meson.add_install_script(install_docs)
