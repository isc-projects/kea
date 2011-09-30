import sys
import os

# this setup is a temporary workaround to deal with the problem of
# having both 'normal' python modules and a wrapper module
# Once all programs use the new interface, we should remove the
# old, and the setup can be made similar to that of the log wrappers.
intree = False
for base in sys.path[:]:
    datasrc_libdir = os.path.join(base, 'isc/datasrc/.libs')
    if os.path.exists(datasrc_libdir):
        sys.path.insert(0, datasrc_libdir)
        intree = True

if intree:
    from datasrc import *
else:
    from isc.datasrc.datasrc import *
from isc.datasrc.sqlite3_ds import *
from isc.datasrc.master import *

