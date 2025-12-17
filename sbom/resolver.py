#!/usr/bin/env python3

"""Dependency Graph Resolution and Normalisation Module.

This module builds and normalises a complete dependency graph by merging data from
Meson introspection and pkg-config queries. It handles name normalisation, deduplication,
transitive dependency expansion, and relationship tracking between packages.

The Graph class represents the dependency structure with both package metadata and
directed edges showing dependency relationships. The recursive resolution algorithm
traverses pkg-config dependencies to discover indirect dependencies that may not be
explicitly declared in the Meson build system.
"""

from pathlib import Path
from typing import Optional

from pkgconfig import PcCache


def _normalised_name(old: str, info: dict, wraps_meta: dict) -> Optional[str]:
    """Determine the canonical name for a dependency package.

    Different sources (Meson, pkg-config, .wrap files) may refer to the same package
    by different names. This function applies normalisation rules to derive a consistent
    canonical name across all sources.

    Args:
        old: Original package name from Meson or other source.
        info: Package metadata dictionary.
        wraps_meta: Dictionary of .wrap file metadata.

    Returns:
        Normalised package name, or None if the package should be excluded
        (e.g., 'packagecache' is filtered out as it's a Meson internal).

    Note:
        Normalisation priority:
        1. Use .pc file stem if available (most reliable)
        2. Use 'directory' from .wrap file metadata
        3. Filter out special names like 'packagecache'
        4. Otherwise, keep the original name
    """
    # Prefer .pc file basename as the canonical name (most reliable)
    pcfile = info.get('pcfile')
    if pcfile:
        stem = Path(pcfile).stem
        if stem:
            return stem

    # Check .wrap metadata for directory name
    for source in info.get('sources', []):
        if source.get('kind') == 'wrap':
            wrap_meta = source.get('meta') or {}
            directory = wrap_meta.get('directory')
            if directory:
                return directory

    # Filter out Meson internal package names
    if old == 'packagecache':
        return None

    return old


def normalise_deps_inplace(deps: dict[str, dict], wraps_meta: dict) -> None:
    """Normalise dependency dictionary keys and merge duplicate entries in-place.

    This function applies name normalisation to all dependency entries and handles
    renaming and merging. When multiple entries map to the same canonical name,
    their metadata is merged with priority given to more complete information.

    Args:
        deps: Dictionary mapping package names to their metadata (modified in-place).
        wraps_meta: Dictionary of .wrap file metadata for normalisation.

    Side Effects:
        Modifies deps dictionary by:
        - Removing entries that should be excluded (e.g., 'packagecache')
        - Renaming keys to their canonical forms
        - Merging metadata when multiple names map to the same canonical name

    Note:
        When merging, existing metadata in the target entry is preserved,
        and only missing fields are filled from the source entry.
    """
    remap = {}
    drops: set[str] = set()

    # First pass: identify packages to drop and rename mappings
    for old_name, package_info in list(deps.items()):
        new = _normalised_name(old_name, package_info, wraps_meta)
        if new is None:
            drops.add(old_name)
        elif new != old_name:
            remap[old_name] = new

    # Remove packages marked for exclusion
    for package_name in drops:
        deps.pop(package_name, None)

    # Second pass: apply renames and merge metadata
    for old, new in remap.items():
        if old not in deps:
            continue
        source_entry = deps.pop(old)
        target_entry = deps.get(new)

        if not target_entry:
            # No collision: simply rename the entry
            source_entry['name'] = new
            deps[new] = source_entry
        else:
            # Collision: merge metadata, preserving existing target_entry fields
            for field in ('version', 'url', 'pcfile', 'type'):
                if not target_entry.get(field) and source_entry.get(field):
                    target_entry[field] = source_entry[field]


