# Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Developed by AdaLogics under contract to ISC.

"""SPDX 2.3 Document Generation Module.

This module converts a resolved dependency graph into a fully structured SPDX 2.3
JSON document. It implements the SPDX specification for Software Bill of Materials,
including package metadata, external references (PURLs), and dependency relationships.

The module uses string templates to construct the SPDX JSON structure efficiently,
and includes functionality to discover runtime system library dependencies by analysing
built binaries with ldd and mapping them to OS packages via dpkg/rpm.

SPDX (Software Package Data Exchange) is an open standard for communicating software
bill of materials information, including components, licenses, and security references.
"""

import json
import re
import subprocess
import uuid
from datetime import datetime, timezone
from pathlib import Path
from string import Template
from typing import Optional
from urllib.parse import urlparse


# SPDX 2.3 document template with placeholders for dynamic content
DOC_TEMPLATE = Template('''{
  "spdxVersion": "SPDX-2.3",
  "dataLicense": "CC0-1.0",
  "SPDXID": "SPDXRef-DOCUMENT",
  "name": "$DOC_NAME",
  "documentNamespace": "$DOC_NAMESPACE",
  "creationInfo": $CREATION_INFO,
  "packages": [
$PACKAGES
  ],
  "relationships": [
$RELATIONSHIPS
  ]
}''')

# Template for the root package (the project being analysed)
ROOT_PACKAGE_TEMPLATE = Template('''{
  "SPDXID": "$SPDXID",
  "name": "$NAME",
  "versionInfo": "$VERSION",
  "downloadLocation": "NOASSERTION",
  "filesAnalyzed": false,
  "licenseConcluded": "NOASSERTION",
  "supplier": "$SUPPLIER",
  "externalRefs": [
    {
      "referenceCategory": "PACKAGE-MANAGER",
      "referenceType": "purl",
      "referenceLocator": "$PURL"
    }
  ]
}''')

# Template for dependency packages (both build-time and runtime dependencies)
PACKAGE_TEMPLATE = Template('''{
  "SPDXID": "$SPDXID",
  "name": "$NAME",
  "versionInfo": "$VERSION",
  "downloadLocation": $DOWNLOAD,
  "filesAnalyzed": false,
  "licenseConcluded": "NOASSERTION",
  "supplier": "$SUPPLIER",
  "externalRefs": $EXTERNAL_REFS
}''')

# Template for relationship entries connecting SPDX elements
REL_LINE_TEMPLATE = Template('{"spdxElementId":"$SRC","relationshipType":"$TYPE","relatedSpdxElement":"$DST"}')


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
    except (OSError, subprocess.SubprocessError):
        return None


def _purl(name: str, ver: str) -> str:
    """Generate a Package URL (PURL) for a package.

    Package URLs are a standardized way to identify software packages across
    different package managers and ecosystems. This function generates a generic
    PURL for packages that don't have a specific package manager.

    Args:
        name: Package name.
        ver: Package version string.

    Returns:
        PURL string in the format 'pkg:generic/name[@version]'.

    Note:
        If version is missing, UNKNOWN, or NOASSERTION, only the name is included.
        See https://github.com/package-url/purl-spec for PURL specification.
    """
    if not ver or ver.upper() in ('UNKNOWN', 'NOASSERTION'):
        return f'pkg:generic/{name}'
    return f'pkg:generic/{name}@{ver}'


def _dedupe_relationships(rel_list: list[dict]) -> list[dict]:
    """Remove duplicate relationship entries from a list.

    Relationships are deduplicated based on the tuple of (spdxElementId,
    relationshipType, relatedSpdxElement). This ensures each unique dependency
    relationship appears only once in the final SPDX document.

    Args:
        rel_list: List of relationship dictionaries.

    Returns:
        New list with duplicates removed, preserving order of first occurrence.
    """
    seen = set()
    out = []
    for relationship in rel_list:
        key = (
            relationship.get('spdxElementId'),
            relationship.get('relationshipType'),
            relationship.get('relatedSpdxElement'),
        )
        if key in seen:
            continue
        seen.add(key)
        out.append(relationship)
    return out


def _get_pkg_version(pkg_name: str) -> Optional[str]:
    """Query the OS package manager for a package's version.

    Currently supports dpkg (Debian/Ubuntu). Additional package managers
    can be added as needed (rpm, pacman, etc.).

    Args:
        pkg_name: OS package name to query.

    Returns:
        Version string if found, None otherwise.
    """
    version = _run(['dpkg-query', '-W', '-f=${Version}', pkg_name])
    if version:
        return version

    return None


def _get_supplier_from_url(url: str) -> str:
    """Extract supplier/organization name from a URL.

    Attempts to derive a supplier identifier from a package's source URL
    by extracting the hostname. This provides a reasonable default when
    explicit supplier information is not available.

    Args:
        url: Package source or homepage URL.

    Returns:
        Supplier string in the format "Organization: hostname" or
        "Organization: Unknown" if URL parsing fails.
    """
    try:
        host = urlparse(url).hostname
        if host:
            return f'Organization: {host}'
    except (TypeError, ValueError):
        pass
    return 'Organization: Unknown'


