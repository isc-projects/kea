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
decomment = re.compile('\s*(?:;.*)+')
def cleanup(s):
    global decomment
    s = s.strip().expandtabs()
    s = decomment.sub('', s)
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
ttl_regex = re.compile('[0-9]+[wdhms]?', re.I)
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
    m = re.match('([0-9]+)(.*)', s)
    if not m:
        raise MasterFileError('Invalid TTL: ' + s)
    ttl, suffix = int(m.group(1)), m.group(2)
    if suffix.lower() == 'w':
        ttl *= 604800
    elif suffix.lower() == 'd':
        ttl *= 86400
    elif suffix.lower() == 'h':
        ttl *= 3600
    elif suffix.lower() == 'm':
        ttl *= 60
    return ttl

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
    for line in input:
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
        yield ret

#########################################################################
# define the MasterFile class for reading zone master files
#########################################################################
class MasterFile:
    __defclass = 'IN'
    __maxttl = 0x7fffffff
    __defttl = ''
    __zonefile = ''
    __name = ''

    def __init__(self, filename, initial_origin = ''):
        if initial_origin == '.':
            initial_origin = ''
        self.__initial_origin = initial_origin
        self.__origin = initial_origin
        try:
            self.__zonefile = open(filename, 'r')
        except:
            raise MasterFileError("Could not open " + filename)

    def __del__(self):
        if self.__zonefile:
            self.__zonefile.close()

    #########################################################################
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
            if second == '.':
                self.__origin = ''
            elif second[-1] == '.':
                self.__origin = second
            else:
                self.__origin = second + '.' + self.__origin
            return True
        elif re.match('\$ttl', first, re.I):
            if not second or not isttl(second):
                raise MasterFileError('Invalid TTL: "' + second + '"')
            if more:
                raise MasterFileError('Invalid $TTL statement')
            self.__defttl = parse_ttl(second)
            if self.__defttl > self.__maxttl:
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
    __filename = re.compile('[\"\']*([^\'\"]+)[\"\']*')
    def __include(self, s):
        first, rest = pop(s)
        if re.match('\$include', first, re.I):
            m = self.__filename.match(rest)
            if m:
                file = m.group(1)
                return file

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
    def __three(self, record, curname):
        ret = ''
        list = record.split()
        if len(list) <= 3:
            return ret
        if istype(list[2]) and not istype(list[1]):
            if isclass(list[1]) and not isttl(list[0]) and isname(list[0]):
                rrclass = list[1]
                ttl = self.__defttl
                name = list[0]
            elif not isclass(list[1]) and isttl(list[1]) and isname(list[0]):
                rrclass = self.__defclass
                ttl = parse_ttl(list[1])
                name = list[0]
            elif curname and isclass(list[1]) and isttl(list[0]):
                rrclass = self.__defclass
                ttl = parse_ttl(list[0])
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
            rrclass = self.__defclass
            rrtype = list[1]
            if list[0].lower() == 'rrsig':
                name = curname
                ttl = self.__defttl
                rrtype = list[0]
                rdata = ' '.join(list[1:])
            elif isttl(list[0]):
                ttl = parse_ttl(list[0])
                name = curname
                rdata = ' '.join(list[2:])
            elif isname(list[0]):
                name = list[0]
                ttl = self.__defttl
                rdata = ' '.join(list[2:])
            else:
                raise MasterFileError("Cannot parse RR: " + record)

            ret = name, ttl, rrclass, rrtype, rdata

        return ret

    #########################################################################
    # zonedata: generator function to parse a zone master file and return
    # each RR as a (name, ttl, type, class, rdata) tuple
    #########################################################################
    def zonedata(self):
        name = ''

        for record in records(self.__zonefile):
            if self.__directive(record):
                continue

            incl = self.__include(record)
            if incl:
                sub = MasterFile(incl, self.__origin)
                for name, ttl, rrclass, rrtype, rdata in sub.zonedata():
                    yield (name, ttl, rrclass, rrtype, rdata)
                del sub
                continue

            # replace @ with origin
            rl = record.split()
            if rl[0] == '@':
                rl[0] = self.__origin
                if not self.__origin:
                    rl[0] = '.'
                record = ' '.join(rl)

            result = self.__four(record, name)

            if not result:
                result = self.__three(record, name)

            if not result:
                result = self.__two(record, name)

            if not result:
                first, rdata = pop(record)
                if istype(first):
                    result = name, self.__defttl, self.__defclass, first, rdata

            if not result:
                raise MasterFileError("Cannot parse RR: " + record)

            name, ttl, rrclass, rrtype, rdata = result
            if name[-1] != '.':
                name += '.' + self.__origin

            if rrclass.lower() != 'in':
                raise MasterFileError("CH and HS zones not supported")

            if not ttl:
                raise MasterFileError("No TTL specified; zone rejected")

            # add origin to rdata containing names, if necessary
            if rrtype.lower() in ('cname', 'dname', 'ns', 'ptr'):
                if not isname(rdata):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                if rdata[-1] != '.':
                    rdata += '.' + self.__origin
            if rrtype.lower() == 'soa':
                soa = rdata.split()
                if len(soa) < 2 or not isname(soa[0]) or not isname(soa[1]):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                if soa[0][-1] != '.':
                    soa[0] += '.' + self.__origin
                if soa[1][-1] != '.':
                    soa[1] += '.' + self.__origin
                rdata = ' '.join(soa)
            if rrtype.lower() == 'mx':
                mx = rdata.split()
                if len(mx) != 2 or not isname(mx[1]):
                    raise MasterFileError("Invalid " + rrtype + ": " + rdata)
                if mx[1][-1] != '.':
                    mx[1] += '.' + self.__origin
                    rdata = ' '.join(mx)

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
        old_location = self.__zonefile.tell()
        self.__zonefile.seek(0)
        for name, ttl, rrclass, rrtype, rdata in self.zonedata():
            if rrtype.lower() == 'soa':
                break
        self.__zonefile.seek(old_location)
        self.__origin = old_origin
        if rrtype.lower() != 'soa':
            raise MasterFileError("No SOA found")
        self.__name = name
        return name

    #########################################################################
    # reset: reset the state of the master file
    #########################################################################
    def reset(self):
        self.__zonefile.seek(0)
        self.__origin = self.__initial_origin
        self.__defttl = ''

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
        print ('ttl: ' + str(ttl))
        print ('rrclass: ' + rrclass)
        print ('rrtype: ' + rrtype)
        print ('rdata: ' + rdata)
        print ('---------------------')
    del master

if __name__ == "__main__":
    main()
