from isc.datasrc.master import *
from isc.datasrc.sqlite3_ds import *

for base in sys.path[:]:
    datasrc_libdir = os.path.join(base, 'isc/datasrc/.libs')
    if os.path.exists(datasrc_libdir):
        sys.path.insert(0, datasrc_libdir)

from datasrc import *
