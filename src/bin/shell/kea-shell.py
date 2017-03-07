#!/usr/bin/python

# First, let's import the right kea_connector.
# We have two versions: one for python 2.x and another for python 3.x.
# Sadly, there's no unified way to handle http connections. The recommended
# way is to use Requests (http://docs.python-requests.org/en/master/), but
# that's a stand alone package that requires separate installation. One of
# the design requirements was to not require any additional packages, so
# the code uses standard libraries available in python. Hence two versions.
import sys
import signal
import argparse

if (sys.version_info[0] == 2):
    # This is Python 2.x
    import kea_connector2 as kea_connector
else:
    if (sys.version_info[0] == 3):
        # This is Python 3.x
        import kea_connector3 as kea_connector
    else:
        # This is... have no idea what it is.
        raise SystemExit("Unknown python version:" + str(sys.version_info[0]))

from kea_conn import CARequest, CAResponse

# Second step: Need to parse command line parameters. We will use argparse for
# that purpose. It does great job with having default values, taking care of
# the help and sanity checking input parameters.

parser = argparse.ArgumentParser(description='Connects to Kea Control Agent.')
parser.add_argument('--host', type=str, nargs=1, default='127.0.0.1',
                    help='hostname of the CA to connect to')
parser.add_argument('--port', type=int, nargs=1, default=8000,
                    help='TCP port of the CA to connect to')
parser.add_argument('--timeout', type=int, nargs=1, default='10',
                    help='Timeout (in seconds) when attempting to connect to CA')
parser.add_argument('command', type=str, nargs="?", default='list-commands',
                    help='command to be executed. If not specified, "list-commands" is used')
cmd_args = parser.parse_args()

# Ok, now time to put the parameters parsed into the structure to be used by the
# connection.
params = CARequest()
params.command = cmd_args.command
params.http_host = cmd_args.host[0]
params.http_port = cmd_args.port[0]
params.timeout = cmd_args.timeout

params.generateBody()
params.generateHeaders()

conn = kea_connector.KeaConnector()

def timeout_handler(signum, frame):
    print ("Connection timeout")
    sys.exit(1)

# Load command processor
# @todo - command specific processing will be added as part of future work
# (either #5138 or #5139, whichever is implemented first)

# Read parameters from stdin (they're optional for some commands)
for line in sys.stdin:
    params.params += line

# Set the timeout timer. If the connection takes too long,
# it will send a signal to us.
signal.signal(signal.SIGALRM, timeout_handler)
signal.alarm(params.timeout)

# Ok, everything is ready. Let's send the command and get a response.
try:
    resp = conn.sendCA(params)
except Exception as e:
    print("Failed to run: " + str(e))
    sys.exit(1)

resp.printResp()

sys.exit(0)
