"""Python tests"""

from dns import *

example = fromText("www.example.com")
upper = fromText("WWW.EXAMPLE.COM")
small = fromText("aaa.example.com")
large = fromText("zzz.example.com")

def f2b(name):
    """file to binary"""
    f = open(name)
    rl = f.readlines()
    f.close()
    b = bytearray()
    for l in rl:
        if l[0] == '#':
            continue
        if l[-1] == '\n':
            l = l[:-1]
        b += bytearray().fromhex(l)
    return bytes(b)

def nflc():
    """name Factory Lower Case"""
    namestr = ''
    labelcount = 0
    for ch in range(0, bind10_dns_noboost.MAX_WIRE + 1):
        if (ch < ord('A')) or (ch > ord('Z')):
            ss = '%03d' % ch
            namestr += '\\' + ss
            labelcount += 1
            if labelcount == bind10_dns_noboost.MAX_LABELLEN:
                namestr += '.'
                labelcount = 0
    return Name(namestr)

    

def testFT():
    """fromText"""
    nl = []
    nl.append(fromText("www.example.com"))
    nl.append(fromText("www.example.com."))  # with a trailing dot
    nl.append(fromText("wWw.exAmpLe.com"))   # mixed cases
    nl.append(fromText("\\wWw.exAmpLe.com")) # escape with a backslash
    # decimal representation for "WWW"
    nl.append(fromText("\\087\\087\\087.example.com"))

    for it in nl:
        if it != example:
            print('FAILED: (FT)',it,'!=',example)

    # root names
    if fromText("@") != fromText("."):
        print('FAILED: (FT) root name')

    # downcase
    n = fromText("Www.eXample.coM", True)
    if n.toWire() != example.toWire():
        print('FAILED: (FT) downcase')

    #
    # Tests for bogus names.  These should trigger an exception.
    #
    # empty label cannot be followed by another label
    try:
        n = fromText(".a")
        print('FAILED: (FT) .a')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'EmptyLabel':
            print('FAILED: (FT) .a')
    # duplicate period
    try:
        n = fromText("a..")
        print('FAILED: (FT) a..')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'EmptyLabel':
            print('FAILED: (FT) a..')
    # label length must be < 64
    try:
        n = fromText("012345678901234567890123456789" +
                     "012345678901234567890123456789" +
                     "0123")
        print('FAILED: (FT) TooLongLabel')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongLabel':
            print('FAILED: (FT) TooLongLabel')
    # now-unsupported bitstring labels
    try:
        n = fromText("\\[b11010000011101]")
        print('FAILED: (FT) BadLabelType')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadLabelType':
            print('FAILED: (FT) BadLabelType')
    # label length must be < 64
    try:
        n = fromText("012345678901234567890123456789" +
                     "012345678901234567890123456789" +
                     "012\\x")
        print('FAILED: (FT) TooLongLabel')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongLabel':
            print('FAILED: (FT) TooLongLabel')
    # but okay as long as resulting len < 64 even if the original string is
    # "too long"
    try:
        n = fromText("012345678901234567890123456789" +
                     "012345678901234567890123456789" +
                     "01\\x")
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FT) too long')
    # incomplete \DDD pattern (exactly 3 D's must appear)
    try:
        n = fromText("\\12abc")
        print('FAILED: (FT) BadEscape')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadEscape':
            print('FAILED: (FT) BadEscape')
    # \DDD must not exceed 255
    try:
        n = fromText("\\256")
        print('FAILED: (FT) BadEscape')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadEscape':
            print('FAILED: (FT) BadEscape')
    # Same tests for \111 as for \\x above
    try:
        n = fromText("012345678901234567890123456789" +
                     "012345678901234567890123456789" +
                     "012\\111")
        print('FAILED: (FT) TooLongLabel')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongLabel':
            print('FAILED: (FT) TooLongLabel')
    try:
        n = fromText("012345678901234567890123456789" +
                     "012345678901234567890123456789" +
                     "01\\111")
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FT) too long')
    # A domain name must be 255 octets or less
    try:
        n = fromText("123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "1234")
        print('FAILED: (FT) TooLongName')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongName':
            print('FAILED: (FT) TooLongName')
    # This is a possible longest name and should be accepted
    try:
        n = fromText("123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123456789.123456789.123456789.123456789.123456789." +
                     "123")
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FT) longest')
    # \DDD must consist of 3 digits
    try:
        n = fromText("\\12")
        print('FAILED: (FT) IncompleteName')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'IncompleteName':
            print('FAILED: (FT) IncompleteName')

    # a name with the max number of labels.  should be constructed without
    # an error, and its length should be the max value.
    try:
        n = fromText("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 40
                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 80
                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 120
                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 160
                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 200
                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9." + # 240
                     "0.1.2.3.4.5.6.")
        if bind10_dns_noboost.MAX_LABELS != n.getLabelCount():
            print('FAILED: (FT)',bind10_dns_noboost.MAX_LABELS,'!=',
                  n.getLabelCount())
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FT) maxlabels')

