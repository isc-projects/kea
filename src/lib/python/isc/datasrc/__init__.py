from isc.datasrc.master import *
from isc.datasrc.sqlite3_ds import *

for base in sys.path[:]:
    loglibdir = os.path.join(base, 'isc/datasrc/.libs')
    if os.path.exists(loglibdir):
        sys.path.insert(0, loglibdir)

from datasrc import *
