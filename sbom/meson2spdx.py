#!/usr/bin/env python3

"""Meson to SPDX SBOM Generation Tool - Main Entry Point.

This is the main executable script that orchestrates the complete SBOM generation
pipeline for Meson-based projects. It coordinates the following operations:

1. Parses command-line arguments for build directory, project root, and output file
2. Invokes Meson introspection to extract project metadata and dependencies
3. Normalises dependency names across different sources (Meson, pkg-config, .wrap)
4. Recursively expands the dependency graph using pkg-config queries
5. Analyses build targets to infer subproject relationships
6. Generates a complete SPDX 2.3 JSON document with all dependencies

The tool produces SBOM documents that comply with both NTIA Minimum Elements
and SPDX 2.3 specifications, suitable for software supply chain security analysis.

Usage:
    python3 meson2spdx.py -b build -r . -o sbom.spdx.json

For more information, see the accompanying README.md.
"""

import argparse
from pathlib import Path

from meson import discover_meson
from resolver import (
    normalise_deps_inplace,
    Graph,
    build_pkg_graph_recursive,
    add_subproject_edges_from_targets,
)
from spdx import build_spdx


def main():
    """Main execution function for the meson2spdx SBOM generation tool.

    This function orchestrates the complete SBOM generation pipeline:
    1. Parses command-line arguments
    2. Discovers project metadata and dependencies from Meson
    3. Normalises and resolves the complete dependency graph
    4. Generates and writes the SPDX 2.3 JSON document

    The tool performs recursive dependency resolution with a maximum depth
    limit to prevent infinite loops in case of circular dependencies.

    Command-line Arguments:
        -b, --build-dir: Path to Meson build directory (default: 'build')
        -r, --project-dir: Path to project root directory (default: '.')
        -o, --out: Output SPDX JSON file path (default: 'sbom.spdx.json')

    Exit Behavior:
        Prints the absolute path of the generated SPDX file upon successful completion.
        Exits with error if Meson introspection files are missing or inaccessible.
    """
    ap = argparse.ArgumentParser(description='Meson to SPDX JSON')
    ap.add_argument('-b', '--build-dir', default='build', help='Meson build dir')
    ap.add_argument('-r', '--project-dir', default='.', help='Project root dir')
    ap.add_argument('-o', '--out', default='sbom.spdx.json', help='Output SPDX JSON file')
    args = ap.parse_args()

    # Initialise paths and configuration
    build_dir = Path(args.build_dir)
    project_dir = Path(args.project_dir)
    max_depth = 10  # Maximum recursion depth for dependency resolution

    # Phase 1: Discover initial project metadata and dependencies from Meson introspection
    proj_name, proj_ver, deps, intro_targets, binaries, wraps_meta = discover_meson(build_dir, project_dir)

    # Phase 2: Normalise dependency names to ensure consistency across sources
    normalise_deps_inplace(deps, wraps_meta)
    graph = Graph(deps)

    # Phase 3: Recursively expand dependency tree using pkg-config queries
    build_pkg_graph_recursive(graph, wraps_meta, max_depth=max_depth)

    # Phase 4: Add edges from Meson build targets to infer subproject relationships
    add_subproject_edges_from_targets(intro_targets, graph)

    # Phase 5: Final normalisation pass to ensure all names are consistent
    normalise_deps_inplace(graph.deps, wraps_meta)

    # Phase 6: Generate SPDX 2.3 JSON document and write to output file
    doc_str = build_spdx(proj_name, proj_ver, graph, binaries)
    Path(args.out).write_text(doc_str)
    print(f'SPDX JSON written: {Path(args.out).resolve()}')


if __name__ == '__main__':
    main()
