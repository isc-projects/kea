list = run_command('grabber.sh', check: true)
api_files = list.stdout().strip().split('\n')
DATADIR = get_option('datadir')
INSTALL_DIR = f'@DATADIR@/kea/api'
install_data(api_files, install_dir: INSTALL_DIR)