class Graph:
    """Represents a dependency graph with packages and directed edges.

    This class maintains both package metadata and dependency relationships
    (directed edges from parent to child packages). It provides methods to
    ensure packages exist in the graph and to record dependency relationships.

    Attributes:
        deps: Dictionary mapping package names to their metadata.
        edges: Set of tuples (parent, child) representing dependency relationships.
    """

    def __init__(self, deps: dict[str, dict]):
        """Initialise graph with existing package metadata.

        Args:
            deps: Initial dictionary of package metadata.
        """
        self.deps = deps
        self.edges: set[tuple[str, str]] = set()

    def ensure_pkg(self, name: str, cache: PcCache):
        """Ensure a pkg-config package exists in the graph with enriched metadata.

        If the package doesn't exist in the graph, it is added with default type.
        Metadata from pkg-config (version, URL, .pc file path) is then merged
        into the package entry, filling only missing fields.

        Args:
            name: Package name to ensure exists.
            cache: PcCache instance for querying pkg-config metadata.

        Returns:
            The package metadata dictionary.
        """
        entry = self.deps.get(name)
        if not entry:
            entry = self.deps[name] = {'name': name, 'type': 'pkg-config'}

        # Enrich with pkg-config metadata
        info = cache.info(name)
        for k, v in info.items():
            if v and not entry.get(k):
                entry[k] = v

        return entry

    def ensure_syslib(self, libname: str):
        """Ensure a system library exists in the graph.

        System libraries are discovered through linker flags but may not have
        pkg-config metadata. This method adds them with a standardized name
        (prefixed with 'lib' if not already) and marks them as 'systemlib' type.

        Args:
            libname: Library name (with or without 'lib' prefix).

        Returns:
            The library metadata dictionary.

        Note:
            Version is set to 'UNKNOWN' as system libraries typically don't
            expose version information through linker flags alone.
        """
        # Normalise library name to include 'lib' prefix
        normalised_name = libname if libname.startswith('lib') else f'lib{libname}'
        self.deps.setdefault(normalised_name, {'name': normalised_name, 'type': 'systemlib', 'version': 'UNKNOWN'})
        return self.deps[normalised_name]

    def add_edge(self, parent: str, child: str):
        """Record a dependency relationship between two packages.

        Args:
            parent: Name of the package that depends on the child.
            child: Name of the package being depended upon.

        Note:
            Edges are stored in a set, so duplicate edges are automatically ignored.
            Both parent and child must be non-empty strings to be recorded.
        """
        if parent and child:
            self.edges.add((parent, child))


def _search_pkg(pkg: str, graph: Graph, cache: PcCache, wraps_meta: dict,
             visited: set[str], stack: set[str], max_depth: int, depth: int):
    """Recursively discover and add transitive dependencies to the graph.

    This function performs depth-first traversal of the dependency tree starting
    from a given package. It queries pkg-config for both required packages
    (Requires/Requires.private) and linked libraries (--libs/--libs-private),
    distinguishing between libraries with pkg-config metadata and system libraries.

    Args:
        pkg: Current package name being explored.
        graph: Graph instance to populate with dependencies and edges.
        cache: PcCache instance for pkg-config queries.
        wraps_meta: Dictionary of .wrap file metadata for normalisation.
        visited: Set of already-processed package names (prevents reprocessing).
        stack: Set of packages currently in the call stack (detects cycles).
        max_depth: Maximum recursion depth to prevent infinite loops.
        depth: Current recursion depth.

    Note:
        Circular dependencies are handled by tracking the call stack.
        System libraries (those without pkg-config metadata) are marked as
        terminal nodes and are not recursively explored.
    """
    # Stopping criteria: prevent infinite recursion and circular dependencies
    if depth > max_depth or pkg in stack:
        return
    stack.add(pkg)

    # Query pkg-config for dependencies and linked libraries
    required_packages = cache.requires(pkg)  # Required packages (Requires/Requires.private)
    linked_libraries = cache.libs(pkg)      # Linked libraries from -l flags

    # Categorize libraries: those with pkg-config metadata vs. system libraries
    pkgconfig_libs = {lib for lib in linked_libraries if cache.exists(lib)}
    system_libs = {lib for lib in linked_libraries if lib not in pkgconfig_libs}

    # Ensure all discovered dependencies exist in the graph
    for required_pkg in required_packages:
        graph.ensure_pkg(required_pkg, cache)
    for pkgconfig_lib in pkgconfig_libs:
        graph.ensure_pkg(pkgconfig_lib, cache)
    for system_lib in system_libs:
        graph.ensure_syslib(system_lib)

    # Normalise package names after adding new entries
    normalise_deps_inplace(graph.deps, wraps_meta)

    # Recursively process pkg-config dependencies
    for child in set(required_packages) | pkgconfig_libs:
        graph.add_edge(pkg, child)
        if child not in visited:
            _search_pkg(child, graph, cache, wraps_meta, visited, stack, max_depth, depth + 1)

    # Add edges to system libraries (terminal nodes, no recursion)
    for system_lib in system_libs:
        normalised_name = system_lib if system_lib.startswith('lib') else f'lib{system_lib}'
        graph.add_edge(pkg, normalised_name)

    # Backtrack: remove from call stack and mark as visited
    stack.remove(pkg)
    visited.add(pkg)


