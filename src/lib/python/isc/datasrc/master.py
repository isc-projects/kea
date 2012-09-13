# Copyright (C) 2010  Internet Systems Consortium.
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

import sys, re, string
import time
import os
#########################################################################
# define exceptions
#########################################################################
class MasterFileError(Exception):
    pass

#########################################################################
# pop: remove the first word from a line
# input: a line
# returns: first word, rest of the line
#########################################################################
def pop(line):
    list = line.split()
    first, rest = '', ''
    if len(list) != 0:
        first = list[0]
    if len(list) > 1:
        rest = ' '.join(list[1:])
    return first, rest

#########################################################################
# cleanup: removes excess content from zone file data, including comments
# and extra whitespace
# input:
#   line of text
# returns:
#   the same line, with comments removed, leading and trailing
#   whitespace removed, and all other whitespace compressed to
#   single spaces
#########################################################################
decomment = re.compile('^\s*((?:[^;"]|"[^"]*")*)\s*(?:|;.*)$')
# Regular expression explained:
# First, ignore any whitespace at the start. Then take the content,
# each bit is either a harmless character (no ; nor ") or a string -
# sequence between " " not containing double quotes. Then there may
# be a comment at the end.
def cleanup(s):
    global decomment
    s = s.strip().expandtabs()
    s = decomment.search(s).group(1)
    return ' '.join(s.split())

#########################################################################
# istype: check whether a string is a known RR type.
# returns: boolean
#########################################################################
rrtypes = set(['a', 'aaaa', 'afsdb', 'apl', 'cert', 'cname', 'dhcid',
               'dlv', 'dname', 'dnskey', 'ds', 'gpos', 'hinfo', 'hip',
               'ipseckey', 'isdn', 'key', 'kx', 'loc', 'mb', 'md',
               'mf', 'mg', 'minfo', 'mr', 'mx', 'naptr', 'ns', 'nsap',
               'nsap-ptr', 'nsec', 'nsec3', 'nsec3param', 'null',
               'nxt', 'opt', 'ptr', 'px', 'rp', 'rrsig', 'rt', 'sig',
               'soa', 'spf', 'srv', 'sshfp', 'tkey', 'tsig', 'txt',
               'x25', 'wks'])
def istype(s):
    global rrtypes
    if s.lower() in rrtypes:
        return True
    else:
        return False

#########################################################################
# isclass: check whether a string is a known RR class.  (only 'IN' is
# supported, but the others must still be recognizable.)
# returns: boolean
#########################################################################
rrclasses = set(['in', 'ch', 'chaos', 'hs', 'hesiod'])
def isclass(s):
    global rrclasses
    if s.lower() in rrclasses:
        return True
    else:
        return False

#########################################################################
# isname: check whether a string is a valid DNS name.
# returns: boolean
#########################################################################
name_regex = re.compile('[-\w\$\d\/*]+(?:\.[-\w\$\d\/]+)*\.?')
def isname(s):
    global name_regex
    if s == '.' or name_regex.match(s):
        return True
    else:
        return False

#########################################################################
# isttl: check whether a string is a valid TTL specifier.
# returns: boolean
#########################################################################
ttl_regex = re.compile('([0-9]+[wdhms]?)+$', re.I)
def isttl(s):
    global ttl_regex
    if ttl_regex.match(s):
        return True
    else:
        return False

#########################################################################
# parse_ttl: convert a TTL field into an integer TTL value
# (multiplying as needed for minutes, hours, etc.)
# input:
#   string
# returns:
#   int
# throws:
#   MasterFileError
#########################################################################
def parse_ttl(s):
    sum = 0
    if not isttl(s):
        raise MasterFileError('Invalid TTL: ' + s)
    for ttl_expr in re.findall('\d+[wdhms]?', s, re.I):
        if ttl_expr.isdigit():
            ttl = int(ttl_expr)
            sum += ttl
            continue
        ttl = int(ttl_expr[:-1])
        suffix = ttl_expr[-1].lower()
        if suffix == 'w':
            ttl *= 604800
        elif suffix == 'd':
            ttl *= 86400
        elif suffix == 'h':
            ttl *= 3600
        elif suffix == 'm':
            ttl *= 60
        sum += ttl
    return str(sum)

#########################################################################
# records: generator function to return complete RRs from the zone file,
# combining lines when necessary because of parentheses
# input:
#   descriptor for a zone master file (returned from openzone)
# yields:
#   complete RR
#########################################################################
def records(input):
    record = []
    complete = True
    paren = 0
    size = 0
    for line in input:
        size += len(line)
        list = cleanup(line).split()
        for word in list:
            if paren == 0:
                left, p, right = word.partition('(')
                if p == '(':
                    if left: record.append(left)
                    if right: record.append(right)
                    paren += 1
                else:
                    record.append(word)
            else:
                left, p, right = word.partition(')')
                if p == ')':
                    if left: record.append(left)
                    if right: record.append(right)
                    paren -= 1
                else:
                    record.append(word)

        if paren == 1 or not record:
            continue
        
        ret = ' '.join(record)
        record = []
        oldsize = size
        size = 0
        yield ret, oldsize

