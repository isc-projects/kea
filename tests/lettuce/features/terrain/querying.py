# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# This script provides querying functionality
# The most important step is
#
# query for <name> [type X] [class X] [to <addr>[:port]] should have rcode <rc>
#
# By default, it will send queries to 127.0.0.1:56176 unless specified
# otherwise. The rcode is always checked. If the result is not NO_ANSWER,
# the result will be stored in last_query_result, which can then be inspected
# more closely, for instance with the step
#
# "the last query response should have <property> <value>"
#
# Also see example.feature for some examples

from lettuce import *
import subprocess
import re

#
# define a class to easily access different parts
# We may consider using our full library for this, but for now
# simply store several parts of the response as text values in
# this structure.
# (this actually has the advantage of not relying on our own libraries
# to test our own, well, libraries)
#
# The following attributes are 'parsed' from the response, all as strings,
# and end up as direct attributes of the QueryResult object:
# opcode, rcode, id, flags, qdcount, ancount, nscount, adcount,
# edns_version, edns_flags, and edns_udp_size
# (flags and edns_flags are both one string with all flags, in the order
# in which they appear in the response message.)
#
# this will set 'rcode' as the result code, we 'define' one additional
# rcode, "NO_ANSWER", if the dig process returned an error code itself
# In this case none of the other attributes will be set.
#
# The different sections will be lists of strings, one for each RR in the
# section. The question section will start with ';', as per dig output
#
# See server_from_sqlite3.feature for various examples to perform queries
class QueryResult(object):
    status_re = re.compile("opcode: ([A-Z])+, status: ([A-Z]+), id: ([0-9]+)")
    edns_re = re.compile("; EDNS: version: ([0-9]+), flags: ([a-z ]*); udp: ([0-9]+)")
    flags_re = re.compile("flags: ([a-z ]+); QUERY: ([0-9]+), ANSWER: " +
                          "([0-9]+), AUTHORITY: ([0-9]+), ADDITIONAL: ([0-9]+)")

    def __init__(self, name, qtype, qclass, address, port,
                 additional_args=None):
        """
        Constructor. This fires of a query using dig.
        Parameters:
        name: The domain name to query
        qtype: The RR type to query. Defaults to A if it is None.
        qclass: The RR class to query. Defaults to IN if it is None.
        address: The IP address to send the query to.
        port: The port number to send the query to.
        additional_args: List of additional arguments (e.g. '+dnssec').
        All parameters must be either strings or have the correct string
        representation.
        Only one query attempt will be made.
        """
        args = [ 'dig', '+tries=1', '@' + str(address), '-p', str(port) ]
        if qtype is not None:
            args.append('-t')
            args.append(str(qtype))
        if qclass is not None:
            args.append('-c')
            args.append(str(qclass))
        if additional_args is not None:
            args.extend(additional_args)
        args.append(name)
        dig_process = subprocess.Popen(args, 1, None, None, subprocess.PIPE,
                                       None)
        result = dig_process.wait()
        if result != 0:
            self.rcode = "NO_ANSWER"
        else:
            self.rcode = None
            parsing = "HEADER"
            self.question_section = []
            self.answer_section = []
            self.authority_section = []
            self.additional_section = []
            self.line_handler = self.parse_header
            for out in dig_process.stdout:
                self.line_handler(out)

    def _check_next_header(self, line):
        """
        Returns true if we found a next header, and sets the internal
        line handler to the appropriate value.
        """
        if line == ";; ANSWER SECTION:\n":
            self.line_handler = self.parse_answer
        elif line == ";; OPT PSEUDOSECTION:\n":
            self.line_handler = self.parse_opt
        elif line == ";; QUESTION SECTION:\n":
            self.line_handler = self.parse_question
        elif line == ";; AUTHORITY SECTION:\n":
            self.line_handler = self.parse_authority
        elif line == ";; ADDITIONAL SECTION:\n":
            self.line_handler = self.parse_additional
        elif line.startswith(";; Query time"):
            self.line_handler = self.parse_footer
        else:
            return False
        return True

    def parse_header(self, line):
        """
        Parse the header lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            status_match = self.status_re.search(line)
            flags_match = self.flags_re.search(line)
            if status_match is not None:
                self.opcode = status_match.group(1)
                self.rcode = status_match.group(2)
            elif flags_match is not None:
                self.flags = flags_match.group(1)
                self.qdcount = flags_match.group(2)
                self.ancount = flags_match.group(3)
                self.nscount = flags_match.group(4)
                self.adcount = flags_match.group(5)

    def parse_opt(self, line):
        """
        Parse the header lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            edns_match = self.edns_re.search(line)
            if edns_match is not None:
                self.edns_version = edns_match.group(1)
                self.edns_flags = edns_match.group(2)
                self.edns_udp_size = edns_match.group(3)

    def parse_question(self, line):
        """
        Parse the question section lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            if line != "\n":
                self.question_section.append(line.strip())

    def parse_answer(self, line):
        """
        Parse the answer section lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            if line != "\n":
                self.answer_section.append(line.strip())

    def parse_authority(self, line):
        """
        Parse the authority section lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            if line != "\n":
                self.authority_section.append(line.strip())

    def parse_additional(self, line):
        """
        Parse the additional section lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        if not self._check_next_header(line):
            if line != "\n":
                self.additional_section.append(line.strip())

    def parse_footer(self, line):
        """
        Parse the footer lines of the query response.
        Parameters:
        line: The current line of the response.
        """
        pass

@step('A (dnssec )?(recursive )?query for ([\S]+) (?:type ([A-Z0-9]+) )?' +
      '(?:class ([A-Z]+) )?(?:to ([^:]+|\[[0-9a-fA-F:]+\])(?::([0-9]+))? )?' +
      'should have rcode ([\w.]+)')
