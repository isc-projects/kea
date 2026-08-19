# How to run the python script meson2spdx

The following were tested on Linux. The same approach should work on
other OSes, but the flags need some tweaking.

```shell
# Assume necessary packages for kea build and pkg-config are already installed in the running environment.

# Compile Kea and generate meson-info
export CXXFLAGS="${CXXFLAGS:-} -gdwarf-4"
export LDFLAGS="${LDFLAGS:-} -gdwarf-4"


# Tomek: The following exports were recommended by the AdaLogics team. It caused my compiler
# (g++ 13.3.0 on ubuntu 24.04.4 LTS) to fail. With them skipped, the compilation and SBOM
# generation succeeded.
CPP_ARGS="-stdlib=libc++  \
  -DCHRONO_SAME_DURATION=1 -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR \
  -D_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION -D_GLIBCXX_USE_DEPRECATED=1"
LD_ARGS="-stdlib=libc++"

meson subprojects download
meson setup build -D cpp_std=c++17 -D crypto=openssl -D default_library=static \
  -D default_both_libraries=static -D cpp_args="$CPP_ARGS" -D cpp_link_args="$LD_ARGS" \
  -D postgresql=enabled -D mysql=enabled -D krb5=enabled
meson compile --verbose -C build

# Run the script
cd tools/sbom
python3 meson2spdx.py -b ../../build -o sbom.spdx.json -r ../..

# Output in sbom.spdx.json from the above command
cat sbom.spdx.json
```

## sbom-conformance validation

SBOM conformance tool can be used to verify if the SBOM files generated
adhere to the standards:

```shell
go install github.com/google/sbom-conformance@latest
sbom-conformance -specs eo -sbom sbom.spdx.json
sbom-conformance -specs spdx -sbom sbom.spdx.json

```

## sbom-conformance result (eo and spdx2.3)

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
