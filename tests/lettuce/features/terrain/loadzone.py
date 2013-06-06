# Copyright (C) 2013  Internet Systems Consortium.
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

from lettuce import *
import subprocess
import tempfile

def run_loadzone(zone, zone_file, db_file):
    """Run b10-loadzone.

    It currently only works for an SQLite3-based data source, and takes
    its DB file as a parameter.

    Parameters:
    zone (str): the zone name
    zone_file (str): master zone file for the zone; can be None to make an
                     empty zone.
    db_file (str): SQLite3 DB file to load the zone into

    """
    sqlite_datasrc_cfg = '{"database_file": "' + db_file + '"}'
    if zone_file is not None:
        args = ['b10-loadzone', '-c', sqlite_datasrc_cfg, zone, zone_file]
    else:
        args = ['b10-loadzone', '-c', sqlite_datasrc_cfg, '-e', zone]
    loadzone = subprocess.Popen(args, 1, None, None,
                                subprocess.PIPE, subprocess.PIPE)
    (stdout, stderr) = loadzone.communicate()
    result = loadzone.returncode
    world.last_loadzone_stdout = stdout
    world.last_loadzone_stderr = stderr
    assert result == 0, "loadzone exit code: " + str(result) +\
                        "\nstdout:\n" + str(stdout) +\
                        "stderr:\n" + str(stderr)

@step('load zone (\S+) to DB file (\S+) from (\S+)')
def load_zone_to_dbfile(step, zone, db_file, zone_file):
    """Load a zone into a data source from a zone file.

    It currently only works for an SQLite3-based data source.  Its
    DB file name should be specified.

    Step definition:
    load zone <zone_name> to DB file <db_file> from <zone_file>

    """
    run_loadzone(zone, zone_file, db_file)

@step('make empty zone (\S+) in DB file (\S+)')
def make_empty_zone_to_dbfile(step, zone, db_file):
    """Make an empty zone into a data source.

    If a non-empty zone already exists in the data source, it will be emptied;
    otherwise, a new empty zone will be created.

    It currently only works for an SQLite3-based data source.  Its
    DB file name should be specified.

    Step definition:
    make empty zone <zone_name> to DB file <db_file>

    """
    run_loadzone(zone, None, db_file)

@step('load (\d+) records for zone (\S+) to DB file (\S+)')
def load_zone_rr_to_dbfile(step, num_records, zone, db_file):
    """Load a zone with a specified number of RRs into a data source.

    It currently only works for an SQLite3-based data source.  Its
    DB file name should be specified.

    It creates the content of the zone dynamically so the total number of
    RRs of the zone is the specified number, including mandatory SOA and NS.

    Step definition:
    load zone <zone_name> to DB file <db_file> from <zone_file>

    """
    num_records = int(num_records)
    assert num_records >= 2, 'zone must have at least 2 RRs: SOA and NS'
    num_records -= 2
    with tempfile.NamedTemporaryFile(mode='w', prefix='zone-file',
                                     dir='data/', delete=True) as f:
        filename = f.name
        f.write('$TTL 3600\n')
        f.write('$ORIGIN .\n')  # so it'll work whether or not zone ends with .
        f.write(zone + ' IN SOA . . 0 0 0 0 0\n')
        f.write(zone + ' IN NS 0.' + zone + '\n')
        count = 0
        while count < num_records:
            f.write(str(count) + '.' + zone + ' IN A 192.0.2.1\n')
            count += 1
        f.flush()
        run_loadzone(zone, f.name, db_file)
