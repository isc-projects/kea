list = run_command('grabber.sh', check: true)
api_files = list.stdout().strip().split('\n')
install_dir = f'@DATADIR@/kea/api'
install_data(api_files, install_dir: install_dir)
