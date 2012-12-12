# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

"""\
This script checks output of gen-statisticsitems.py.

This script checks XML file. Spec file, C++ code and header files syntax is
checked in the other unittests or system tests.
"""

import os
import sys
from xml.etree import ElementTree

"""\
User-defined exception for parse error. It is thrown if a file is not
formatted as expected.
"""
class ParseError(Exception):
    pass

"""\
Test XML file.

It should have <refsect1> which has <title>STATISTICS DATA</title>.
Inside the section, it should have one or more <varlistentry> of each item
inside <variablelist>.
Each <varlistentry> should have <term> for item name and <simpara> inside
<listitem> for item description.

Example:
    <refsect1>
        <title>STATISTICS DATA</title>
        <variablelist>
            <varlistentry>
                <term>item1</term>
                <listitem>
                    <simpara>
                        statistics item
                    </simpara>
                </listitem>
            </varlistentry>
            <varlistentry>
                <term>item2</term>
                <listitem>
                    <simpara>
                        another statistics item
                    </simpara>
                </listitem>
            </varlistentry>
        </variablelist>
    </refsect1>
"""
def testXMLfile(xmlfilepath):
    xmltree = ElementTree.parse(xmlfilepath)
    root = xmltree.getroot()
    # find <refsect1> which has <title> of 'STATISTICS DATA'
    stats_node = [t for t in root.findall('./refsect1')
            if t.find('./title').text == 'STATISTICS DATA']
    if not stats_node:
        raise ParseError('Statistics data section does not exist')
    # find all <varlistentry> inside <variablelist>
    entries = stats_node[0].find('./variablelist').findall('./varlistentry')
    if not entries:
        raise ParseError('<varlistentry> does not exist inside section')
    for entry in entries:
        # find <term> for item name
        name = entry.find('./term')
        if name is None or name.text == '':
            raise ParseError('<term> for item name does not exist')
        # find <simpara> inside <listitem> for item description
        description = entry.find('./listitem/simpara')
        if description is None or description.text == '':
            raise ParseError('<listitem> nor <simpara> for item description'
                             ' does not exist')
    return

if __name__ == "__main__":
    xmlfilepath = sys.argv[1]
    testXMLfile(xmlfilepath)
