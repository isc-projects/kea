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

# Produce System Messages Manual
#
# This tool reads all the .mes files in the directory tree whose root is given
# on the command line and interprets them as BIND 10 message files.  It pulls
# all the messages and description out, sorts them by message ID, and writes
# them out as a single (formatted) file.
#
# Invocation:
# The code is invoked using the command line:
#
# python system_messages.py [-o <output-file>] <top-source-directory>
#
# If no output file is specified, output is written to stdout.

import re
import os
import sys
from optparse import OptionParser

# Main dictionary holding all the messages.  The messages are accumulated here
# before being printed in alphabetical order.
dictionary = {}

# The structure of the output page is:
#
#        header
#           message
#        separator
#           message
#        separator
#          :
#        separator
#           message
#        trailer
#
# (Indentation is not relevant - it has only been added to the above
# illustration to make the structure clearer.)  The text of these section is:

# Header - this is output before anything else.
SEC_HEADER = """<html>
<head>
<title>BIND 10 System Messages</title>
<link rel="stylesheet" href="./bind10-guide.css" type="text/css">
</head>
<body>
<h1>BIND 10 System Messages</h1>
<p/>
"""

# This is output once for each message.  The string contains substitution
# tokens: $I is replaced by the message identification, $T by the message text,
# and $D by the message description.
SEC_MESSAGE = """<b><a name="$I">$I</a></b>, $T<br/>
$D"""

# A description may contain blank lines intended to separate paragraphs.  If so,
# each blank line is replaced by the following.
SEC_BLANK = "<p/>"

# The separator is copied to the output verbatim after each message except
# the last.
SEC_SEPARATOR = "<p/>"

# The trailier is copied to the output verbatim after the last message.
SEC_TRAILER = """</body>
</html>"""


def reportError(filename, what):
    """Report an error and exit"""
    print("*** ERROR in ", filename, file=sys.stderr)
    print("*** REASON: ", what, file=sys.stderr)
    print("*** System message generator terminating", file=sys.stderr)
    sys.exit(1)



# Printing functions
def printHeader():
    print(SEC_HEADER)

def printSeparator():
    print(SEC_SEPARATOR)

def printMessage(msgid):
    m1 = SEC_MESSAGE.replace("$I", msgid)
    m2 = m1.replace("$T", dictionary[msgid]['text'])
    m3 = m2.replace("$D", dictionary[msgid]['description'])
    print(m3)

def printTrailer():
    print(SEC_TRAILER)



def replaceBlankLines(lines):
    """Replaces blank lines in an array with the contents of the 'blank'
       section.
    """
    result = []
    for l in lines:
        if len(l) == 0:
            result.append(SEC_BLANK)
        else:
            result.append(l)

    return result



