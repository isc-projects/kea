#!/usr/bin/env python3

# Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

import argparse
import os
import pathlib
import re
import subprocess
import sys


USAGE = """
This script does several verifications regarding logged messages:
1. Checks that messages are logged only once (outside of an exhonerated list).
2. Checks that no two messages share the same id.
3. Checks that there are no unlogged/unused messages.
4. Removes all occurences of unused messages (when run with -a).
5. Checks that the debug log level is correctly logged in the message documentation.
6. Automatically adds or fixes the debug log level in the message documentation (when run with -a).
7. Checks that the placeholder ids are consecutive, starting with 1, and unique in the same message definition.
"""


def check_duplicate_occurences(occurences):
    exhonerated = {}
    parent_dir = os.path.dirname(os.path.realpath(os.path.abspath(sys.argv[0])))
    for exh_txt in [
        f'{parent_dir}/exhonerated-duplicate-messages.txt',
        f'{parent_dir}/../premium/tools/exhonerated-duplicate-messages.txt',
    ]:
        if pathlib.Path(exh_txt).is_file():
            with open(exh_txt, 'r', encoding='utf-8') as f:
                lines = f.read().splitlines()
                for line in lines:
                    message_id = line.split('%')[1].split(':')[0].strip()
                    max_allowed = line.split(':')[1].strip()
                    exhonerated[message_id] = int(max_allowed)

    failure = False
    duplicate_occurences = {k: v for k, v in occurences.items() if v > 1}
    for k, v in duplicate_occurences.items():
        if k in exhonerated and v <= exhonerated[k]:
            continue
        if not failure:  # in other words: if first
            print('Duplicate occurences found:')
            failure = True
        print(f'    % {k}: {v}')
    return failure


def check_unlogged_messages(messages, autofix):
    parent_dir = os.path.dirname(os.path.realpath(os.path.abspath(sys.argv[0])))
    root_dir = f'{parent_dir}/..'
    all_source_files = set(pathlib.Path(root_dir).glob('**/*.cc')) \
        - set(pathlib.Path(root_dir).glob('**/*messages.cc')) \
        | set(pathlib.Path(root_dir).glob('**/*.h')) \
        - set(pathlib.Path(root_dir).glob('**/*messages.h'))
    all_source_code = ''
    for file in all_source_files:
        with open(file, 'r', encoding='utf-8') as f:
            all_source_code += f.read()
    failure = False
    for message_id in messages:
        if message_id not in all_source_code:
            if not failure:  # in other words: if first
                print('Unlogged messages found:')
                failure = True
            print(f'    % {message_id}')
            if autofix:
                remove_message_definition(message_id, messages[message_id]['file'])
                print('        ^ autofixed')
    return failure


# This function is deprecated. Replaced by check_unlogged_messages.
# Messages can appear outside LOG_* function calls.
# So checking occurences is not enough.
def check_unlogged_messages_based_on_occurences(messages, occurences, autofix):
    failure = False
    for message_id in messages:
        if message_id not in occurences:
            if not failure:  # in other words: if first
                print('Unlogged messages found:')
                failure = True
            print(f'    % {message_id}')
            if autofix:
                remove_message_definition(message_id, messages[message_id]['file'])
                print('        ^ autofixed')
    return failure


def check_that_debug_log_levels_are_documented(messages, debug_levels, log_lines, autofix):
    failure = False
    for message_id, message in messages.items():
        log_level = None
        for line in log_lines:
            if line.startswith('LOG_DEBUG') and message_id in line:
                log_level = line.split(',')[1].strip().replace('isc::log::', '').replace('log::', '')
                break
        if log_level is None:
            continue
        if not log_level.isdigit():
            log_level = debug_levels[log_level]
        if isinstance(log_level, str):
            log_level = int(log_level)
        if not isinstance(log_level, int):
            print(f'Could not determine numerical log level of {message_id}. Supposedly {log_level}?')
            failure = True
        if message['debug_log_level_line'] != f'Logged at debug log level {log_level}.':
            if not failure:  # in other words: if first
                print('Messages that do not document their debug log levels:')
                failure = True
            print(f'    % {message_id}: {message["debug_log_level_line"]}')
            print(f'        % It should be: Logged at debug log level {log_level}.')
            if autofix:
                file = message['file']
                # If line is already there, remove it.
                if message['debug_log_level_line'].startswith('Logged at debug log level '):
                    line_number = run(fr'grep -En "^% \b{message_id}\b" "{file}" | cut -d ":" -f 1')
                    line_number = int(line_number) + 1
                    run(f'sed "{line_number}d" "{file}" > "{file}.tmp"')
                    run(f'mv "{file}.tmp" "{file}"')
                # And add the right one.
                run(f'sed "/^% {message_id} /a Logged at debug log level {log_level}." "{file}" > "{file}.tmp"')
                run(f'mv "{file}.tmp" "{file}"')
                print('            ^ autofixed')
    return failure


