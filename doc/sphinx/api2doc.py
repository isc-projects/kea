#!/usr/bin/env python3

# Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http:#mozilla.org/MPL/2.0/.

# Produce API Reference
# - reads *.json files (each file describes a single command)
# - produces .rst file suitable for Sphinx as output

import os
import json
import argparse
import collections


def parse_args():
    parser = argparse.ArgumentParser(description='Convert set of *.json files to .rst documentation format')
    parser.add_argument('-o', '--output', help='Output file name (default to stdout).')
    parser.add_argument('files', help='Input API .json files.', nargs='+')

    args = parser.parse_args()
    return args


def read_input_files(files):
    apis = {}
    for f in files:
        name = os.path.basename(f)[:-5]
        # Skip special names starting with _ (such as _template.json)
        if name.startswith('_'):
            print("Skipping %s (starts with underscore)" % f)
            continue
        with open(f) as fp:
            print("Processing %s" % f)
            # use OrderedDict to preserve order of fields in cmd-syntax
            try:
                descr = json.load(fp, object_pairs_hook=collections.OrderedDict)
            except:
                print('\nError while processing %s\n\n' % f)
                raise
            assert name == descr['name']
        apis[name] = descr

    return apis


def generate_rst(apis):
    rst = '''.. _api:

API Reference
=============

'''

    daemons = {}
    hooks = {}
    for func in apis.values():
        for dm in func['support']:
            if dm not in daemons:
                daemons[dm] = []
            daemons[dm].append(func)

        if 'hook' in func:
            if func['hook'] not in hooks:
                hooks[func['hook']] = []
            hooks[func['hook']].append(func)

    rst += 'Kea currently supports %d commands in %s daemons and %s hook libraries.\n\n' % (
        len(apis),
        ", ".join([':ref:`%s <commands-%s>`' % (m, m) for m in sorted(daemons.keys())]),
        ", ".join([':ref:`%s <commands-%s>`' % (m, m) for m in sorted(hooks.keys())]))

    for dm, funcs in sorted(daemons.items()):
        rst += '.. _commands-%s:\n\n' % dm
        rst += 'Commands supported by `%s` daemon: ' % dm
        funcs = sorted([ ':ref:`%s <ref-%s>`' % (f['name'], f['name']) for f in funcs])
        rst += ', '.join(funcs)
        rst += '.\n\n'

    for h, funcs in sorted(hooks.items()):
        rst += '.. _commands-%s:\n\n' % h
        rst += 'Commands supported by `%s` hook library: ' % h
        funcs = sorted([ ':ref:`%s <ref-%s>`' % (f['name'], f['name']) for f in funcs])
        rst += ', '.join(funcs)
        rst += '.\n\n'

    for func in sorted(apis.values(), key=lambda f: f['name']):
        name = func['name']
        rst += '.. _ref-%s:\n\n' % name
        rst += name + '\n'
        rst += '-' * len(name) + '\n\n'

        # command overview
        for brief_line in func['brief']:
            rst += '%s\n' % brief_line
        rst += '\n'

        # command can be issued to the following daemons
        rst += 'Supported by: '
        rst += ', '.join(sorted([':ref:`%s <commands-%s>`' % (dm, dm) for dm in func['support']]))
        rst += '\n\n'

        # availability
        rst += 'Availability: %s ' % func['avail']
        rst += '(:ref:`%s <commands-%s>` hook library)' % (func['hook'], func['hook']) if 'hook' in func else '(built-in)'
        rst += '\n\n'

        # description and examples
        rst += 'Description and examples: see :ref:`%s command <command-%s>`\n\n' % (name, name)

        # command syntax
        rst += 'Command syntax:\n\n'
        rst += '::\n\n'
        if 'cmd-syntax' in func:
            cmd_syntaxes = [func['cmd-syntax']]
            if isinstance(cmd_syntaxes, dict):
                cmd_syntaxes = [cmd_syntax]
            for cmd_syntax in cmd_syntaxes:
                if 'comment' in cmd_syntax:
                    rst += cmd_syntax['comment']
                    rst += '\n\n'
                    del cmd_syntax['comment']

                for line in cmd_syntax:
                    rst += '    %s\n' % line
        else:
            rst += '   {\n'
            rst += '       "command": \"%s\"\n' % name
            rst += '   }'
        rst += '\n\n'

        if 'cmd-comment' in func:
            for l in func['cmd-comment']:
                rst += "%s\n" % l
            rst += '\n'

        # response syntax
        rst += 'Response syntax:\n\n'
        rst += '::\n\n'
        if 'resp-syntax' in func:
            resp_syntaxes = [func['resp-syntax']]
            if isinstance(resp_syntaxes, dict):
                resp_syntaxes = [resp_syntax]
            for resp_syntax in resp_syntaxes:

                for line in resp_syntax:
                    rst += '    %s\n' % line

        else:
            rst += '   {\n'
            rst += '       "result": <integer>,\n'
            rst += '       "text": "<string>"\n'
            rst += '   }'
        rst += '\n\n'

        if 'resp-comment' in func:
            for resp_comment_line in func['resp-comment']:
                rst += "%s\n" % resp_comment_line
            rst += '\n\n'
        else:
            rst += 'Result is an integer representation of the status. Currently supported statuses are:\n\n'
            rst += '- 0 - success\n'
            rst += '- 1 - error\n'
            rst += '- 2 - unsupported\n'
            rst += '- 3 - empty (command was completed successfully, but no data was affected or returned)\n\n'

    return rst


def generate(in_files, out_file):
    apis = read_input_files(in_files)

    rst = generate_rst(apis)

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
