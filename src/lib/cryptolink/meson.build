sources = [
  'cryptolink.h',
  'cryptolink.cc',
  'crypto_hash.h',
  'crypto_hash.cc',
  'crypto_hmac.h',
  'crypto_hmac.cc',
  'crypto_rng.h',
  'crypto_rng.cc']

# in case of openssl
sources += [
  'openssl_link.cc',
  'openssl_common.h',
  'openssl_hash.cc',
  'openssl_compat.h',
  'openssl_hmac.cc']

foolib = static_library('kea-cryptolink',
                        sources,
                        include_directories : [lib_inc, configuration_inc],
                        #dependencies : glib_dep,
                        install : true)
