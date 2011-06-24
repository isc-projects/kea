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
SEC_HEADER="""<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE book PUBLIC "-//OASIS//DTD DocBook XML V4.2//EN"
"http://www.oasis-open.org/docbook/xml/4.2/docbookx.dtd" [
<!ENTITY mdash  "&#x2014;" >
<!ENTITY % version SYSTEM "version.ent">
%version;
]>
<book>
  <?xml-stylesheet href="bind10-guide.css" type="text/css"?>

  <bookinfo>
    <title>BIND 10 Messages Manual</title>

    <copyright>
      <year>2011</year><holder>Internet Systems Consortium, Inc.</holder>
    </copyright>

    <abstract>
      <para>BIND 10 is a Domain Name System (DNS) suite managed by
	  Internet Systems Consortium (ISC). It includes DNS libraries
	  and modular components for controlling authoritative and
	  recursive DNS servers.
      </para>
      <para>
        This is the messages manual for BIND 10 version &__VERSION__;.
	    The most up-to-date version of this document, along with
	    other documents for BIND 10, can be found at
        <ulink url="http://bind10.isc.org/docs"/>.
      </para>
    </abstract>

    <releaseinfo>This is the messages manual for BIND 10 version
        &__VERSION__;.</releaseinfo>
  </bookinfo>

  <chapter id="intro">
    <title>Introduction</title>
    <para>
      This document lists each message that can be logged by the
      programs in the BIND 10 package.  Each entry in this manual
      is of the form:
      <screen>IDENTIFICATION message-text</screen>
      ... where "IDENTIFICATION" is the message identification included
      in each message logged and "message-text" is the accompanying
      message text.  The "message-text" may include placeholders of the
      form "%1", "%2" etc.; these parameters are replaced by relevant
      values when the message is logged.
    </para>
    <para>
      Each entry is also accompanied by a description giving more
      information about the circumstances that result in the message
      being logged.
    </para>
    <para>
      For information on configuring and using BIND 10 logging,
      refer to the <ulink url="bind10-guide.html">BIND 10 Guide</ulink>.
    </para>
  </chapter>

  <chapter id="messages">
    <title>BIND 10 Messages</title>
    <para>
      <variablelist>
"""

# This is output once for each message.  The string contains substitution
# tokens: $I is replaced by the message identification, $T by the message text,
# and $D by the message description.
SEC_MESSAGE = """<varlistentry id="$I">
<term>$I, $T</term>
<listitem><para>
$D
</para></listitem>
</varlistentry>"""

# A description may contain blank lines intended to separate paragraphs.  If so,
# each blank line is replaced by the following.
SEC_BLANK = "</para><para>"

# The separator is copied to the output verbatim after each message except
# the last.
SEC_SEPARATOR = ""

# The trailier is copied to the output verbatim after the last message.
SEC_TRAILER = """      </variablelist>
    </para>
  </chapter>
</book>
"""


def reportError(filename, what):
    """Report an error and exit"""
    print("*** ERROR in ", filename, file=sys.stderr)
    print("*** REASON: ", what, file=sys.stderr)
    print("*** System message generator terminating", file=sys.stderr)
    sys.exit(1)



def replaceTag(string):
    """Replaces the '<' and '>' in text about to be inserted into the template
       sections above with &lt; and &gt; to avoid problems with message text
       being interpreted as XML text.
    """
    string1 = string.replace("<", "&lt;")
    string2 = string1.replace(">", "&gt;")
    return string2



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



# Printing functions
def printHeader():
    print(SEC_HEADER)

def printSeparator():
    print(SEC_SEPARATOR)

def printMessage(msgid):
    # In the message ID, replace "<" and ">" with XML-safe versions and
    # substitute into the data.
    m1 = SEC_MESSAGE.replace("$I", replaceTag(msgid))

    # Do the same for the message text.
    m2 = m1.replace("$T", replaceTag(dictionary[msgid]['text']))

    # Do the same for the description then replace blank lines with the
    # specified separator.  (We do this in that order to avoid replacing
    # the "<" and ">" in the XML tags in the separator.)
    desc1 = [replaceTag(l) for l in dictionary[msgid]['description']]
    desc2 = replaceBlankLines(desc1)

    # Join the lines together to form a single string and insert into
    # current text.
    m3 = m2.replace("$D", "\n".join(desc2))

    print(m3)

def printTrailer():
    print(SEC_TRAILER)



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

    # Remove leading and trailing blank lines in the description, then
    # add everything into a subdictionary which is then added to the main
    # one.
    details = {}
    details['text'] = msgtext
    details['description'] = removeEmptyLeadingTrailing(desc)
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

    # Now just print out everything we've read (in alphabetical order).
    count = 1
    printHeader()
    for msgid in sorted(dictionary):
        if count > 1:
            printSeparator()
        count = count + 1
        printMessage(msgid)
    printTrailer()