def testFW():
    """fromWire"""
    #
    # test cases derived from BIND9 tests.
    #
    # normal case with a compression pointer
    (n, _) = fromWire(f2b("testdata/name_fromWire1"), 25)
    if n != fromText("vix.com"):
        print('FAILED: (FW) n',n.toText(),'!=',"vix.com")
    # bogus label character (looks like a local compression pointer)
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire2"), 25)
        print('FAILED: (FW) BadLabelType')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadLabelType':
            print('FAILED: (FW) BadLabelType')
    # a bad compression pointer (too big)
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire3_1"), 25)
        print('FAILED: (FW) BadPointer')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadPointer':
            print('FAILED: (FW) BadPointer')
    # forward reference
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire3_2"), 25)
        print('FAILED: (FW) BadPointer')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadPointer':
            print('FAILED: (FW) BadPointer')
    # invalid name length
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire4"), 550)
        print('FAILED: (FW) TooLongName')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongName':
            print('FAILED: (FW) TooLongName')

    # skip test for from Wire5.  It's for disabling decompression, but our
    # implementation always allows it.

    # bad pointer (too big)
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire6"), 25)
        print('FAILED: (FW) BadPointer')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadPointer':
            print('FAILED: (FW) BadPointer')
    # input ends unexpectedly
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire7"), 25)
        print('FAILED: (FW) IncompleteName')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'IncompleteName':
            print('FAILED: (FW) IncompleteName')
    # many hops of compression but valid.  should succeed
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire8"), 383)
        if n != fromText("vix.com"):
            print('FAILED: (FW) vix.com')
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FW) vix.com')

    #
    # Additional test cases
    #

    # large names, a long but valid one, and invalid (too long) one.
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire9"), 0)
        if n.getLength() != bind10_dns_noboost.MAX_WIRE:
            print('FAILED: (FW) ong but valid')
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FW) ong but valid')
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire10"), 0)
        print('FAILED: (FW) TooLongName')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongName':
            print('FAILED: (FW) TooLongName')

    # A name with possible maximum number of labels; awkward but valid
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire11"), 0)
        if n.getLabelCount() != bind10_dns_noboost.MAX_LABELS:
            print('FAILED: (FW) maxlabels')
    except bind10_dns_noboost.DNSException:
        print('FAILED: (FW) maxlabels')

    # Wire format including an invalid label length
    try:
        (n, _) = fromWire(f2b("testdata/name_fromWire12"), 0)
        print('FAILED: (FW) BadLabelType')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'BadLabelType':
            print('FAILED: (FW) BadLabelType')

    # converting upper-case letters to down-case
    (n, _) = fromWire(f2b("testdata/name_fromWire1"), 25, True)
    if n.toText() != 'vix.com.':
        print('FAILED: (FW) ',n.toText(),'!=','vix.com.')
    if n.getLabelCount() != 3:
        print('FAILED: (FW) ',n.getLabelCount(),'!= 3')

def testTT():
    """toText"""
    # tests derived from BIND9
    n = fromText("a.b.c.d")
    if n.toText(True) != "a.b.c.d":
        print('FAILED: (TT)',n.toText(True),'!= a.b.c.d')
    n = fromText("a.\\\\[\\[.c.d")
    if n.toText(True) != "a.\\\\[[.c.d":
        print('FAILED: (TT)',n.toText(),'!= a.\\\\[[.c.d')
    n = fromText("a.b.C.d")
    if n.toText(False) != "a.b.C.d.":
        print('FAILED: (TT)',n.toText(False),'!= a.b.C.d.')

    # test omit_final_dot.  It's false by default.
    n = fromText("a.b.c.d.")
    if n.toText(True) != "a.b.c.d":
        print('FAILED: (TT)',n.toText(True),'!= a.b.c.d')
    n1 = fromText("a.b.")
    n2 = fromText("a.b.")
    if n1.toText(False) != n2.toText():
        print('FAILED: (TT)',n1.toText(False))

    # the root name is a special case: omit_final_dot will be ignored.
    n = fromText(".")
    if n.toText(True) != '.':
        print('FAILED: (TT)',n.toText(True),' != ,')