def check_placeholder_ids(messages):
    failure = False
    placeholder_id_pattern = re.compile('(%[0-9]+)')
    for message_id in messages:
        text = messages[message_id]['text']
        matches = placeholder_id_pattern.search(text)
        if matches is not None:
            for i in range(len(matches.groups())):
                match = matches.group(i)
                if match != f'%{i + 1}':
                    print(f'Expected %{i + 1} but found {match} for message:')
                    print(f'    % {message_id} {text}')
                    failure = True
    return failure


def generate_page_with_messages_printed_on_each_debug_level(messages, debug_levels):
    content = []
    for log_level in sorted(set(debug_levels.values())):
        messages_at_this_log_level = [(message_id, message) for message_id, message in sorted(messages.items())
                                      if message['debug_log_level_line'] == f'Logged at debug log level {log_level}.']
        if len(messages_at_this_log_level) == 0:
            # Do not write "Messages printed" subtitle if there are no messages.
            continue
        subtitle = f'Messages printed on debuglevel {log_level}'
        content.append(subtitle)
        content.append('=' * len(subtitle))
        content.append('\n')
        for message_id, message in messages_at_this_log_level:
            content.append(f'- {message_id}')
        content.append('\n')
    parent_dir = os.path.dirname(os.path.realpath(os.path.abspath(sys.argv[0])))
    with open(f'{parent_dir}/../doc/sphinx/debug-messages.rst', 'w', encoding='utf-8') as f:
        f.write('..\n')
        f.write('    File generated by "./tools/check-messages.py -a". Do not edit by hand.\n\n')
        for i in content:
            f.write(i)
            f.write('\n')


def remove_message_definition(message, file):
    new_lines = []
    removing = False
    with open(file, 'r', encoding='utf-8') as f:
        lines = f.read().splitlines()
        for line in lines:
            if line.startswith(f'% {message}'):
                removing = True
            elif not removing:
                new_lines.append(line)
            elif len(line) == 0:
                removing = False
    with open(file, 'w', encoding='utf-8') as f:
        for i in new_lines:
            f.write(i)
            f.write('\n')


def run(command):
    ''' Executes a shell command and returns its output.

    :param command: the command to be executed
    :type command: str

    :return: the standard output from the command
    :type: str
    '''
    if 'DEBUG' in os.environ:
        print(f'> {command}')
    # Issue: [B602:subprocess_popen_with_shell_equals_true] subprocess call with shell=True identified, security
    #        issue.
    with subprocess.Popen(command, encoding='utf-8', shell=True,  # nosec B602
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE) as p:
        output, error = p.communicate()
    if error:
        print('ERROR:', error, file=sys.stderr)
        sys.exit(2)
    return output.strip()


