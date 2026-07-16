#!/usr/bin/env python3

# Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Developed by AdaLogics under contract to ISC.

"""pkg-config Query Interface and Metadata Extraction Module.

This module provides a cached interface to the system's pkg-config tool for querying
information about installed libraries and packages. It implements the PcCache class
which efficiently retrieves and caches package metadata including versions, URLs,
dependencies (Requires/Requires.private), and linked libraries.

The pkg-config tool is a standard utility on Unix-like systems that provides
a unified interface for querying installed library information. This module wraps
pkg-config to enable dependency discovery and enrichment during SBOM generation.
"""

import re
import shlex
import subprocess
from typing import Optional

# Regular expression to extract package names from pkg-config Requires output.
# Matches alphanumeric package names, allowing dots, underscores, plus signs, and hyphens.
# Example: "openssl >= 1.1.0" -> captures "openssl"
_REQ_TOKEN = re.compile(r'^[A-Za-z0-9_.+-]+')

# Regular expression to extract library names from linker flags.
# Matches the -l flag followed by the library name.
# Example: "-lpthread" -> captures "pthread"
_LIB_TOKEN = re.compile(r'^-l([A-Za-z0-9_.+-]+)$')


def _run(cmd: list[str]) -> Optional[str]:
    """Execute a shell command and return its output.

    Args:
        cmd: List of command arguments to execute.

    Returns:
        Stripped output string if successful, None if command fails.

    Note:
        stderr is redirected to DEVNULL to suppress error messages.
    """
    try:
        return subprocess.check_output(cmd, text=True, stderr=subprocess.DEVNULL).strip()
    except Exception:
        return None


class PcCache:
    """Caching wrapper for pkg-config queries to minimize system calls.

    This class provides methods to query package information from pkg-config
    while caching results to avoid redundant system calls. It supports checking
    package existence, retrieving metadata (version, URL, .pc file path),
    discovering dependencies, and extracting linked libraries.

    Attributes:
        _exists: Cache for package existence checks (name -> bool).
        _info: Cache for package metadata (name -> dict).
        _requires: Cache for package dependencies (name -> list of names).
        _libs: Cache for linked libraries (name -> list of library names).
    """

    def __init__(self):
        """Initialise empty caches for pkg-config query results."""
        self._exists: dict[str, bool] = {}
        self._info: dict[str, dict] = {}
        self._requires: dict[str, list[str]] = {}
        self._libs: dict[str, list[str]] = {}

    def exists(self, name: str) -> bool:
        """Check if a pkg-config package exists on the system.

        Args:
            name: Package name to check (e.g., 'openssl', 'libcurl').

        Returns:
            True if the package is known to pkg-config, False otherwise.

        Note:
            Results are cached to avoid repeated system calls for the same package.
        """
        if name in self._exists:
            return self._exists[name]
        try:
            subprocess.check_call(['pkg-config', '--exists', name],
                                  stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            self._exists[name] = True
        except Exception:
            self._exists[name] = False
        return self._exists[name]

    def info(self, name: str) -> dict:
        """Retrieve comprehensive metadata for a pkg-config package.

        Queries pkg-config for package version, URL/homepage, and .pc file location.
        This information is used to populate SPDX package metadata.

        Args:
            name: Package name to query.

        Returns:
            Dictionary containing available metadata with keys:
                - 'version': Package version string (from --modversion)
                - 'url': Package URL or homepage (from --variable=url or --variable=homepage)
                - 'pcfile': Absolute path to the .pc file (from --path)

        Note:
            Results are cached. Only successfully retrieved fields are included
            in the returned dictionary.
        """
        if name in self._info:
            return self._info[name]
        data = {}

        # Query package version
        version = _run(['pkg-config', '--modversion', name])
        if version:
            data['version'] = version

        # Query package URL (try 'url' variable first, then 'homepage' as fallback)
        url = _run(['pkg-config', '--variable=url', name]) or _run(['pkg-config', '--variable=homepage', name])
        if url:
            data['url'] = url

        # Query .pc file location for reference
        path = _run(['pkg-config', '--path', name])
        if path:
            data['pcfile'] = path

        self._info[name] = data
        return data

    def requires(self, name: str) -> list[str]:
        """Discover all direct dependencies of a pkg-config package.

        Queries both public (Requires) and private (Requires.private) dependencies
        to build a complete dependency graph. This is essential for transitive
        dependency discovery in SBOM generation.

        Args:
            name: Package name to query dependencies for.

        Returns:
            Sorted list of unique package names that this package depends on.
            Self-references are automatically excluded.

        Note:
            The method parses pkg-config output to extract package names from
            potentially complex dependency specifications (e.g., "zlib >= 1.2.11").
            Results are cached and deduplicated.
        """
        if name in self._requires:
            return self._requires[name]
        required_packages: set[str] = set()

        # Query both public and private dependencies for complete coverage
        for flag in ('--print-requires', '--print-requires-private'):
            out = _run(['pkg-config', flag, name]) or ''
            for line in out.splitlines():
                # Extract package name from dependency specification
                # Example: "openssl >= 1.1.0" -> "openssl"
                match = _REQ_TOKEN.match(line.strip())
                if not match:
                    continue
                package = match.group(0).rstrip(',')
                # Exclude self-references and empty names
                if package and package != name:
                    required_packages.add(package)

        self._requires[name] = sorted(required_packages)
        return self._requires[name]

    def libs(self, name: str) -> list[str]:
        """Extract library names from pkg-config linker flags.

        Queries both public (--libs) and private (--libs-private) linker flags
        to discover all libraries that would be linked when using this package.
        This helps identify both direct library dependencies and transitive
        system libraries.

        Args:
            name: Package name to query libraries for.

        Returns:
            Sorted list of unique library names (without the 'lib' prefix or '-l' flag).
            For example, if pkg-config returns "-lpthread -lssl -lcrypto",
            this method returns ["crypto", "pthread", "ssl"].

        Note:
            Results are cached. Only -l flags are processed; other linker flags
            like -L or -Wl are ignored.
        """
        if name in self._libs:
            return self._libs[name]
        library_names: set[str] = set()

        # Query both public and private library flags for complete coverage
        for flag in ('--libs', '--libs-private'):
            out = _run(['pkg-config', flag, name]) or ''
            # Use shlex to properly handle quoted strings and whitespace
            for token in shlex.split(out):
                # Extract library name from -l flags
                # Example: "-lpthread" -> "pthread"
                match = _LIB_TOKEN.match(token)
                if match:
                    library_names.add(match.group(1))

        self._libs[name] = sorted(library_names)
        return self._libs[name]
