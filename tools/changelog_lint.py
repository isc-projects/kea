#!/usr/bin/env python3

# Copyright (C) 2019-2026 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""Lints Kea changelog files.

Usages:
./changelog-lint.py
./changelog-lint.py kea
./changelog-lint.py kea-premium
./changelog-lint.py 1.2.3 kea/ChangeLog ./a.html False
./changelog-lint.py 1.2.3 kea-premium/ChangeLog ./a.html False
./changelog-lint.py 1.2.3 kea/changelog_unreleased/1234-bugfix ./a.html True
./changelog-lint.py 1.2.3 kea-premium/changelog_unreleased/1234-bugfix ./a.html True
"""

# pylint: disable = fixme
# pylint: disable = global-statement
# pylint: disable = too-many-nested-blocks

# TODO: add check spelling with enchant?

import datetime
import glob
import sys
import re

errors = 0
output = None


def trace(msg):
    """Print a message and append it to a file if the file is configured.

    :param msg: message to print
    :type msg: str
    """
    print(msg)
    if output:
        with open(output, 'a', encoding='utf-8') as f:
            f.write(msg + '<br>')


def error(lineno, line, msg):
    """Increment an error count and print details about the error.

    :param lineno: line number from the changelog file where the error occurs indexed from 0
    :type lineno: int
    :param line: the line from the changelog file where the error occurs
    :type line: str
    :param msg: the error message
    :type msg: str
    """
    global errors
    errors += 1
    trace(f'{lineno + 1}: "{line}"')
    trace(f'  {msg}')


def main(kea_version, changelog_path, output_path=None, is_entry_file=False):
    """Entry point.

    :param kea_version:
    :type kea_version:
    :param changelog_path:
    :type changelog_path:
    :param output_path:
    :type output_path:
    :param is_entry_file:
    :type is_entry_file:
    :return: whether there were no errors
    :rtype: bool
    """
    global output
    output = output_path

    title = f'ChangeLog Lint: {changelog_path}'
    trace(title)
    trace('=' * len(title))

    with open(changelog_path, encoding='utf-8') as f:
        lines = f.readlines()

    prev_entry_id = None
    text = ""
    entries_num = 0
    releases = []
    allowed_categories = ['bug', 'build', 'doc', 'func', 'sec', 'perf', 'test']

    rel_date_checked = False
    for idx, line in enumerate(lines):
        line = line[:-1]

        # check trailing whitespace
        if line != line.rstrip():
            error(idx, line, 'Trailing whitespace.')

        if len(line) == 0:
            # skip empty line
            continue

        # Check line length but only in the first 100 lines
        # (the rest can be skipped as they were already checked).
        # This check is only for 1.9.x and newer Kea.
        if not kea_version.startswith(("1.6", "1.8")):
            line_t = line.replace('\t', ' ' * 8)
            length = len(line_t)
            if idx < 100 and length > 73 and 'released on' not in line:
                error(
                    idx, line_t, f'Line is too long ({length}), should be < 73 characters (tab is counted as 8 spaces).'
                )

        # first line on entry of ChangeLog
        if not is_entry_file and line[0].isdigit():
            entries_num += 1
            text = ""
            m = re.search(r"^(\d+)\.\s+\[(.+)\]\*?\s+(.+)", line)
            if not m:
                error(idx, line, 'Malformed first entry line. Expected: "<num>.   [<categories>]   <authors>".')
                break
            entry_id, category, authors = m.groups()

            # check authors
            for char in authors:
                if not char.isalnum() and char not in [' ', ',', '-', '.', '_', '(', ')', '[', ']']:
                    error(idx, line, 'Authors contain other characters than alphanumeric, dash, dot, underline, '
                          f'round brackets, or square brackets: "{authors}".')

            # check categories
            categories = category.split(',')
            categories = [cat.strip() for cat in categories]
            for cat in categories:
                if cat not in allowed_categories:
                    error(idx, line, f'Unknown category "{cat}".')

            # check entry id
            try:
                entry_id = int(entry_id)
            except (TypeError, ValueError):
                error(idx, line, f'Entry ID "{entry_id}" is not an integer.')
                break
            if prev_entry_id is not None and entry_id not in [1148, 1491]:
                if entry_id != prev_entry_id - 1:
                    error(idx, line, f'Entry ID is not consecutive ("{entry_id}" while previous is "{prev_entry_id}").')
            prev_entry_id = entry_id

        # first line of the ChangeLog entry file
        elif is_entry_file and line[0] == '[':
            entries_num += 1
            text = ""

            m = re.search(r"^\[(.+)\]\*?\t\t(.+)", line)
            if not m:
                error(idx, line, 'Malformed first entry line. Expected: "[<categories>]   <authors>".')
                break
            category, authors = m.groups()

            # check categories
            categories = category.split(',')
            categories = [cat.strip() for cat in categories]
            for cat in categories:
                if cat not in allowed_categories:
                    error(idx, line, f'Unknown category "{cat}".')

        # line of entry text
        elif line[0] == '\t':
            text += line + '\n'

        # release line
        elif line.startswith('Kea'):
            if is_entry_file:
                error(idx, line, 'Release line should not be in entry file.')
                break

            releases.append(line)
            m = re.match(r'Kea (\S+) (\S*) *released on (.+)', line)
            if not m:
                m = re.match(r'Kea-premium hooks package (\S+) (\S*) *released on (.+)', line)
            if not m:
                error(idx, line, 'Release line is malformed.')
            else:
                version, release_type, rel_date = m.groups()
                if version in ['0.9.1beta', '0.9', '0.9beta1', '0.9beta1']:
                    # ignore old versions
                    continue
                version_parts = version.split('-')
                ver_nums = version_parts[0].split('.')
                if len(ver_nums) != 3:
                    error(idx, line, f'Version number "{version_parts[0]}" is not divided by 2 dots.')
                for n in ver_nums:
                    if not n.isdigit():
                        error(idx, line, f'Version number "{n}" is not a digit.')
                ver_type = ''
                if len(version_parts) == 2:
                    ver_type = version_parts[1]
                    if not ver_type.startswith('beta'):
                        error(idx, line, f'Version type "{ver_type}" is malformed. It should start with "beta".')

                ver0 = int(ver_nums[0])
                ver1 = int(ver_nums[1])
                if (ver0 == 1 and ver1 >= 6) or ver0 > 1:
                    if not release_type:
                        error(idx, line, 'Missing release type, it should be either (development) or (stable)')
                    elif release_type not in ['(development)', '(stable)']:
                        error(
                            idx,
                            line,
                            f'Release type should be either (development) or (stable) but it is {release_type}.',
                        )
                    else:
                        if (ver1 % 2 == 1 or 'beta' in ver_type) and release_type != '(development)':
                            error(
                                idx,
                                line,
                                'Release type for odd minor version or beta should be (development), but is '
                                f'{release_type}.',
                            )
                        if ver1 % 2 == 0 and 'beta' not in ver_type and release_type != '(stable)':
                            error(
                                idx,
                                line,
                                'Release type for even minor version and not beta should be (stable), but is '
                                f'{release_type}.',
                            )
                # Check only the latest release date.
                if not rel_date_checked:
                    try:
                        datetime.datetime.strptime(rel_date, "%B %d, %Y")
                    except ValueError:
                        error(idx, line, f'Release date does not conform to format "%B %d, %Y": "{rel_date}"')
                    rel_date_checked = True

        # rubbish to ignore
        elif line.startswith('bind10'):
            # ignore
            pass

        # last entry, stop processing
        elif prev_entry_id == 1:
            break

        else:
            error(idx, line, 'Entry text should be indented by tabulator sign.')

    trace('Summary:')
    if not is_entry_file:
        trace(f'last release: {releases[0]}')
    trace(f'entries: {entries_num}')
    trace(f'errors: {errors}')
    trace('')
    return errors == 0


if __name__ == '__main__':
    argc = len(sys.argv)
    success = True
    if argc <= 2:
        directory = '.' if argc == 1 else sys.argv[1]
        success &= main('x.y.z', f'{directory}/ChangeLog', None, is_entry_file=False)
        for i in glob.glob(f'{directory}/changelog_unreleased/*'):
            success &= main('x.y.z', i, None, is_entry_file=True)
    else:
        success &= main(
            sys.argv[1],
            sys.argv[2],
            sys.argv[3] if argc <= 4 else None,
            (sys.argv[4].lower() in ['true', 'yes']) if argc <= 5 else False,
        )
    if not success:
        sys.exit(1)
