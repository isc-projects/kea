#!/usr/bin/env python3

# Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http:#mozilla.org/MPL/2.0/.

# Produce System Messages Manual
#
# This tool reads all the message files given on the command line.
# It pulls all the messages and description out, sorts them by
# message ID, and writes them out as a single (formatted) file.
#
# Invocation:
# The code is invoked using the command line:
#
# system_messages.py [-o <output-file>] <files>
#
# If no output file is specified, output is written to stdout.
# The produced format is ReStructuredText.

import re
import argparse


def parse_args():
    parser = argparse.ArgumentParser(description='Convert set of *.mes files to .rst documentation format')
    parser.add_argument('-o', '--output', help='Output file name (default to stdout).')
    parser.add_argument('files', help='Input .mes files.', nargs='+')

    args = parser.parse_args()
    return args


def read_input_files(files):
    messages = {}
    for f in files:
        with open(f) as fp:
            print("Processing %s" % f)
            namespace = None
            msg_descr = None
            msg_id = None
            msg_text = None
            for line in fp.readlines():
                line = line.strip()

                if not line or line.startswith('#'):
                    pass

                elif line.startswith('$'):
                    pass

                elif line.startswith('%'):
                    # end previous message
                    if msg_id is not None:
                        section = msg_id.split('_')[0]
                        messages[msg_id] = (section, msg_id, msg_text, msg_descr)

                    # start next message
                    m = re.search('^%\s?([A-Z0-9_]+)\s+(.*)', line);
                    msg_id, msg_text = m.groups()
                    msg_descr = []

                else:
                    msg_descr.append(line)

    return messages


def generate_rst(messages):
    rst = '''
###################
Kea Messages Manual
###################

Kea is an open source implementation of the Dynamic Host Configuration
Protocol (DHCP) servers, developed and maintained by Internet Systems
Consortium (ISC).

This is the reference guide for Kea version |release|.
Links to the most up-to-date version of this document (in PDF, HTML,
and plain text formats), along with other documents for
Kea, can be found in ISC's `Knowledgebase <https://kb.isc.org/docs/kea-administrator-reference-manual>`_.


.. toctree::
   :numbered:
   :maxdepth: 5

'''

    prev_section = None
    for _, msg in sorted(messages.items()):
        section, msg_id, msg_text, msg_descr = msg

        if section != prev_section:
            prev_section = section
            rst += section + '\n'
            rst += '~' * len(section) + '\n\n'

        rst += '**' + msg_id + '**\n\n'

        rst += msg_text + '\n\n'

        rst += ''.join(['  ' + l + '\n' for l in msg_descr])
        rst += '\n'


    return rst

def generate(in_files, out_file):
    messages = read_input_files(in_files)

    rst = generate_rst(messages)

    if out_file:
        with open(out_file, 'w') as f:
            f.write(rst)
        print('Wrote generated RST content to: %s' % out_file)
    else:
        print(rst)


def main():
    args = parse_args()
    generate(args.files, args.output)


if __name__ == '__main__':
    main()