def testTW():
    """toWire"""
    data = "\x01\x61\x03\x76\x69\x78\x03\x63\x6f\x6d\x00"
    n = fromText("a.vix.com.")
    w = n.toWire()
    if len(w) != len(data):
        print('FAILED: (TW)',len(w),'!=',len(data))

def testF():
    """compare"""
    n1 = fromText("c.d")
    n2 = fromText("a.b.c.d")
    t = compare(n1, n2)
    if t[0] < 0:
        tt = (-1, t[1], t[2])
    elif t[0] > 0:
        tt = (1, t[1],t[2])
    else:
        tt = (0, t[1],t[2])
    if tt != (-1,3,'SUPERDOMAIN'):
        print('FAILED: (F) ', tt)

    n1 = fromText("a.b.c.d")
    n2 = fromText("c.d")
    t = compare(n1, n2)
    if t[0] < 0:
        tt = (-1, t[1], t[2])
    elif t[0] > 0:
        tt = (1, t[1],t[2])
    else:
        tt = (0, t[1],t[2])
    if tt != (1, 3, 'SUBDOMAIN'):
        print('FAILED: (F) ', tt)

    n1 = fromText("a.b.c.d")
    n2 = fromText("c.d.e.f")
    t = compare(n1, n2)
    if t[0] < 0:
        tt = (-1, t[1], t[2])
    elif t[0] > 0:
        tt = (1, t[1],t[2])
    else:
        tt = (0, t[1],t[2])
    if tt != (-1, 1, 'COMMONANCESTOR'):
        print('FAILED: (F) ', tt)

    n1 = fromText("a.b.c.d")
    n2 = fromText("f.g.c.d")
    t = compare(n1, n2)
    if t[0] < 0:
        tt = (-1, t[1], t[2])
    elif t[0] > 0:
        tt = (1, t[1],t[2])
    else:
        tt = (0, t[1],t[2])
    if tt != (-1, 3, 'COMMONANCESTOR'):
        print('FAILED: (F) ', tt)

    n1 = fromText("a.b.c.d")
    n2 = fromText("A.b.C.d.")
    t = compare(n1, n2)
    if t[0] < 0:
        tt = (-1, t[1], t[2])
    elif t[0] > 0:
        tt = (1, t[1],t[2])
    else:
        tt = (0, t[1],t[2])
    if tt != (0, 5, 'EQUAL'):
        print('FAILED: (F) ', tt)

def testE():
    """equal"""
    n = fromText("WWW.EXAMPLE.COM.")
    if not (example == n):
        print('FAILED: (E) 1')
    if not example.equals(n):
        print('FAILED: (E) 2')
    n = fromText("www.example.org.")
    if not (example != n):
        print('FAILED: (E) 3')
    if not example.nequals(n):
        print('FAILED: (E) 4')

def testIW():
    """isWildcard"""
    if not example.isWildcard() is False:
        print('FAILED: (IW)',example.toText())
    n = fromText("*.a.example.com")
    if not n.isWildcard() is True:
        print('FAILED: (IW)',n.toText())
    n = fromText("a.*.example.com")
    if not n.isWildcard() is False:
        print('FAILED: (IW)',n.toText())

def testC():
    """concatenate"""
    nc = fromText("aaa.www.example.com.")
    n = fromText("aaa")
    c = compare(nc, concatenate(n, example))
    if c[2] != 'EQUAL':
        print('FAILED: (C)',nc,'!=',n,'+',example)

    n = fromText(".")
    c = compare(example, concatenate(n, example))
    if c[2] != 'EQUAL':
        print('FAILED: (C)',example,'!=',n,'+',example)

    c = compare(example, concatenate(example, n))
    if c[2] != 'EQUAL':
        print('FAILED: (C)',example,'!=',example,'+',n)

    # concatenating two valid names would result in too long a name.
    n1 = fromText("123456789.123456789.123456789.123456789.123456789." +
                  "123456789.123456789.123456789.123456789.123456789." +
                  "123456789.123456789.123456789.123456789.123456789.")
    n2 = fromText("123456789.123456789.123456789.123456789.123456789." +
                  "123456789.123456789.123456789.123456789.123456789." +
                  "1234.");
    try:
        n = concatenate(n1, n2)
        print('FAILED: (C) toolong')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'TooLongName':
            print('FAILED: (C) TooLongName')

