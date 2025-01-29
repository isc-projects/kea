sources = []
if crypto == botan
    sources += [
        'botan_common.h',
        'botan_hash.cc',
        'botan_hmac.cc',
        'botan_link.cc',
    ]
elif crypto == openssl
    sources += [
        'openssl_common.h',
        'openssl_hash.cc',
        'openssl_hmac.cc',
        'openssl_link.cc',
    ]
endif

kea_cryptolink_lib = library(
    'kea-cryptolink',
    'cryptolink.cc',
    'cryptolink.h',
    'crypto_hash.cc',
    'crypto_hash.h',
    'crypto_hmac.cc',
    'crypto_hmac.h',
    'crypto_rng.cc',
    'crypto_rng.h',
    sources,
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_cryptolink_lib] + LIBS_BUILT_SO_FAR
subdir('tests')
