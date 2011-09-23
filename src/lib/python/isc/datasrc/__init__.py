from isc.datasrc.master import *
from isc.datasrc.sqlite3_ds import *

for base in sys.path[:]:
    datasrclibdir = os.path.join(base, 'isc/datasrc/.libs')
    if os.path.exists(datasrclibdir):
        sys.path.insert(0, datasrclibdir)

from datasrc import *
