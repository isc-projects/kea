from lettuce import *
import subprocess
import re

#
# define a class to easily access different parts
# We may consider using our full library for this, but for now
# simply store several parts of the response as text values in
# this structure
#
# this will set 'rcode' as the result code, we 'define' one additional
# rcode, "NO_ANSWER", if the dig process returned an error code itself
# we will extend as necessary
class QueryResult:
    def __init__(self, name, qtype = None, qclass = None, port = 47806):
        args = [ 'dig', '@localhost', '-p', str(port) ]
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
            rcode_re = re.compile("status: ([A-Z]+)")
            self.rcode = None
            for out in dig_process.stdout:
                rcode_match = rcode_re.search(out)
                if rcode_match is not None:
                    self.rcode = rcode_match.group(1)


@step(u'A query for ([\w.]+) should have rcode ([\w.]+)')
def query(step, query_name, rcode):
    query_result = QueryResult(query_name)
    assert query_result.rcode == rcode, "Got " + query_result.rcode

