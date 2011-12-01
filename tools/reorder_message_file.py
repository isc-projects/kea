# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

# Reorder Message File
#
# Reads a message file into memory, then outputs it with the messages and
# associated descriptions in alphabetical order.
#
# Invocation:
# The code is invoked using the command line:
#
# python reorder.py message_file
#
# Output is written to stdout.

import sys

def removeEmptyLeadingTrailing(lines):
    """
    Removes leading and trailing empty lines.

    A list of strings is passed as argument, some of which may be empty.
    This function removes from the start and end of the list a contiguous
    sequence of empty lines and returns the result.  Embedded sequences of
    empty lines are not touched.

    Parameters:
    lines List of strings to be modified.

    Return:
    Input list of strings with leading/trailing blank line sequences
    removed.
    """

    retlines = []

    # Dispose of degenerate case of empty array
    if len(lines) == 0:
        return retlines

    # Search for first non-blank line
    start = 0
    while start < len(lines):
        if len(lines[start]) > 0:
            break
        start = start + 1

    # Handle case when entire list is empty
    if start >= len(lines):
        return retlines

    # Search for last non-blank line
    finish = len(lines) - 1
    while finish >= 0:
        if len(lines[finish]) > 0:
            break
        finish = finish - 1

    retlines = lines[start:finish + 1]
    return retlines


def canonicalise_message_line(line):
    """
    Given a line known to start with the '%' character (i.e. a line
    introducing a message), canonicalise it by ensuring that the result
    is of the form '%<single-space>MESSAGE_IDENTIFIER<single-space>text'.

    Parameters:
    line - input line.  Known to start with a '%' and to have leading
           and trailing spaces removed.

    Return:
    Canonicalised line.
    """
    # Cope with degenerate case of a single "%"
    if len(line) == 1:
        return line

    # Get the rest of the line
    line = line[1:].lstrip()

    # Extract the first word (the message ID)
    words = line.split()
    message_line = "% " + words[0]

    # ... and now the rest of the line
    if len(line) > len(words[0]):
        message_line = message_line + " " + line[len(words[0]):].lstrip()

    return message_line


def make_dict(lines):
    """
    Split the lines into segments starting with the message definition and
    place into a dictionary.

    Parameters:
    lines - list of lines containing the text of the message file (less the
            header).

    Returns:
    dictionary - map of the messages, keyed by the line that holds the message
                 ID.
    """

    dictionary = {}

    message_key = canonicalise_message_line(lines[0])
    message_lines = [message_key]
    index = 1;
    while index < len(lines):
        if lines[index].startswith("%"):
            # Start of new message
            dictionary[message_key] = removeEmptyLeadingTrailing(message_lines)
            message_key = canonicalise_message_line(lines[index])
            message_lines = [message_key]
        else:
            message_lines.append(lines[index])

        index = index + 1

    dictionary[message_key] = removeEmptyLeadingTrailing(message_lines)

    return dictionary


def print_dict(dictionary):
    """
    Prints the dictionary with a blank line between entries.

    Parameters:
    dicitionary - Map holding the message dictionary
    """
    count = 0
    for msgid in sorted(dictionary):

        # Blank line before all entries but the first
        if count > 0:
            print("")
        count = count + 1

        # ... and the entry itself.
        for l in dictionary[msgid]:
            print(l.strip())


def processFile(filename):
    """
    Processes a file by reading it and searching for the first line starting
    with the '%' sign.  Everything before that line is treated as the file
    header and is copied to the output with leading and trailing spaces removed.
    After that, each message block is read and stored for later sorting.

    Parameters:
    filename     Name of the message file to process
    """
    lines = open(filename).read().splitlines()

    # Search for the first line starting with the percent character.  Everything
    # before it is considered the file header and is copied to the output with
    # leading and trailing spaces removed.
    index = 0
    while index < len(lines):
        if lines[index].startswith("%"):
            break
        print(lines[index].strip())
        index = index + 1

    # Now put the remaining lines into the message dictionary
    dictionary = make_dict(lines[index:])

    # ...and print it
    print_dict(dictionary)


# Main program
if __name__ == "__main__":

    # Read the files and load the data
    if len(sys.argv) != 2:
        print "Usage: python reorder.py message_file"
    else:
        processFile(sys.argv[1])
