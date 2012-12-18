import sys
import os

# The datasource factory loader uses dlopen, as does python
# for its modules. Some dynamic linkers do not play nice if
# modules are not loaded with RTLD_GLOBAL, a symptom of which
# is that exceptions are not recognized by type. So to make
# sure this doesn't happen, we temporarily set RTLD_GLOBAL
# during the loading of the datasource wrappers.
import ctypes
flags = sys.getdlopenflags()
sys.setdlopenflags(flags | ctypes.RTLD_GLOBAL)

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

# revert to the default dlopen flags
sys.setdlopenflags(flags)

from isc.datasrc.sqlite3_ds import *

