#!/bin/bash -eu
# Copyright (C) 2025 Ada Logics Ltd.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
################################################################################

# Compile log4cplus
cd $SRC/log4cplus
./configure --prefix=/usr --enable-static --disable-shared --with-pic
make -j"$(nproc)"
make install

# Configure flags
cd $SRC/kea
export CXXFLAGS="${CXXFLAGS:-} -gdwarf-4"
export LDFLAGS="${LDFLAGS:-} -gdwarf-4"

CPP_ARGS="-stdlib=libc++  \
  -DCHRONO_SAME_DURATION=1 -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR \
  -D_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION -D_GLIBCXX_USE_DEPRECATED=1"
LD_ARGS="-stdlib=libc++"

if [ "$SANITIZER" = "coverage" ]; then
  CPP_ARGS="${CPP_ARGS} -fprofile-instr-generate -fcoverage-mapping"
fi

if [ "$SANITIZER" = "coverage" ] || [ "$SANITIZER" = "introspector" ] || [ "$SANITIZER" = "none" ]; then
  SANITIZER_CHOICE=
else
  SANITIZER_CHOICE="-D b_sanitize=${SANITIZER}"
  CPP_ARGS="${CPP_ARGS} -fsanitize=fuzzer-no-link"
fi

meson setup build --prefix="$OUT" $SANITIZER_CHOICE -D cpp_std=c++17 \
  -D fuzz=enabled -D tests=enabled -D crypto=openssl -D default_library=static \
  -D default_both_libraries=static -D cpp_args="$CPP_ARGS" -D cpp_link_args="$LD_ARGS" \
  -D postgresql=enabled -D mysql=enabled -D krb5=enabled -D b_ndebug=true
meson compile --verbose -C build

# Package static library
find $SRC/kea/build/src/lib -type f -name '*.o' -print0 | xargs -0 llvm-ar rcsD libkea.a
llvm-ranlib libkea.a

# Find necessary static libraries
BUILD_BASEDIR="$SRC/kea/build/src"
KEA_STATIC_LIBS="/usr/lib/liblog4cplus.a libkea.a  "
KEA_STATIC_LIBS+=$(find $BUILD_BASEDIR/bin \( -path '/src/kea/build/src/bin/dhcp4/*' -o -path '/src/kea/build/src/bin/dhcp6/*' \) -prune -o -type f -name '*.a' -print)
KEA_STATIC_LIBS_TEST="$KEA_STATIC_LIBS $SRC/kea/build/subprojects/googletest-1.15.2/googletest/libgtest-all.a"

INCLUDES="-I. -I$SRC -I$SRC/kea-fuzzer -Isrc -Ibuild -Isrc/lib -Isrc/bin -Isrc/hooks -Isrc/hooks/d2 -Isrc/hooks/d2/gss_tsig "
INCLUDES+="-Isrc/hooks/dhcp/pgsql -Isrc/hooks/dhcp/mysql -Isrc/hooks/dhcp/user_chk -I/usr/include/postgresql -I/usr/include/mariadb"
KEA_INCLUDES="$INCLUDES -I/src/kea/subprojects/googletest-1.15.2/googletest/include -Ifuzz"
LIBS="-lpthread -ldl -lm -lc++ -lc++abi -lssl -lcrypto -lkrb5 -lgssapi_krb5"
export CXXFLAGS="${CXXFLAGS} -std=c++17 -stdlib=libc++ -Wno-unused-parameter -Wno-unused-value"

# Build non-dhcp specific fuzzers
for fuzzer in fuzz_cc fuzz_d2 fuzz_agent fuzz_util fuzz_dhcpsrv fuzz_dhcpsrv_csv_lease fuzz_dns fuzz_encode fuzz_cryptolink
do
  extra_lib=""
  case "$fuzzer" in fuzz_hook_tsig)
    extra_lib="$SRC/kea/build/src/hooks/d2/gss_tsig/libddns_gss_tsig.a"
    ;;
  esac
  
  # fuzz_dns, fuzz_encode, and fuzz_cryptolink don't need helper_func.cc
  if [ "$fuzzer" = "fuzz_dns" ] || [ "$fuzzer" = "fuzz_encode" ] || [ "$fuzzer" = "fuzz_cryptolink" ]; then
    $CXX $CXXFLAGS "$SRC/kea-fuzzer/${fuzzer}.cc"  \
      -Wl,--start-group $KEA_STATIC_LIBS $extra_lib -Wl,--end-group  \
      $INCLUDES $LIBS $LIB_FUZZING_ENGINE -o "$OUT/${fuzzer}"
  else
    $CXX $CXXFLAGS "$SRC/kea-fuzzer/helper_func.cc" \
      "$SRC/kea-fuzzer/${fuzzer}.cc"  \
      -Wl,--start-group $KEA_STATIC_LIBS $extra_lib -Wl,--end-group  \
      $INCLUDES $LIBS $LIB_FUZZING_ENGINE -o "$OUT/${fuzzer}"
  fi

  if [ -f "$SRC/kea-fuzzer/${fuzzer}.dict" ]; then
    cp $SRC/kea-fuzzer/${fuzzer}.dict $OUT
  fi
