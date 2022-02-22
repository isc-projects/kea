#!/usr/bin/env python3

# This script is used to maintain upgrade scripts in Kea and to ensure that the
# incremental and the full schema scripts are in sync. See usage() function
# below for help in how to use it.

import difflib
import glob
import os
import re
import subprocess
import sys


def usage():
    print('''\
Usage: are-scripts-in-sync.py [-h|--help] [$file|$gitref [$gitref2]]

$ are-scripts-in-sync.py
  No parameters are given.
  All the SQL scripts changed in the current branch are checked.

$ are-scripts-in-sync.py $file
  One file is given. It must be a dhcpdb_create script or an upgrade script.
  If it is a dhcpdb_create script, it is compared with the latest upgrade script.
  If it is an upgrade script, it is compared to the dhcpdb_create script.

$ are-scripts-in-sync.py $gitref
  Two git refs are given. They can be branches, commits, tags, etc.
  All the SQL scripts changed between HEAD and $gitref are checked.

$ are-scripts-in-sync.py $gitref1 $gitref2
  Two git refs are given. They can be branches, commits, tags, etc.
  All the SQL scripts changed between $gitref1 and $gitref2 are checked.''')


def filter_the_noise(text, is_upgrade_script):
    ''' Removes portions of the script which are always different.

    :param text: the script content to be analyzed
    :type text: str

    :param is_upgrade_script: determines if it is an upgrade script or a
        dhcpdb_create script. Different delimiters are used for each.
    :type is_upgrade_script: bool

    :return: the trimmed down portion of text
    :type: str
    '''
    append=False
    result=[]
    for i in text:
        if re.search('<<EOF$' if is_upgrade_script else 'CREATE TABLE.*lease4', i):
            append=True
        elif re.search('^EOF$' if is_upgrade_script else 'Notes:', i):
            append=False
        elif re.search('^START TRANSACTION;$', i) or \
                re.search('^COMMIT;$', i) or \
                re.search('^$', i):
            # Exclude start transactions, commits, and empty lines.
            pass
        elif append:
            result.append(i)
    return result


def diff(dhcpdb_create_script, upgrade_script):
    ''' Compares the common parts of two files. Prints the difference.

    :param dhcpdb_create_script: the path to the dhcpdb_create script
    :type dhcpdb_create_script: str
    :param upgrade_script: the path to the upgrade script
    :type upgrade_script: str

    :return: True if there is a difference, False otherwise
    :type: bool
    '''
    with open(dhcpdb_create_script, encoding='utf-8') as create_file:
        create_text = create_file.readlines()

    with open(upgrade_script, encoding='utf-8') as upgrade_file:
        upgrade_text = upgrade_file.readlines()

    # PostgreSQL upgrade scripts need the $ delimiters escaped as opposed to
    # create scripts. So escape them in the create script for the duration of
    # this diff so that they don't come up in the diff (or so that they do
    # come up if they are not correctly escaped in the upgrade script).
    if dhcpdb_create_script.endswith('.pgsql'):
        create_text = [i.replace('$', r'\$') for i in create_text]

    # Removes portions of the script which are always different: the beginning
    # and the end.
    create_text = filter_the_noise(create_text, False)
    upgrade_text = filter_the_noise(upgrade_text, True)

    latest_upgrade_script = find_files_in_same_directory_starting_with(upgrade_script, 'upgrade_')[-1]
    if upgrade_script == latest_upgrade_script:
        # Truncate the create script to the length of the upgrade script to
        # exclude chances of wrong matching.
        create_text = create_text[len(create_text) - len(upgrade_text) :]

    # Use difflib to create the diff.
    raw_diff = ''.join(difflib.context_diff(create_text, upgrade_text, n=0)).splitlines()

    # Determine groups of a heuristical number of consecutive lines that differ.
    # These are considered to be outside the upgrade script's scope and are
    # subject to exclusion from the diff.
    consecutive_lines_to_exclude = 16
    first_exclamation_mark = None
    to_be_removed = []
    for i, line in enumerate(raw_diff):
        if line.startswith('!'):
            if first_exclamation_mark is None:
                first_exclamation_mark = i
        else:
            if first_exclamation_mark is not None and first_exclamation_mark + consecutive_lines_to_exclude < i:
                to_be_removed.append([first_exclamation_mark, i - 1])
            first_exclamation_mark = None

    # Exclude the groups determined above.
    sanitized_diff = []
    for i, line in enumerate(raw_diff):
        if len(to_be_removed) > 0 and to_be_removed[0][0] <= i <= to_be_removed[0][1]:
            pass
        elif len(to_be_removed) > 0 and to_be_removed[0][1] < i:
            while len(to_be_removed) > 0 and to_be_removed[0][1] < i:
                to_be_removed.pop(0)
        else:
            sanitized_diff.append(line)

    # Print only the lines that start with an exclamation mark. This is how
    # difflib's context diff is provided.
    output = ''
    for i in sanitized_diff:
        if i.startswith('!'):
            if len(output) == 0:
                print (f'=== {dhcpdb_create_script} vs {upgrade_script} ===')
            output += i + '\n'

    # Only print if we have something to print to avoid a newline.
    if len(output) > 0:
        if upgrade_script != latest_upgrade_script:
            print('WARNING: There is a small chance of false errors on this pair of scripts.\n')
        print(output)

    # Only report errors on the latest upgrade script. For all other upgrade
    # scripts, there is a chance of false errors caused by incorrect matching of
    # lines. Assume no diff so that CI doesn't complain.
    return len(output) > 0 and upgrade_script == latest_upgrade_script


