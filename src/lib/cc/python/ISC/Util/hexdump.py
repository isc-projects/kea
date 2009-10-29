import sys

_FILTER=''.join([(len(repr(chr(x)))==3) and chr(x) or '.' for x in range(256)])

def hexdump(src, length=16):
    result=[]
    for i in xrange(0, len(src), length):
        s = src[i:i+length]
        hexa = ' '.join(["%02X" % ord(x) for x in s])
        printable = s.translate(_FILTER)
        item = "%08X   %-*s   %s\n" % (i, length * 3, hexa, printable)
        result.append(item[0:34] + ' ' + item[34:])
    print(''.join(result))