def build_pkg_graph_recursive(graph: Graph, wraps_meta: dict, max_depth: int):
    """Build complete transitive dependency graph from pkg-config seeds.

    This function identifies all packages in the graph that have pkg-config metadata
    and recursively expands their dependencies. It serves as the main entry point
    for dependency discovery after initial Meson introspection.

    Args:
        graph: Graph instance containing initial dependencies from Meson.
        wraps_meta: Dictionary of .wrap file metadata for normalisation.
        max_depth: Maximum recursion depth for dependency traversal.

    Side Effects:
        Populates graph.deps with all discovered transitive dependencies and
        graph.edges with all dependency relationships.

    Note:
        Only packages with .pc files or 'pkg' in their type are used as seeds.
        This ensures we only traverse dependencies that can be queried via pkg-config.
    """
    cache = PcCache()
    visited: set[str] = set()

    # Identify seed packages: those with pkg-config metadata
    seeds = [name for name, info in list(graph.deps.items())
             if info.get('pcfile') or 'pkg' in (info.get('type') or '').lower()]

    # Recursively expand dependencies from each seed package
    for seed in seeds:
        if seed not in visited:
            _search_pkg(seed, graph, cache, wraps_meta, visited, set(), max_depth, 0)


def add_subproject_edges_from_targets(intro_targets: list, graph: Graph):
    """Infer and add dependency edges from Meson build target information.

    Meson build targets contain information about which subprojects they belong to
    and what dependencies they use. This function extracts these relationships and
    adds them to the dependency graph, enriching the graph with intra-project
    dependency information that may not be captured by pkg-config alone.

    Args:
        intro_targets: List of build target dictionaries from Meson intro-targets.json.
        graph: Graph instance to populate with subproject edges.

    Side Effects:
        Adds edges from subprojects to their dependencies in graph.edges.
        Ensures all referenced subprojects and dependencies exist in graph.deps.

    Note:
        This captures relationships between Meson subprojects and their declared
        dependencies, complementing the pkg-config-based dependency discovery.
    """
    cache = PcCache()

    for target in intro_targets or []:
        # Extract subproject name from target
        subproject_name = target.get('subproject')
        if not subproject_name:
            continue

        # Ensure subproject exists in graph
        graph.deps.setdefault(subproject_name, {'name': subproject_name, 'type': 'subproject'})

        # Process all dependencies declared by this target
        for dependency in target.get('dependencies') or []:
            dep_name = dependency.get('name') or dependency.get('depname') or dependency.get('project_name')
            if not dep_name:
                continue

            # Ensure dependency exists and add edge from subproject to dependency
            graph.ensure_pkg(dep_name, cache)
            graph.add_edge(subproject_name, dep_name)
