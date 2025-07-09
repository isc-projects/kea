# PostgreSQL requires restricted permissions on the key files.
current_source_dir = meson.current_source_dir()
configure_file(
    command: ['chmod', 'og-rwx', f'@current_source_dir@/kea-client.key'],
    input: 'kea-client.key',
    output: 'kea-client.key',
)
configure_file(
    command: ['chmod', 'og-rwx', f'@current_source_dir@/kea-other.key'],
    input: 'kea-other.key',
    output: 'kea-other.key',
)
