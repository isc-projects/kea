#!/usr/bin/env python3

"""
This script checks that all source headers are installed by inspecting
meson.build files.

Usage: ./tools/find-uninstalled-headers.py
"""

import pathlib
import re
import sys


EXCLUDE_LIST = [
    'src/lib/dns/name_internal.h',
]


def main():
    meson_builds = sorted(pathlib.Path('./src/lib').glob('**/meson.build'))
    headers = []
    for ext in ['h', 'hh']:
        headers += pathlib.Path('./src/lib').glob(f'**/*.{ext}')
    headers = sorted(headers)
    headers_pattern = re.compile(r'kea_.*_headers = \[([^]]*)(\]?)$')
    failure = False
    for meson_build in meson_builds:
        with open(meson_build, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            in_headers_block = False
            for line in lines:
                line = line.strip()
                if line == ']':
                    in_headers_block = False
                    continue

                headers_matches = headers_pattern.search(line)
                if headers_matches is None:
                    # Entries on multiple lines.
                    if in_headers_block:
                        header = line.strip().strip(',').strip("'").strip()
                        if header == '':
                            continue
                        relative_path = meson_build.parent / header
                        if relative_path not in headers:
                            print(f'ERROR: Header {relative_path} not installed.')
                            failure = True
                            continue
                        headers.remove(relative_path)
                else:
                    # Entries on a single line.
                    header_line = headers_matches.group(1)
                    for header in header_line.split(','):
                        header = header.strip().strip("'")
                        if header == '':
                            # TODO: Why does this happen?
                            continue
                        relative_path = meson_build.parent / header.strip()
                        if relative_path not in headers:
                            print(f'ERROR: Header {relative_path} not installed.')
                            failure = True
                            continue
                        headers.remove(relative_path)

                    end_square_bracket = headers_matches.group(2)
                    if end_square_bracket == ']':
                        in_headers_block = False
                    else:
                        in_headers_block = True

    first = True
    for header in headers:
        if str(header) in EXCLUDE_LIST:
            continue
        if any(i in header.parts for i in ['tests', 'testutils', 'unittests']):
            continue
        if first:
            print('The following headers are not mentioned in an install_headers call of '
                  'their respective meson.build file:')
            first = False
        print(f'- {header}')
        failure = True

    if failure:
        sys.exit(1)


if __name__ == '__main__':
    main()
