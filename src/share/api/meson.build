list = run_command(
    GRABBER,
    TOP_SOURCE_DIR / 'src/share/api',
    '[a-z]*.json',
    check: true,
)
api_files = list.stdout().strip().split('\n')
install_data(api_files, install_dir: DATADIR / 'kea/api')