def execute(command):
    ''' Executes a shell command and returns its output.

    :param command: the command to be executed
    :type command: str

    :return: the standard output from the command
    :type: str
    '''
    if 'DEBUG' in os.environ:
        print(f'> {command}')
    with subprocess.Popen(command, encoding='utf-8', shell=True,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE) as p:
        output, error = p.communicate()
    if error:
        print('ERROR:', error, file=sys.stderr)
        sys.exit(1)
    return output.strip()

def find_files_in_same_directory_starting_with(file, startswith):
    ''' Returns the files that start with given criteria.

    :param file: the path to the file that lives in the same directory as the
        desired file
    :type file: str

    :param startswith: the substring that the file name should start with
    :type startswith: str
    '''
    dirname = os.path.dirname(file)
    files = []
    for i in glob.glob(dirname + '/*'):
        matches = re.search('^' + dirname + '/' + startswith + '.*$', i)
        if matches is not None:
            files.append(matches.group())
    return sorted(files)


def get_files_changed_in_gitref_range(gitref_range):
    # Change to toplevel for easier management of file names.
    toplevel = execute('git rev-parse --show-toplevel')
    os.chdir(toplevel)

    # Get the list of changed files since {gitref}.
    return execute(f'git diff --name-only "{gitref_range}" ./src/share/database/scripts').splitlines()


def main(parameters):
    # Print help if requested.
    if '-h'in parameters or '--help' in parameters:
        usage()
        sys.exit(0)

    # Parse parameters.
    p1 = None
    p2 = None
    for i in parameters:
        if p1 is None:
            p1 = i
        elif p2 is None:
            p2 = i
        else:
            print('ERROR: Too many arguments.', file=sys.stderr)
            usage()
            sys.exit(1)

    # Determine the files that we need to check.
    if p1 is None and p2 is None:
        files = get_files_changed_in_gitref_range('$(git merge-base origin/master HEAD)')
    elif p1 is not None:
        if os.path.isfile(p1):
            files = [p1]
        else:
            files = get_files_changed_in_gitref_range(f'{p1}')
    else:
        files = get_files_changed_in_gitref_range(f'{p1}..{p2}')

    diff_found = False
    for i in files:
        basename = os.path.basename(i)
        if basename.startswith('dhcpdb_create'):
            # Get the latest upgrade script.
            latest_upgrade_script = find_files_in_same_directory_starting_with(i, 'upgrade_')[-1]
            # Do the diff.
            diff_found |= diff(i, latest_upgrade_script)
        elif basename.startswith('upgrade_'):
            # Get the dhcpdb_create script.
            dhcpdb_create = find_files_in_same_directory_starting_with(i, 'dhcpdb_create')[-1]
            # Do the diff.
            diff_found |= diff(dhcpdb_create, i)

    # For any diff, return 1 so that CI complains.
    # For no diff, return 0 to appease CI.
    return int(diff_found)


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