done

for DHCPVER in 4 6
do
  for fuzzer in fuzz_dhcp_parser fuzz_eval fuzz_dhcp_pkt fuzz_pgsql \
                fuzz_mysql fuzz_dhcp_pkt_process fuzz_hook_run_script \
                fuzz_hook_radius fuzz_hook_ddns_tuning fuzz_hook_lease_query \
                fuzz_hook_flex_id fuzz_hook_user_chk
  do
    extra_lib=""
    case "$fuzzer" in fuzz_pgsql)
      extra_lib="$SRC/kea-fuzzer/pgmock.cc "
      extra_lib+="$SRC/kea/build/src/hooks/dhcp/pgsql/libdhcp_pgsql.a"
      ;;
    esac
    case "$fuzzer" in fuzz_mysql)
      extra_lib="$SRC/kea-fuzzer/mysqlmock.cc "
      extra_lib+="$SRC/kea/build/src/hooks/dhcp/mysql/libdhcp_mysql.a"
      ;;
    esac
    case "$fuzzer" in fuzz_dhcp_pkt_process)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/lease_cmds/libdhcp_lease_cmds.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_run_script)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/run_script/libdhcp_run_script.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_radius)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/radius/libdhcp_radius.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_ddns_tuning)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/ddns_tuning/libdhcp_ddns_tuning.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_lease_query)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/lease_query/libdhcp_lease_query.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_flex_id)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/flex_id/libdhcp_flex_id.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac
    case "$fuzzer" in fuzz_hook_user_chk)
      extra_lib="$SRC/kea/build/src/hooks/dhcp/user_chk/libdhcp_user_chk.a"
      cp $SRC/kea-fuzzer/fuzz_dhcp_pkt.dict $OUT/${fuzzer}${DHCPVER}.dict
      ;;
    esac

    $CXX $CXXFLAGS -Wl,--start-group "$SRC/kea-fuzzer/helper_func.cc" \
      "$SRC/kea-fuzzer/${fuzzer}${DHCPVER}.cc" $extra_lib \
      $KEA_STATIC_LIBS $BUILD_BASEDIR/bin/dhcp$DHCPVER/libdhcp$DHCPVER.a \
      -Wl,--end-group $INCLUDES $LIBS \
      $LIB_FUZZING_ENGINE -o "$OUT/${fuzzer}${DHCPVER}"

    if [ -f "$SRC/kea-fuzzer/${fuzzer}.dict" ]; then
      cp $SRC/kea-fuzzer/${fuzzer}.dict $OUT/${fuzzer}${DHCPVER}.dict
    fi
  done

  # Compile fuzzers from kea repository
  for fuzzer in fuzz_config_kea_dhcp fuzz_http_endpoint_kea_dhcp fuzz_packets_kea_dhcp fuzz_unix_socket_kea_dhcp
  do
    # Skip fuzz_http_endpoint_kea_dhcp6 as it requires real IPv6 binding which is not enabled in OSS-Fuzz
    if [ "$fuzzer" = "fuzz_http_endpoint_kea_dhcp" ] && [ "$DHCPVER" = "6" ]; then
      continue
    fi

    $CXX $CXXFLAGS -Wl,--start-group "$SRC/kea/fuzz/${fuzzer}${DHCPVER}.cc" \
      $SRC/kea/fuzz/fuzz.cc $KEA_STATIC_LIBS_TEST \
      $BUILD_BASEDIR/bin/dhcp$DHCPVER/libdhcp$DHCPVER.a \
      $KEA_INCLUDES $LIBS $LIB_FUZZING_ENGINE -Wl,--end-group \
      -o "$OUT/${fuzzer}${DHCPVER}"
  done
done

# Prepare maximum size option for configuration parsing related fuzzers
for fuzzer in fuzz_eval4 fuzz_eval6 fuzz_dhcp_parser4 fuzz_dhcp_parser6 \
              fuzz_dhcp_pkt4 fuzz_dhcp_pkt6 fuzz_cc fuzz_d2 fuzz_agent \
              fuzz_config_kea_dhcp4 fuzz_config_kea_dhcp6
do
    echo -e "[libfuzzer]\nmax_len=25600" > $OUT/$fuzzer.options
done

# Prepare the seeds
zip -j $OUT/fuzz_dhcpsrv_seed_corpus.zip $SRC/kea-fuzzer/corp/*.json
zip -j $OUT/fuzz_dhcp_parser4_seed_corpus.zip $SRC/kea-fuzzer/corp/*.json
zip -j $OUT/fuzz_dhcp_parser6_seed_corpus.zip $SRC/kea-fuzzer/corp/*.json
zip -j $OUT/fuzz_agent_seed_corpus.zip $SRC/kea/src/bin/agent/tests/testdata/*.json
zip -j $OUT/fuzz_d2_seed_corpus.zip $SRC/kea/src/bin/d2/tests/testdata/*.json
