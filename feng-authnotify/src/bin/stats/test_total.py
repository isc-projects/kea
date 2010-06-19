import sys
sys.path.insert(0, '.')
from statsd import *

def test_total():
    stats = {
              'auth': {
                     'from1': {
                               'component':'auth',
                               'version':1,
                               'from':'from1',
                               'timestamp':20100125,
                               'stats': {
                                   'AUTH': {
                                       'counterid': 1,
                                       'requestv4': 2,
                                       'requestv6': 4,
                                   },
                                   'SYS': {
                                       'sockets': 8,
                                       'memory': 16,
                                   },
                                },
                     },
                     'from2': {
                               'component':'auth',
                               'version':1,
                               'from':'from1',
                               'timestamp':20100126,
                               'stats': {
                                   'AUTH': {
                                       'counterid': 256,
                                       'requestv4': 512,
                                       'requestv6': 1024,
                                   },
                                   'SYS': {
                                       'sockets': 2048,
                                       'memory': 4096,
                                   },
                                },
                     },
              },
            };
    t = {}
    for key in stats:
        t[key] = total(stats[key])
    print (stats)
    print (dicttoxml(stats))
    print (t)
    print (dicttoxml(t))


if __name__ == "__main__":
    test_total()
