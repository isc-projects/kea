sources = []
if CRYPTO_DEP.name() == botan.name()
    sources += ['botan_hash.cc', 'botan_hmac.cc', 'botan_link.cc']
elif CRYPTO_DEP.name() == openssl.name()
    sources += ['openssl_hash.cc', 'openssl_hmac.cc', 'openssl_link.cc']
endif

kea_cryptolink_lib = shared_library(
    'kea-cryptolink',
    'cryptolink.cc',
    'crypto_hash.cc',
    'crypto_hmac.cc',
    'crypto_rng.cc',
    sources,
    dependencies: [CRYPTO_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '63.0.0',
)
LIBS_BUILT_SO_FAR = [kea_cryptolink_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
kea_cryptolink_headers = [
    'botan_common.h',
    'crypto_hash.h',
    'crypto_hmac.h',
    'cryptolink.h',
    'crypto_rng.h',
    'openssl_common.h',
]
install_headers(
    kea_cryptolink_headers,
    preserve_path: true,
    subdir: 'kea/cryptolink',
)