def testS():
    """split"""
    # normal cases with or without explicitly specifying the trailing dot.
    n = fromText("example.com.")
    ns = example.split(1, 2)
    if n != ns:
        print('FAILED: (S)',n,'!=',ns)
    ns = example.split(1, 3)
    if n != ns:
        print('FAILED: (S)',n,'!=',ns)
    # edge cases: only the first or last label.
    n = fromText("www.")
    ns = example.split(0, 1)
    if n != ns:
        print('FAILED: (S)',n,'!=',ns)
    n = fromText(".")
    ns = example.split(3, 1)
    if n != ns:
        print('FAILED: (S)',n,'!=',ns)
    # invalid range: an exception should be thrown.
    try:
        n = example.split(1, 0)
        print('FAILED: (S) OutOfRange')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'OutOfRange':
            print('FAILED: (S) OutOfRange')
    try:
        n = example.split(2, 3)
        print('FAILED: (S) OutOfRange')
    except bind10_dns_noboost.DNSException as e:
        if str(e) != 'OutOfRange':
            print('FAILED: (S) OutOfRange')

def testD():
    """downcase"""
    # usual case: all-upper case name to all-lower case
    upper.downcase()
    if upper.toWire() != example.toWire():
        print('FAILED: (D) upper')
    # confirm that non upper-case characters are intact
    n1 = nflc()
    n2 = nflc()
    n1.downcase()
    if n1.toWire() != n2.toWire():
        print('FAILED: (D) nameFactoryLowerCase')

def testLE():
    """leq"""
    if not (small <= large) or \
            not (small <= small) or \
            large <= small:
        print('FAILED: (LE)')

def testGE():
    """geq"""
    if not (large >= small) or \
            not (large >= large) or \
            small >= large:
        print('FAILED: (GE)')

def testLT():
    """lthan"""
    if not (small < large) or \
            small < small or \
            large < small:
        print('FAILED: (LT)')

def testGT():
    """gthan"""
    if not (large > small) or \
            large > large or \
            small > large:
        print('FAILED: (GT)')

def testWN():
    """writeName"""
    data = f2b("testdata/name_toWire1")
    mr = MessageRenderer()
    n = fromText("a.example.com.")
    mr.writeName(n)
    n = fromText("b.example.com.")
    mr.writeName(n)
    n = fromText("a.example.org.")
    mr.writeName(n)
    if mr.dump() != data:
        print('FAILED: (WN)',mr.dump(),'!=',data)

    # toWireInLargeBuffer
    pad = b'\x00' * 0x3fff
    data = f2b("testdata/name_toWire2")
    mr = MessageRenderer()
    mr.writeData(pad)
    n = fromText("a.example.com.")
    mr.writeName(n)
    n = fromText("a.example.com.")
    mr.writeName(n)
    n = fromText("b.example.com.")
    mr.writeName(n)
    d = mr.dump()[0x3fff :]
    if d != data:
        print('FAILED: (WN) LB',d,'!=',data)

    # toWireWithUncompressed
    data = f2b("testdata/name_toWire3")
    mr = MessageRenderer()
    n = fromText("a.example.com.")
    mr.writeName(n)
    n = fromText("b.example.com.")
    mr.writeName(n, False)
    n = fromText("b.example.com.")
    mr.writeName(n)
    if mr.dump() != data:
        print('FAILED: (WN) UC',mr.dump(),'!=',data)

    # toWireCaseCompress
    data = f2b("testdata/name_toWire1")
    mr = MessageRenderer()
    n = fromText("a.example.com.")
    mr.writeName(n)
    # this should match the first name in terms of compression:
    n = fromText("b.exAmple.CoM.")
    mr.writeName(n)
    n = fromText("a.example.org.")
    mr.writeName(n)
    if mr.dump() != data:
        print('FAILED: (WN) CC',mr.dump(),'!=',data)

def testAll():
    """All"""
    testFT()
    testFW()
    testTT()
    testTW()
    testF()
    testE()
    testIW()
    testC()
    testS()
    testD()
    testLE()
    testGE()
    testLT()
    testGT()
    testWN()

testAll()
print("PASSED")
