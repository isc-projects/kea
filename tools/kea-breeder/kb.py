#!/usr/bin/env python3

import argparse
from termcolor import colored, cprint
from io import StringIO
import json
import os
import re
import sqlalchemy as db
from sqlalchemy.sql import select
import sys

def convert_to_db(entity_name, make_singular=True):
    sql_name = entity_name.replace('-', '_').lower()
    if not make_singular:
        return sql_name

    if not re.search(r'ddns$', sql_name) and not re.search(r'times$', sql_name):
        replacements = [
            [r'classes', 'class'],
            [r'ies', 'y'],
            [r's$', '']
        ]

        for r in replacements:
            new_name = re.sub(r[0], r[1], sql_name)
            if new_name != sql_name:
                break
        sql_name = new_name

    return sql_name

class State:
    def __init__(self, config, database, path = None, token_name = None):
        self.config = config
        self.database = database
        if path is not None:
            self._path = path
        else:
            self._path = []

        if token_name is not None:
            self._path += [token_name]

    def copy(self, token_name = None):
        return State(self.config, self.database, self._path.copy(), token_name)

    def sql_prefix(self):
        return self._path[0].lower()

    def sql_parent_name(self):
        return convert_to_db(self.get_parent_name())

    def sql_current_name(self):
        return convert_to_db(self.get_current_name(), False)

    def sql_current_global_name(self):
        return self.sql_parent_name() + '_' + self.sql_current_name()

    def sql_global_table_name(self):
        return self.sql_parent_name() + '_global_parameter'

    def sql_parent_table_name(self):
        return self.config.get_mapped_table_name('{0}_{1}'.format(self.sql_prefix(), self.sql_parent_name()))

    def sql_table_name(self):
        return self.config.get_mapped_table_name('{0}_{1}'.format(self.sql_prefix(), convert_to_db(self.get_current_name(), True)))

    def get_parent_name(self):
        return self._path[-2]

    def get_current_name(self):
        if self._path:
            return self._path[-1]
        return None

    def get_path(self):
        return self._path

    def get_path_len(self):
        return len(self._path)

class ConfigFile:
    def __init__(self, filename):
        self.filename = filename

    def load(self):
        if not os.path.exists(self.filename):
            print('The all keys file %s does not exist.' % self.filename)
            sys.exit(1)

        with open(self.filename) as f:
            self.config = json.load(f)
            f.close()

    def get_mapped_table_name(self, generated_name):
        mappings = self.config['sql_table_mappings']
        if not mappings or generated_name not in mappings.keys():
            return generated_name

        return mappings[generated_name]['actual_name']

    def is_ignored_parameter(self, name):
        ignored_parameters = self.config['ignored_parameters']
        return name in ignored_parameters

class KeaDatabase:
    def __init__(self):
        engine = db.create_engine('mysql+mysqldb://root@localhost/keatest')
        self.connection = engine.connect()

    def has_table(self, table_name):
        sql = db.text(
            "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = :table_name"
        )
        result = self.connection.execute(sql, {"table_name": table_name}).fetchone()
        return result[0] > 0

    def has_column(self, table_name, column_name):
        sql = db.text(
            "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = :table_name AND COLUMN_NAME = :column_name"
        )
        result = self.connection.execute(sql, {"table_name": table_name, "column_name": column_name}).fetchone()
        return result[0] > 0