def removeEmptyLeadingTrailing(lines):
    """Removes leading and trailing empty lines.

       A list of strings is passed as argument, some of which may be empty.
       This function removes from the start and end of list a contiguous
       sequence of empty lines and returns the result.  Embedded sequence of
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



def addToDictionary(msgid, msgtext, desc, filename):
    """Add the current message ID and associated information to the global
       dictionary.  If a message with that ID already exists, loop appending
       suffixes of the form "(n)" to it until one is found that doesn't.

       Parameters:
       msgid        Message ID
       msgtext      Message text
       desc         Message description
       filename     File from which the message came.  Currently this is
                    not used, but a future enhancement may wish to include the
                    name of the message file in the messages manual.
    """

    # If the ID is in the dictionary, append a "(n)" to the name - this wil
    # flag that there are multiple instances.  (However, this is an error -
    # each ID should be unique in BIND-10.)
    if msgid in dictionary:
        i = 1
        while msgid + " (" + str(i) + ")" in dictionary:
            i = i + 1
        msgid = msgid + " (" + str(i) + ")"

    # Remove leading and trailing blank lines, and replace embedded blanks
    # with the blank section element.
    modified_desc = replaceBlankLines(removeEmptyLeadingTrailing(desc))

    # Put everything in a sub-dictionary that is added to the main one.  At
    # this point, for ease of subsequent processing the description lines are
    # concatenated together to form a single string, the lines being separated
    # by a newline.
    details = {}
    details['text'] = msgtext
    details['description'] = "\n".join(modified_desc)
    details['filename'] = filename
    dictionary[msgid] = details



def processFileContent(filename, lines):
    """Processes file content.  Messages and descriptions are identified and
       added to a dictionary (keyed by message ID).  If the key already exists,
       a numeric suffix is added to it.

       Parameters:
       filename     Name of the message file being processed
       lines        Lines read from the file
    """

    prefix = ""         # Last prefix encountered
    msgid = ""          # Last message ID encountered
    msgtext = ""        # Text of the message
    description = []    # Description

    for l in lines:
        if l.startswith("$"):
            # Starts with "$".  Ignore anything other than $PREFIX
            words = re.split("\s+", l)
            if words[0].upper() == "$PREFIX":
                if len(words) == 1:
                    prefix = ""
                else:
                    prefix = words[1]

        elif l.startswith("%"):
            # Start of a message.  Add the message we were processing to the
            # dictionary and clear everything apart from the file name.
            if msgid != "":
                addToDictionary(msgid, msgtext, description, filename)

            msgid = ""
            msgtext = ""
            description = []

            # Start of a message
            l = l[1:].strip()       # Remove "%" and trim leading spaces
            if len(l) == 0:
                printError(filename, "Line with single % found")
                next

            # Split into words.  The first word is the message ID
            words = re.split("\s+", l)
            msgid = (prefix + words[0]).upper()
            msgtext = l[len(words[0]):].strip()

        else:
            # Part of a description, so add to the current description array
            description.append(l)

    # All done, add the last message to the global dictionaty.
    if msgid != "":
        addToDictionary(msgid, msgtext, description, filename)


#
# \param file Name of the file to process

def processFile(filename):
    """Processes a file by reading it in and stripping out all comments and
       and directives.  Leading and trailing blank lines in the file are removed
       and the remainder passed for message processing.

       Parameters:
       filename     Name of the message file to process
    """
    lines = open(filename).readlines();

    # Trim leading and trailing spaces from each line, and remove comments.
    lines = [l.strip() for l in lines]
    lines = [l for l in lines if not l.startswith("#")]

    # Remove leading/trailing empty line sequences from the result
    lines = removeEmptyLeadingTrailing(lines)

    # Interpret content
    processFileContent(filename, lines)



def processAllFiles(root):
    """Iterates through all files in the tree starting at the given root and
       calls processFile for all .mes files found.

       Parameters:
       root     Directory that is the root of the BIND-10 source tree
    """
    for (path, dirs, files) in os.walk(root):

        # Identify message files
        mes_files = [f for f in files if f.endswith(".mes")]

        # ... and process each file in the list
        for m in mes_files:
            processFile(path + os.sep + m)


# Main program
if __name__ == "__main__":
    parser = OptionParser(usage="Usage: %prog [--help | options] root")
    parser.add_option("-o", "--output", dest="output", default=None,
                      metavar="FILE", 
                      help="output file name (default to stdout)")
    (options, args) = parser.parse_args()

    if len(args) == 0:
        parser.error("Must supply directory at which to begin search")
    elif len(args) > 1:
        parser.error("Only a single root directory can be given")

    # Redirect output if specified (errors are written to stderr)
    if options.output is not None:
        sys.stdout = open(options.output, 'w')

    # Read the files and load the data
    processAllFiles(args[0])

    # Now just list the message IDs and text in the global dictionary
    count = 1
    printHeader()
    for msgid in sorted(dictionary):
        if count > 1:
            printSeparator()
        count = count + 1
        printMessage(msgid)
    printTrailer()
