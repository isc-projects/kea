# INSTALLATION INSTRUCTIONS

This document explains briefly how to install Kea, either by compiling
from sources or using pre-compiled packages.

## Compilation from sources

Set up the build. If you want to alter Kea's installation path, or want to
make sure that certain capabilities are included (e.g. enabling MySQL or
PostgreSQL), you will need to specify these as options to the command (run
"meson configure" for a list of options).

```shell
$ meson setup build
```

If your environment is missing dependencies, the command will exit
with error and should emit sufficient information to guide you on how to
proceed. A detailed account of the setup process is captured in
build/meson-logs/meson-log.txt.

Build it. Once you've successfully set up the build, run "meson compile" to
build it.

```shell
  $ meson compile -C build
```

Install it. Depending on your target directory, this step will likely
require a root privileges. You can install the software by running:

```shell
  $ meson install -C build
```

Kea depends on C++ compiler, meson, ninja, boost (at least includes, but many
OSes require boost-system library), log4cplus and one crypto library (either
OpenSSL or Botan) for compilation.

Optional backends (MySQL and PostgreSQL) have additional dependencies. For
detailed installation directions, see the documentation in the
doc/sphinx/arm/install.rst text file or on the Kea online docs:
https://kea.readthedocs.io/en/stable/arm/install.html.

Other optional dependencies are Kerberos with GSSAPI support for the GSS-TSIG
hook library and libyang and sysrepo for providing a YANG/NETCONF interface.

You can find current OS-specific build/installation
instructions in our knowledge base at https://kb.isc.org/docs/installing-kea.

## Precompiled packages

Precompiled packages are available for easy installation. See
https://kea.readthedocs.io/en/stable/arm/install.html#packages for details.