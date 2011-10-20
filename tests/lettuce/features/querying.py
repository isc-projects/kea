from lettuce import *
import subprocess
import re

# This script provides querying functionality
# The most important step is
#
# query for <name> [type X] [class X] [to <addr>[:port]] should have rcode <rc>
#
# By default, it will send queries to 127.0.0.1:47806 unless specified
# otherwise. The rcode is always checked. If the result is not NO_ANSWER,
# the result will be stored in last_query_result, which can then be inspected
# more closely, for instance with the step
#
# last query should have <property> <value>
#

#
# define a class to easily access different parts
# We may consider using our full library for this, but for now
# simply store several parts of the response as text values in
# this structure
#
# The following attributes are 'parsed' from the response, all as strings,
# and end up as direct attributes of the QueryResult object:
# opcode, rcode, id, flags, qdcount, ancount, nscount, adcount
# (flags is one string with all flags)
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
    flags_re = re.compile("flags: ([a-z ]+); QUERY: ([0-9]+), ANSWER: " +
                          "([0-9]+), AUTHORITY: ([0-9]+), ADDITIONAL: ([0-9]+)")

    def __init__(self, name, qtype, qclass, address, port):
        args = [ 'dig', '+tries=1', '@' + address, '-p', str(port) ]
        if qtype is not None:
            args.append('-t')
            args.append(str(qtype))
        if qclass is not None:
            args.append('-c')
            args.append(str(qclass))
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

    def parse_header(self, line):
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
        elif line == ";; QUESTION SECTION:\n":
            self.line_handler = self.parse_question

    def parse_question(self, line):
        if line == ";; ANSWER SECTION:\n":
            self.line_handler = self.parse_answer
        elif line != "\n":
            self.question_section.append(line)

    def parse_answer(self, line):
        if line == ";; AUTHORITY SECTION:\n":
            self.line_handler = self.parse_authority
        elif line != "\n":
            self.answer_section.append(line)

    def parse_authority(self, line):
        if line == ";; ADDITIONAL SECTION:\n":
            self.line_handler = self.parse_additional
        elif line != "\n":
            self.additional_section.append(line)

    def parse_authority(self, line):
        if line.startswith(";; Query time"):
            self.line_handler = self.parse_footer
        elif line != "\n":
            self.additional_section.append(line)

    def parse_footer(self, line):
        pass

@step('A query for ([\w.]+) (?:type ([A-Z]+) )?(?:class ([A-Z]+) )?' +
      '(?:to ([^:]+)(?::([0-9]+))? )?should have rcode ([\w.]+)')
def query(step, query_name, qtype, qclass, addr, port, rcode):
    if qtype is None:
        qtype = "A"
    if qclass is None:
        qclass = "IN"
    if addr is None:
        addr = "127.0.0.1"
    if port is None:
        port = 47806
    query_result = QueryResult(query_name, qtype, qclass, addr, port)
    assert query_result.rcode == rcode, "Got " + query_result.rcode
    world.last_query_result = query_result

@step('The SOA serial for ([\w.]+) should be ([0-9]+)')
def query_soa(step, query_name, serial):
    query_result = QueryResult(query_name, "SOA", "IN", "127.0.0.1", "47806")
    assert "NOERROR" == query_result.rcode,\
        "Got " + query_result.rcode + ", expected NOERROR"
    assert len(query_result.answer_section) == 1,\
        "Too few or too many answers in SOA response"
    soa_parts = query_result.answer_section[0].split()
    assert serial == soa_parts[6],\
        "Got SOA serial " + soa_parts[6] + ", expected " + serial

@step('last query should have (\S+) (.+)')
def check_last_query(step, item, value):
    assert world.last_query_result is not None
    assert item in world.last_query_result.__dict__
    lq_val = world.last_query_result.__dict__[item]
    assert str(value) == str(lq_val),\
           "Got: " + str(lq_val) + ", expected: " + str(value)
