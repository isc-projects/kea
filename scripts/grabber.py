#!/usr/bin/env python3

import fnmatch
import pathlib
import sys


def main(directory, pattern):
    current_dir = pathlib.Path(directory)
    files = []
    for item in current_dir.iterdir():
        if item.is_file() and fnmatch.fnmatch(item.name, pattern):
            files.append(item.name)
    files = sorted(files)
    for file in files:
        print(file)


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