def main():
    # Parse parameters.
    parser = argparse.ArgumentParser(description=USAGE,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-a', '--autofix', action='store_true',
                        help='Autofix unused messages and debug log levels in docs.')
    parser.add_argument('-g', '--generate-debug-messages-page', action='store_true',
                        help='Generate the debug-messages.rst file included in the ARM.')
    args = parser.parse_args()

    # Initializations
    failure = False
    debug_levels = {}
    log_lines = []
    messages = {}
    occurences = {}
    debug_level_pattern = re.compile(r'^(extern |)const int (.*DBG.*) =(.*)$')
    message_id_pattern = re.compile(r'^% (\w+) (.*)')
    log_pattern = re.compile(r'\b(LOG_DEBUG|LOG_ERROR|LOG_FATAL|LOG_INFO|LOG_WARN)\(')

    # Process .mes files.
    parent_dir = os.path.dirname(os.path.realpath(os.path.abspath(sys.argv[0])))
    root_dir = f'{parent_dir}/..'
    mes_files = sorted(pathlib.Path(root_dir).glob('**/*.mes'))
    for mes_file in mes_files:
        with open(mes_file, 'r', encoding='utf-8') as f:
            current_message_id = None
            lines = f.read().splitlines()
            for line in lines:
                if len(line) == 0:
                    current_message_id = None

                message_id_matches = message_id_pattern.search(line)
                if message_id_matches is None:
                    # Could be message description.
                    if current_message_id is not None:
                        if 'debug_log_level_line' in messages[current_message_id]:
                            # If debug log level line is already there, that's all that concerns us, so unset
                            # current_message_id so that we ignore future lines.
                            current_message_id = None
                        else:
                            messages[current_message_id]['debug_log_level_line'] = line
                else:
                    # Message definition
                    message_id = message_id_matches.group(1)
                    message_text = message_id_matches.group(2)

                    # 2. Checks that no two messages share the same id.
                    if message_id in messages:
                        print(f'Duplicate message id definition: {message_id}. Check in both core and premium.')
                        failure = True

                    current_message_id = message_id
                    messages[message_id] = {
                        'file': mes_file,
                        'text': message_text,
                    }

    # Process .cc and .h files.
    cc_files = sorted(pathlib.Path(root_dir).glob('**/*.cc'))
    h_files = sorted(pathlib.Path(root_dir).glob('**/*.h'))
    cpp_files = cc_files + h_files
    for cpp_file in cpp_files:
        # Skip test files.
        if any(i in cpp_file.parts for i in ['tests', 'testutils', 'unittests']):
            continue

        with open(cpp_file, 'r', encoding='utf-8') as f:
            lines = f.read().splitlines()
            current_log_line = ''
            current_debug_level = ''
            for line in lines:
                line = line.strip()

                if len(current_debug_level) != 0:
                    debug_levels[current_debug_level] = (line.strip().rstrip(';')
                                                         .replace('isc::log::', '').replace('log::', ''))
                    current_debug_level = ''

                matches = debug_level_pattern.search(line)
                if matches is not None:
                    level = matches.group(2)
                    reference = matches.group(3)
                    if level is not None:
                        if len(reference) == 0:
                            current_debug_level = level
                        else:
                            debug_levels[level] = (reference.strip().rstrip(';')
                                                   .replace('isc::log::', '').replace('log::', ''))

                if len(current_log_line) == 0:
                    matches = log_pattern.search(line)
                    if matches is not None:
                        if not line.startswith('//'):
                            current_log_line = line
                    else:
                        continue
                else:
                    current_log_line += line.strip()
                if current_log_line.endswith(';'):
                    log_lines.append(current_log_line)
                    current_log_line = ''
    log_lines = sorted(log_lines)

    # Resolve all debug_levels to numbers.
    finished = False
    while not finished:
        finished = True
        for level, reference in debug_levels.items():
            if reference.isdigit():
                continue
            for i in reference.split(' '):
                if i in debug_levels:
                    if debug_levels[i].isdigit():
                        debug_levels[level] = debug_levels[level].replace(i, debug_levels[i])
                        finished = False
            if finished:  # in other words, if no replacement was done, so if all replacements were already done, then:
                debug_levels[level] = eval(reference)  # pylint: disable=eval-used
    for level in debug_levels:
        debug_levels[level] = int(debug_levels[level])

    if args.autofix or args.generate_debug_messages_page:
        generate_page_with_messages_printed_on_each_debug_level(messages, debug_levels)
        if args.generate_debug_messages_page:
            return

    # Get number of occurences for each message id.
    for line in log_lines:
        pos = 1
        if line.split('(')[0] == 'LOG_DEBUG':
            pos = 2
        message_id = line.split(',')[pos]
        message_id = message_id.split(')')[0]
        message_id = message_id.strip()
        if message_id in occurences:
            occurences[message_id] += 1
        else:
            occurences[message_id] = 1

    # 1. Checks that messages are logged only once.
    failure |= check_duplicate_occurences(occurences)

    # 3. Checks that there are no unlogged/unused messages.
    # 4. Removes all occurences of unused messages (when run with -a).
    failure |= check_unlogged_messages(messages, args.autofix)

    # 5. Checks that the debug log level is correctly logged in the message documentation.
    # 6. Automatically adds or fixes the debug log level in the message documentation (when run with -a).
    failure |= check_that_debug_log_levels_are_documented(messages, debug_levels, log_lines, args.autofix)

    # 7. Checks that the placeholder ids are consecutive, starting with 1, and unique in the same message definition.
    failure |= check_placeholder_ids(messages)

    if failure:
        sys.exit(1)


if __name__ == '__main__':
    main()