def traverse(state, parents, json_object):
    if state.config.is_ignored_parameter(state.get_current_name()):
        return

    new_parents = parents.copy()
    new_parents.append(json_object)

    comment = ''

    if state.get_path_len() == 1:
        # Top level configuration item, e.g. Dhcp4.
        comment = cprint(text='Top level configuration item', color='green')

    elif state.get_path_len() == 2 and not isinstance(json_object, list) and not isinstance(json_object, dict):
        # Global primitive value, e.g. boolean. Kea has a dedicated table for them.
        comment = cprint(text='Set primitive value {0} in {1} table'.format(state.sql_current_name(), state.sql_global_table_name()), color='green')

    else:
        # Handle primitives at lower levels.
        if not isinstance(json_object, dict) and not isinstance(json_object, list):
            if isinstance(parents[-1], dict) and isinstance(parents[-2], dict):
                if state.get_path_len() > 3:
                    # If the primitive belongs to a hierarchy of two maps, the structure of
                    # the lower level map must be flattened and the respective parameters
                    # must be moved to the upper level map.
                    comment = cprint(text='Create column {0} in the parent table'.format(state.sql_current_name()), color='red')
                else:
                    # An exception is the parameter belonging to the top level maps, e.g.
                    # Dhcp4/map/primitive. This primitive goes to the dhcp4_global_parameter
                    # table.
                    comment = cprint(text='Use global parameter {0}'.format(state.sql_current_global_name()), color='yellow')

            elif isinstance(parents[-1], dict) and isinstance(parents[-2], list):
                # A list of maps deserves its own table. For example: subnet4 or
                # shared_networks, option_def etc.
                if state.database.has_column(state.sql_parent_table_name(), state.sql_current_name()):
                    comment = cprint(text='Column {0} in {1} table exists'.format(state.sql_current_name(), state.sql_parent_table_name()), color='green')
                else:
                    comment = cprint(text='Create column {0} in {1} table'.format(state.sql_current_name(), state.sql_parent_table_name()), color='red')

        elif isinstance(json_object, list):
            if json_object and isinstance(json_object[0], dict):
                if state.database.has_table(state.sql_table_name()):
                    comment = cprint(text='Table {0} exists'.format(state.sql_table_name()), color='green')
                else:
                    comment = cprint(text='Create table {0}'.format(state.sql_table_name()), color='red')
            else:
                comment = cprint(text='Unable to determine children types because all-keys file contains no children for this object', color='red')

        elif isinstance(json_object, dict):
            if len(parents) > 1 and isinstance(parents[-2], dict):
                if state.get_path_len() == 2:
                    comment = cprint(text='Parameters belonging to this map should be in {0}'.format(state.sql_global_table_name()), color='yellow')

    # Format printing the current object depending on its type.
    if isinstance(json_object, dict):
        if parents and not isinstance(parents[-1], list):
            # Only print the map information if the parent is not a list. Otherwise
            # it will be printed twice.
            print('{0}/dict: {1}'.format(state.get_path(), comment))

        # Print each child of the map with recursion.
        for key in sorted(json_object.keys()):
            traverse(state.copy(key), parents + [json_object], json_object[key])

    elif isinstance(json_object, list) and len(json_object):
        # If it is a list, print only the first element using recursion.
        # All elements of the list should have the same type, so it makes
        # no sense to print all of them.
        print('{0}/list: {1}'.format(state.get_path(), comment))
        traverse(state.copy(), parents + [json_object], json_object[0])

    else:
        # It is neither a list nor a map, so it must be a primitive. Print it
        # along with a comment.
        print('{0}/{1}: {2}'.format(state.get_path(), type(json_object).__name__, comment))

def main():
    parser = argparse.ArgumentParser(description='Kea Developer Tools')
    parser.add_argument('--all-keys-file', metavar='all_keys_file', required=True,
                        help='Kea all_keys.json file location.')
    parser.add_argument('--config-file', metavar='config_file', required=True,
                        help='Configuration file location for this tool.')
    args = parser.parse_args()

    config = ConfigFile(args.config_file)
    config.load()

    if not os.path.exists(args.all_keys_file):
        print('The all keys file %s does not exist.' % args.all_keys_file)
        sys.exit(1)

    sanitized_contents = ''
    f = open(args.all_keys_file)
    for line in f:
        sanitized_line = line.strip()
        if not sanitized_line:
            continue

        if sanitized_line.find('//') != -1 or sanitized_line.find('#') != -1:
            continue

        sanitized_line = sanitized_line.replace(': .', ': 0.')
        sanitized_contents = sanitized_contents + sanitized_line

    f.close()

    io = StringIO(sanitized_contents)
    parsed = json.load(io)

    database = KeaDatabase()

    traverse(State(config, database), [], parsed)

if __name__ == '__main__':
    main()