def query(step, dnssec, recursive, query_name, qtype, qclass, addr, port,
          rcode):
    """
    Run a query, check the rcode of the response, and store the query
    result in world.last_query_result.
    Parameters:
    dnssec ('dnssec'): DO bit is set in the query.
                       Defaults to unset (no DNSSEC).
    recursive ('recursive'): RD bit is set in the query.
                             Defaults to unset (no recursion).
    query_name ('query for <name>'): The domain name to query.
    qtype ('type <type>', optional): The RR type to query. Defaults to A.
    qclass ('class <class>', optional): The RR class to query. Defaults to IN.
    addr ('to <address>', optional): The IP address of the nameserver to query.
                           Defaults to 127.0.0.1.
    port (':<port>', optional): The port number of the nameserver to query.
                      Defaults to 56176.
    rcode ('should have rcode <rcode>'): The expected rcode of the answer.
    """
    if qtype is None:
        qtype = "A"
    if qclass is None:
        qclass = "IN"
    if addr is None:
        addr = "127.0.0.1"
    addr = re.sub(r"\[(.+)\]", r"\1", addr) # convert [IPv6_addr] to IPv6_addr
    if port is None:
        port = 56176
    additional_arguments = []
    if dnssec is not None:
        additional_arguments.append("+dnssec")
    else:
        # some builds of dig add edns0 by default. This could muck up
        # additional counts, so unless we need dnssec, explicitly
        # disable edns0
        additional_arguments.append("+noedns")
    # dig sets RD bit by default.
    if recursive is None:
        additional_arguments.append("+norecurse")
    query_result = QueryResult(query_name, qtype, qclass, addr, port,
                               additional_arguments)
    assert query_result.rcode == rcode,\
        "Expected: " + rcode + ", got " + query_result.rcode
    world.last_query_result = query_result

@step('The SOA serial for ([\S.]+) (?:at (\S+)(?::([0-9]+)) )?should be ([0-9]+)')
def query_soa(step, query_name, address, port, serial=None):
    """
    Convenience function to check the SOA SERIAL value of the given zone at
    the nameserver at the default address (127.0.0.1:56176).
    Parameters:
    query_name ('for <name>'): The zone to find the SOA record for.
    serial ('should be <number>'): The expected value of the SOA SERIAL.
    If the rcode is not NOERROR, or the answer section does not contain the
    SOA record, this step fails.
    """
    if address is None:
        address = "127.0.0.1"
    if port is None:
        port = "56176"
    query_result = QueryResult(query_name, "SOA", "IN", address, port)
    assert "NOERROR" == query_result.rcode,\
        "Got " + query_result.rcode + ", expected NOERROR"
    assert len(query_result.answer_section) == 1,\
        "Too few or too many answers in SOA response"
    soa_parts = query_result.answer_section[0].split()
    assert serial == soa_parts[6],\
        "Got SOA serial " + soa_parts[6] + ", expected " + serial

@step('last query response should have (\S+) (.+)')
def check_last_query(step, item, value):
    """
    Check a specific value in the reponse from the last successful query sent.
    Parameters:
    item: The item to check the value of
    value: The expected value.
    This performs a very simple direct string comparison of the QueryResult
    member with the given item name and the given value.
    Fails if the item is unknown, or if its value does not match the expected
    value.
    """
    assert world.last_query_result is not None
    assert item in world.last_query_result.__dict__
    lq_val = world.last_query_result.__dict__[item]
    assert str(value) == str(lq_val),\
           "Got: " + str(lq_val) + ", expected: " + str(value)

@step('([a-zA-Z]+) section of the last query response should (exactly )?be')
def check_last_query_section(step, section, exact):
    """
    Check the entire contents of the given section of the response of the last
    query.
    Parameters:
    section ('<section> section'): The name of the section (QUESTION, ANSWER,
                                   AUTHORITY or ADDITIONAL).
    The expected response is taken from the multiline part of the step in the
    scenario. Differing whitespace is ignored, the order of the lines is
    ignored, and the comparison is case insensitive.
    Fails if they do not match.
    WARNING: Case insensitivity is not strictly correct; for instance the
    data of TXT RRs would be case sensitive. But most other output is, so
    currently the checks are always case insensitive. Should we decide
    these checks do need to be case sensitive, we can either remove it
    or make it optional (for the former, we'll need to update a number of
    tests).
    """
    response_string = None
    if section.lower() == 'question':
        response_string = "\n".join(world.last_query_result.question_section)
    elif section.lower() == 'answer':
        response_string = "\n".join(world.last_query_result.answer_section)
    elif section.lower() == 'authority':
        response_string = "\n".join(world.last_query_result.authority_section)
    elif section.lower() == 'additional':
        response_string = "\n".join(world.last_query_result.additional_section)
    else:
        assert False, "Unknown section " + section

    # Now mangle the data for 'conformance'
    # This could be done more efficiently, but is done one
    # by one on a copy of the original data, so it is clear
    # what is done. Final error output is currently still the
    # original unchanged multiline strings

    # replace whitespace of any length by one space
    response_string = re.sub("[ \t]+", " ", response_string)
    expect = re.sub("[ \t]+", " ", step.multiline)
    # lowercase them unless we need to do an exact match
    if exact is None:
        response_string = response_string.lower()
        expect = expect.lower()
    # sort them
    response_string_parts = response_string.split("\n")
    response_string_parts.sort()
    response_string = "\n".join(response_string_parts)
    expect_parts = expect.split("\n")
    expect_parts.sort()
    expect = "\n".join(expect_parts)

    assert response_string.strip() == expect.strip(),\
        "Got:\n'" + response_string + "'\nExpected:\n'" + step.multiline +"'"