#########################################################################
# define the MasterFile class for reading zone master files
#########################################################################
class MasterFile:
    __rrclass = 'IN'
    __maxttl = 0x7fffffff
    __ttl = ''
    __lastttl = ''
    __zonefile = ''
    __name = ''
    __file_level = 0
    __file_type = ""
    __init_time = time.time()
    __records_num = 0

    def __init__(self, filename, initial_origin = '', verbose = False):
        self.__initial_origin = initial_origin
        self.__origin = initial_origin
        self.__datafile = filename

        try:
            self.__zonefile = open(filename, 'r')
        except:
            raise MasterFileError("Could not open " + filename)
        self.__filesize = os.fstat(self.__zonefile.fileno()).st_size

        self.__cur = 0
        self.__numback = 0
        self.__verbose = verbose
        try:
            self.__zonefile = open(filename, 'r')
        except:
            raise MasterFileError("Could not open " + filename)

    def __status(self):
        interval = time.time() - MasterFile.__init_time
        if self.__filesize == 0:
            percent = 100
        else:
            percent = (self.__cur * 100)/self.__filesize

        sys.stdout.write("\r" + (80 * " "))
        sys.stdout.write("\r%d RR(s) loaded in %.2f second(s) (%.2f%% of %s%s)"\
                % (MasterFile.__records_num, interval, percent, MasterFile.__file_type, self.__datafile))

    def __del__(self):
        if self.__zonefile:
            self.__zonefile.close()
    ########################################################################
    # check if the zonename is relative
    # no then return
    # yes , sets the relative domain name to the stated name
    #######################################################################
    def __statedname(self, name, record):
        if name[-1] != '.':
            if not self.__origin:
                raise MasterFileError("Cannot parse RR, No $ORIGIN: " + record)
            elif self.__origin == '.':
                name += '.'
            else:
                name += '.' + self.__origin
        return name
    #####################################################################
    # handle $ORIGIN, $TTL and $GENERATE directives
    # (currently only $ORIGIN and $TTL are implemented)
    # input:
    #   a line from a zone file
    # returns:
    #   a boolean indicating whether a directive was found
    # throws:
    #   MasterFileError
    #########################################################################
    def __directive(self, s):
        first, more = pop(s)
        second, more = pop(more)
        if re.match('\$origin', first, re.I):
            if not second or not isname(second):
                raise MasterFileError('Invalid $ORIGIN')
            if more:
                raise MasterFileError('Invalid $ORIGIN')
            if second[-1] == '.':
                self.__origin = second
            elif not self.__origin:
                raise MasterFileError("$ORIGIN is not absolute in record: %s" % s)
            elif self.__origin != '.':
                self.__origin = second + '.' + self.__origin
            else:
                self.__origin = second + '.'
            return True
        elif re.match('\$ttl', first, re.I):
            if not second or not isttl(second):
                raise MasterFileError('Invalid TTL: "' + second + '"')
            if more:
                raise MasterFileError('Invalid $TTL statement')
            MasterFile.__ttl = parse_ttl(second)
            if int(MasterFile.__ttl) > self.__maxttl:
                raise MasterFileError('TTL too high: ' + second)
            return True
        elif re.match('\$generate', first, re.I):
            raise MasterFileError('$GENERATE not yet implemented')
        else:
            return False

    #########################################################################
    # handle $INCLUDE directives
    # input:
    #   a line from a zone file
    # returns:
    #   the parsed output of the included file, if any, or an empty array
    # throws:
    #   MasterFileError
    #########################################################################
    __include_syntax1 = re.compile('\s+(\S+)(?:\s+(\S+))?$', re.I)
    __include_syntax2 = re.compile('\s+"([^"]+)"(?:\s+(\S+))?$', re.I)
    __include_syntax3 = re.compile("\s+'([^']+)'(?:\s+(\S+))?$", re.I)
    def __include(self, s):
        if not s.lower().startswith('$include'):
            return "", ""
        s = s[len('$include'):]
        m = self.__include_syntax1.match(s)
        if not m:
            m = self.__include_syntax2.match(s)
        if not m:
            m = self.__include_syntax3.match(s)
        if not m:
            raise MasterFileError('Invalid $include format')
        file = m.group(1)
        if m.group(2):
            if not isname(m.group(2)):
                raise MasterFileError('Invalid $include format (invalid origin)')
            origin = self.__statedname(m.group(2), s)
        else:
            origin = self.__origin
        return file, origin

    #########################################################################
    # try parsing an RR on the assumption that the type is specified in
    # field 4, and name, ttl and class are in fields 1-3
    # are all specified, with type in field 4
    # input:
    #   a record to parse, and the most recent name found in prior records
    # returns:
    #   empty list if parse failed, else name, ttl, class, type, rdata
    #########################################################################
    def __four(self, record, curname):
        ret = ''
        list = record.split()
        if len(list) <= 4:
            return ret
        if istype(list[3]):
            if isclass(list[2]) and isttl(list[1]) and isname(list[0]):
                name, ttl, rrclass, rrtype = list[0:4]
                ttl = parse_ttl(ttl)
                MasterFile.__lastttl = ttl or MasterFile.__lastttl
                rdata = ' '.join(list[4:])
                ret = name, ttl, rrclass, rrtype, rdata
            elif isclass(list[1]) and isttl(list[2]) and isname(list[0]):
                name, rrclass, ttl, rrtype = list[0:4]
                ttl = parse_ttl(ttl)
                MasterFile.__lastttl = ttl or MasterFile.__lastttl
                rdata = ' '.join(list[4:])
                ret = name, ttl, rrclass, rrtype, rdata
        return ret

    #########################################################################
    # try parsing an RR on the assumption that the type is specified
    # in field 3, and one of name, ttl, or class has been omitted
    # input:
    #   a record to parse, and the most recent name found in prior records
    # returns:
    #   empty list if parse failed, else name, ttl, class, type, rdata
    #########################################################################
    def __getttl(self):
        return MasterFile.__ttl or MasterFile.__lastttl

    def __three(self, record, curname):
        ret = ''
        list = record.split()
        if len(list) <= 3:
            return ret
        if istype(list[2]) and not istype(list[1]):
            if isclass(list[1]) and not isttl(list[0]) and isname(list[0]):
                rrclass = list[1]
                ttl = self.__getttl()
                name = list[0]
            elif not isclass(list[1]) and isttl(list[1]) and not isclass(list[0]) and isname(list[0]):
                rrclass = self.__rrclass
                ttl = parse_ttl(list[1])
                MasterFile.__lastttl = ttl or MasterFile.__lastttl
                name = list[0]
            elif curname and isclass(list[1]) and isttl(list[0]):
                rrclass = list[1]
                ttl = parse_ttl(list[0])
                MasterFile.__lastttl = ttl or MasterFile.__lastttl
                name = curname
            elif curname and isttl(list[1]) and isclass(list[0]):
                rrclass = list[0]
                ttl = parse_ttl(list[1])
                MasterFile.__lastttl = ttl or MasterFile.__lastttl
                name = curname
            else:
                return ret
            rrtype = list[2]
            rdata = ' '.join(list[3:])
            ret = name, ttl, rrclass, rrtype, rdata
        return ret

    #########################################################################
    # try parsing an RR on the assumption that the type is specified in
    # field 2, and field 1 is either name or ttl
    # input:
    #   a record to parse, and the most recent name found in prior records
    # returns:
    #   empty list if parse failed, else name, ttl, class, type, rdata
    # throws:
    #   MasterFileError
    #########################################################################
    def __two(self, record, curname):
        ret = ''
        list = record.split()
        if len(list) <= 2:
            return ret
        if istype(list[1]):
            rrclass = self.__rrclass
            rrtype = list[1]
            if list[0].lower() == 'rrsig':
                name = curname
                ttl = self.__getttl()
                rrtype = list[0]
                rdata = ' '.join(list[1:])
            elif isttl(list[0]):
                ttl = parse_ttl(list[0])
                name = curname
                rdata = ' '.join(list[2:])
            elif isclass(list[0]):
                ttl = self.__getttl()
                name = curname
                rdata = ' '.join(list[2:])
            elif isname(list[0]):
                name = list[0]
                ttl = self.__getttl()
                rdata = ' '.join(list[2:])
            else:
                raise MasterFileError("Cannot parse RR: " + record)

            ret = name, ttl, rrclass, rrtype, rdata
        return ret

    ########################################################################
    #close verbose
    ######################################################################
    def closeverbose(self):
        self.__status()

    #########################################################################
    # zonedata: generator function to parse a zone master file and return
    # each RR as a (name, ttl, type, class, rdata) tuple
    #########################################################################
    def zonedata(self):
        name = ''
        last_status = 0.0
        flag = 1

        for record, size in records(self.__zonefile):
            if self.__verbose:
                now = time.time()
                if flag == 1:
                    self.__status()
                    flag = 0
                if now - last_status >= 1.0:
                    self.__status()
                    last_status = now

            self.__cur += size
            if self.__directive(record):
                continue

            incl, suborigin = self.__include(record)
            if incl:
                if self.__filesize == 0:
                    percent = 100
                else:
                    percent = (self.__cur * 100)/self.__filesize
                if self.__verbose:
                    sys.stdout.write("\r" + (80 * " "))
                    sys.stdout.write("\rIncluding \"%s\" from \"%s\"\n" % (incl, self.__datafile))
                MasterFile.__file_level += 1
                MasterFile.__file_type = "included "
                sub = MasterFile(incl, suborigin, self.__verbose)

                for rrname, ttl, rrclass, rrtype, rdata in sub.zonedata():
                    yield (rrname, ttl, rrclass, rrtype, rdata)
                if self.__verbose:
                    sub.closeverbose()
                MasterFile.__file_level -= 1
                if MasterFile.__file_level == 0:
                    MasterFile.__file_type = ""
                del sub
                continue

            # replace @ with origin
            rl = record.split()
            if rl[0] == '@':
                rl[0] = self.__origin
                if not self.__origin:
                    raise MasterFileError("Cannot parse RR, No $ORIGIN: " + record)
                record = ' '.join(rl)

            result = self.__four(record, name)

            if not result:
                result = self.__three(record, name)

            if not result:
                result = self.__two(record, name)

            if not result:
                first, rdata = pop(record)
                if istype(first):
                    result = name, self.__getttl(), self.__rrclass, first, rdata

            if not result:
                raise MasterFileError("Cannot parse RR: " + record)

            name, ttl, rrclass, rrtype, rdata = result
            name = self.__statedname(name, record)

            if rrclass.lower() != 'in':
                raise MasterFileError("CH and HS zones not supported")

            # add origin to rdata containing names, if necessary
            if rrtype.lower() in ('cname', 'dname', 'ns', 'ptr'):
                if not isname(rdata):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                rdata = self.__statedname(rdata, record)

            if rrtype.lower() == 'soa':
                soa = rdata.split()
                if len(soa) < 2 or not isname(soa[0]) or not isname(soa[1]):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                soa[0] = self.__statedname(soa[0], record)
                soa[1] = self.__statedname(soa[1], record)
                if not MasterFile.__ttl and not ttl:
                    MasterFile.__ttl = MasterFile.__ttl or parse_ttl(soa[-1])
                    ttl = MasterFile.__ttl

                for index in range(3, len(soa)):
                    if isttl(soa[index]):
                        soa[index] = parse_ttl(soa[index])
                    else :
                        raise MasterFileError("No TTL specified; in soa record!")
                rdata = ' '.join(soa)

            if not ttl:
                raise MasterFileError("No TTL specified; zone rejected")

            if rrtype.lower() == 'mx':
                mx = rdata.split()
                if len(mx) != 2 or not isname(mx[1]):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                if mx[1][-1] != '.':
                    mx[1] += '.' + self.__origin
                    rdata = ' '.join(mx)
            MasterFile.__records_num += 1
            yield (name, ttl, rrclass, rrtype, rdata)

    #########################################################################
    # zonename: scans zone data for an SOA record, returns its name, restores
    # the zone file to its prior state
    #########################################################################
    def zonename(self):
        if self.__name:
            return self.__name
        old_origin = self.__origin
        self.__origin = self.__initial_origin
        cur_value = self.__cur
        old_location = self.__zonefile.tell()
        old_verbose = self.__verbose
        self.__verbose = False
        self.__zonefile.seek(0)

        for name, ttl, rrclass, rrtype, rdata in self.zonedata():
            if rrtype.lower() == 'soa':
                break
        self.__zonefile.seek(old_location)
        self.__origin = old_origin
        self.__cur = cur_value
        if rrtype.lower() != 'soa':
            raise MasterFileError("No SOA found")
        self.__name = name
        self.__verbose = old_verbose
        return name

    #########################################################################
    # reset: reset the state of the master file
    #########################################################################
    def reset(self):
        self.__zonefile.seek(0)
        self.__origin = self.__initial_origin
        MasterFile.__ttl = ''
        MasterFile.__lastttl = ''

#########################################################################
# main: used for testing; parse a zone file and print out each record
# broken up into separate name, ttl, class, type, and rdata files
#########################################################################
def main():
    try:
        file = sys.argv[1]
    except:
        file = 'testfile'
    master = MasterFile(file, '.')
    print ('zone name: ' + master.zonename())
    print ('---------------------')
    for name, ttl, rrclass, rrtype, rdata in master.zonedata():
        print ('name: ' + name)
        print ('ttl: ' + ttl)
        print ('rrclass: ' + rrclass)
        print ('rrtype: ' + rrtype)
        print ('rdata: ' + rdata)
        print ('---------------------')
    del master

if __name__ == "__main__":
    main()