def now() -> str:
    """Get current UTC timestamp in ISO 8601 format.

    Returns:
        ISO 8601 formatted timestamp string (e.g., "2025-12-12T10:30:00Z").

    Note:
        Used for SPDX creationInfo timestamp to record when the SBOM was generated.
    """
    return datetime.now(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ')


def safe(s: str) -> str:
    """Sanitize a string for use in SPDX identifiers.

    SPDX identifiers must consist of letters, numbers, dots, and hyphens.
    This function replaces invalid characters with hyphens and collapses
    multiple consecutive hyphens into one.

    Args:
        s: String to sanitize.

    Returns:
        Sanitized string suitable for SPDX IDs, or 'X' if result would be empty.

    Note:
        Leading and trailing hyphens are removed to ensure valid identifiers.
    """
    s = re.sub(r'[^A-Za-z0-9.\-]+', '-', str(s))
    s = re.sub(r'-{2,}', '-', s).strip('-')
    return s or 'X'


def minjson(obj) -> str:
    """Serialise object to compact JSON without whitespace.

    Args:
        obj: Python object to serialise.

    Returns:
        Compact JSON string with no spaces after separators.

    Note:
        Used to minimize the size of embedded JSON within the SPDX templates.
    """
    return json.dumps(obj, separators=(',', ':'))


def ldd_libs(binary: Path):
    """Discover shared library dependencies of a binary using ldd.

    Executes ldd on the given binary to determine which shared libraries
    it depends on at runtime. This is essential for capturing runtime
    dependencies that may not be visible through build-time analysis alone.

    Args:
        binary: Path to the executable or shared library to analyse.

    Returns:
        List of Path objects representing the absolute paths to shared
        libraries that the binary links against.

    Note:
        The regex pattern extracts library paths from ldd output lines like:
        "libssl.so.3 => /usr/lib/x86_64-linux-gnu/libssl.so.3 (0x00007f...)"
        Only existing file paths are included in the result.
    """
    out = _run(['ldd', str(binary)]) or ''
    libs = []
    for line in out.splitlines():
        # Extract library path from ldd output format: "libname => /path/to/lib (address)"
        match = re.search(r'=>\s+(\S+)\s+\(', line)
        if match:
            lib_path = Path(match.group(1))
            if lib_path.exists():
                libs.append(lib_path)
    return libs


def map_os_pkg(path: Path) -> Optional[str]:
    """Determine which OS package owns a given file.

    Queries the system package manager to find which package installed
    a particular file. This is used to map shared libraries discovered
    via ldd to their corresponding OS packages for SBOM inclusion.

    Args:
        path: Path to the file to query.

    Returns:
        Package name if found, None otherwise.

    Note:
        Currently supports dpkg (Debian/Ubuntu) and rpm (Red Hat/Fedora).
        Additional package managers can be added as needed.
    """
    # Try dpkg (Debian/Ubuntu)
    result = _run(['dpkg', '-S', str(path)])
    if result and ':' in result:
        return result.split(':', 1)[0]

    # Try rpm (Red Hat/Fedora/CentOS)
    result = _run(['rpm', '-qf', str(path)])
    if result and 'is not owned' not in result:
        return result.split()[0]

    return None


def build_spdx(proj_name: str, proj_ver: str, graph, binaries) -> str:
    """Render a complete SPDX 2.3 JSON document from a dependency graph.

    This is the main function that converts the resolved dependency graph into
    a fully compliant SPDX 2.3 JSON document. It performs the following steps:
    1. Creates the root package entry for the project
    2. Generates package entries for all dependencies
    3. Analyses binaries to discover runtime OS library dependencies
    4. Establishes SPDX relationships (DESCRIBES, DEPENDS_ON)
    5. Assembles the complete document using string templates

    Args:
        proj_name: Name of the project being analysed.
        proj_ver: Version string of the project.
        graph: Graph instance containing dependency metadata and edges.
        binaries: List of Path objects to built executables/libraries.

    Returns:
        Complete SPDX 2.3 JSON document as a string.

    Note:
        The function uses text templates instead of object serialisation for
        efficiency and precise control over the JSON structure. Each package
        receives a unique SPDXID in the format "SPDXRef-pkg-{name}-{version}".

        Runtime dependencies are discovered by:
        - Running ldd on each binary to find linked shared libraries
        - Mapping those libraries to OS packages via dpkg/rpm
        - Adding those packages to the SBOM with appropriate metadata
    """
    doc_name = f'{proj_name}-sbom'
    doc_ns = f'urn:uuid:{uuid.uuid4()}'
    creation_info = {'creators': ['Tool: meson2spdx-1.0.0', 'Organization: Ada Logics Ltd.'], 'created': now()}

    # Root package: represents the project being analysed
    root_version = proj_ver or '0.0'
    root_spdx = f'SPDXRef-pkg-{safe(proj_name)}-{safe(root_version)}'
    root_pkg_str = ROOT_PACKAGE_TEMPLATE.substitute(
        SPDXID=root_spdx,
        NAME=proj_name,
        VERSION=root_version,
        SUPPLIER='Organization: Unknown',
        PURL=_purl(proj_name, root_version),
    )

    # Store names for later use in document assembly
    document_name = doc_name
    document_namespace = doc_ns

    # Generate package entries for all build-time dependencies
    idmap: dict[str, str] = {}
    package_lines: list[str] = [root_pkg_str]
    sorted_deps = sorted(graph.deps.items(), key=lambda item: item[0].lower())
    print(f'Found {len(sorted_deps)} build-time dependencies')
    cnt = 1
    for name, info in sorted_deps:
        print(f'Processing build-time dependency {cnt}/{len(sorted_deps)}: {name}...')
        cnt += 1
        version = info.get('version') or '0.0'
        spdx_id = f'SPDXRef-pkg-{safe(name)}-{safe(version)}'

        # Determine supplier from metadata or derive from URL
        supplier = info.get('supplier') or info.get('provider')
        if not supplier:
            supplier = _get_supplier_from_url(info.get('url'))
        idmap[name] = spdx_id

        # Build external references: always include PURL, optionally add pcfile reference
        external_refs = [{
            'referenceCategory': 'PACKAGE-MANAGER',
            'referenceType': 'purl',
            'referenceLocator': _purl(name, version),
        }]
        if info.get('pcfile'):
            external_refs.append({
                'referenceCategory': 'OTHER',
                'referenceType': 'OTHER',
                'referenceLocator': f"pcfile:{info['pcfile']}",
            })

        pkg_line = PACKAGE_TEMPLATE.substitute(
            SPDXID=spdx_id,
            NAME=name,
            VERSION=version,
            SUPPLIER=supplier,
            DOWNLOAD=minjson(info.get('url') or 'NOASSERTION'),
            EXTERNAL_REFS=minjson(external_refs),
        )
        package_lines.append(pkg_line)

    # Establish SPDX relationships
    rel_lines: list[str] = []

    # Document DESCRIBES the root package
    rel_lines.append(REL_LINE_TEMPLATE.substitute(SRC='SPDXRef-DOCUMENT', TYPE='DESCRIBES', DST=root_spdx))

    # Root package DEPENDS_ON all direct dependencies
    for name in graph.deps.keys():
        rel_lines.append(REL_LINE_TEMPLATE.substitute(SRC=root_spdx, TYPE='DEPENDS_ON', DST=idmap[name]))

    # Add transitive dependency edges from the graph
    rel_seen = set()
    for (parent, child) in sorted(graph.edges):
        if parent in idmap and child in idmap:
            key = (idmap[parent], 'DEPENDS_ON', idmap[child])
            if key in rel_seen:
                continue
            rel_seen.add(key)
            rel_lines.append(REL_LINE_TEMPLATE.substitute(SRC=key[0], TYPE=key[1], DST=key[2]))

    # Discover and add runtime OS library dependencies from binaries
    if binaries:
        print(f'Found {len(binaries)} binaries to process')
        os_ids: dict[str, str] = {}
        os_edges: set = set()
        cnt = 1
        for binary_path in binaries:
            print(f'Processing binary {cnt}/{len(binaries)}: {binary_path}...')
            cnt += 1
            # Use ldd to discover shared library dependencies
            for shared_lib in ldd_libs(binary_path):
                # Map shared library file to OS package name
                os_package = map_os_pkg(shared_lib)
                if not os_package:
                    continue

                # Add OS package to SBOM if not already present
                if os_package not in os_ids:
                    os_spdx = f'SPDXRef-os-{safe(os_package)}'
                    os_ids[os_package] = os_spdx
                    version = _get_pkg_version(os_package) or '0.0'
                    pkg_line = PACKAGE_TEMPLATE.substitute(
                        SPDXID=os_spdx,
                        NAME=os_package,
                        VERSION=version,
                        SUPPLIER='Organization: debian',
                        DOWNLOAD=minjson('NOASSERTION'),
                        EXTERNAL_REFS=minjson([{
                            'referenceCategory': 'PACKAGE-MANAGER',
                            'referenceType': 'purl',
                            'referenceLocator': f'pkg:generic/{os_package}'
                        }]),
                    )
                    package_lines.append(pkg_line)

                # Establish dependency edge from root package to OS package
                edge = (root_spdx, os_ids[os_package])
                if edge in os_edges:
                    continue
                os_edges.add(edge)
                rel_lines.append(REL_LINE_TEMPLATE.substitute(SRC=edge[0], TYPE='DEPENDS_ON', DST=edge[1]))

    # Deduplicate relationship entries to ensure clean SPDX output
    relationship_objects = [json.loads(line) for line in rel_lines]
    relationship_objects = _dedupe_relationships(relationship_objects)
    rel_lines = [minjson(relationship_obj) for relationship_obj in relationship_objects]

    # Assemble the complete SPDX document from templates
    spdx_document = DOC_TEMPLATE.substitute(
        DOC_NAME=document_name,
        DOC_NAMESPACE=document_namespace,
        CREATION_INFO=minjson(creation_info),
        PACKAGES=',\n'.join(package_lines),
        RELATIONSHIPS=',\n'.join(rel_lines),
    )
    return spdx_document
