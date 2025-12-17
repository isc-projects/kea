# How to run the python script meson2spdx

```
# Assume necessary packages for kea build and pkg-config are already installed in the running environment.

# Compile Kea and generate meson-info
pushd kea
export CXXFLAGS="${CXXFLAGS:-} -gdwarf-4"
export LDFLAGS="${LDFLAGS:-} -gdwarf-4"
CPP_ARGS="-stdlib=libc++  \
  -DCHRONO_SAME_DURATION=1 -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR \
  -D_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION -D_GLIBCXX_USE_DEPRECATED=1"
LD_ARGS="-stdlib=libc++"
meson subprojects download 
meson setup build -D cpp_std=c++17 -D crypto=openssl -D default_library=static \
  -D default_both_libraries=static -D cpp_args="$CPP_ARGS" -D cpp_link_args="$LD_ARGS" \
  -D postgresql=enabled -D mysql=enabled -D krb5=enabled
meson compile --verbose -C build
meson install -C build --destdir _stage
popd



# Assume all python code in the same directory meson2spdx
# Run the script
pushd meson2spdx
python3 meson2spdx.py -b ../kea/build -o sbom.spdx.json -r ../kea
popd

# Output in meson2spdx/sbom.spdx.json from the above command
cat meson2spdx/sbom.spdx.json

```

# sbom-conformance validation

```
go install github.com/google/sbom-conformance@latest
sbom-conformance -specs eo -sbom meson2spdx/sbom.spdx.json
sbom-conformance -specs spdx -sbom meson2spdx/sbom.spdx.json

```

# sbom-conformance result (eo and spdx2.3)

NTIA Minimum Elements

```
$ sbom-conformance -specs eo -sbom meson2spdx/sbom.spdx.json
Summary:
        Analyzed an SBOM with 27 package(s). 0 top-level conformance check(s) failed. 0 package(s) had at least one failing conformance check.

        The EO spec passed. 7/7 checks passed.

```

SPDX2.3

```
$ sbom-conformance -specs spdx -sbom meson2spdx/sbom.spdx.json
Summary:
        Analyzed an SBOM with 27 package(s). 0 top-level conformance check(s) failed. 0 package(s) had at least one failing conformance check.

        The SPDX spec passed. 12/12 checks passed.

```
