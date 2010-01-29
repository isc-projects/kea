#!/usr/bin/python
#
# This program collects 'counters' from 'statistics' channel.
# It accepts one command: 'Boss' group 'shutdown'

import ISC.CC
import time
import select
import os

bossgroup = 'Boss'
myname = 'statsd'

def total(s):
    def totalsub(d,s):
        for k in s.keys():
            if (k == 'component' or k == 'version' 
                or k == 'timestamp' or k == 'from'):
                continue
            if (k in d):
                if (isinstance(s[k], dict)):
                    totalsub(d[k], s[k])
                else:
                    d[k] = s[k] + d[k]
            else:
                d[k] = s[k]

    if (len(s) == 0):
        return {}
    if (len(s) == 1):
        for k in s.keys():
            out = s[k]
        out['components'] = 1
        out['timestamp2'] = out['timestamp']
        del out['from']
        return out
    _time1 = 0
    _time2 = 0
    out = {}
    for i in s.values():
        if (_time1 == 0 or _time1 < i['timestamp']):
            _time1 = i['timestamp']
        if (_time2 == 0 or _time2 > i['timestamp']):
            _time2 = i['timestamp']
        totalsub(out, i)
    out['components'] = len(s)
    out['timestamp'] = _time1;
    out['timestamp2'] = _time2;
    return out

def dicttoxml(stats, level = 0):
    def dicttoxmlsub(s, level):
        output = ''
        spaces = ' ' * level
        for k in s.keys():
            if (isinstance(s[k], dict)):
                output += spaces + ('<%s>\n' %k) \
                  + dicttoxmlsub(s[k], level+1) \
                  + spaces + '</%s>\n' %k
            else:
                output += spaces + '<%s>%s</%s>\n' % (k, s[k], k)
        return output

    for k in stats.keys():
        space = ' ' * level
        output = space + '<component component="%s">\n' % k
        s = stats[k]
        if ('component' in s or 'components' in s):
            output += dicttoxmlsub(s, level+1)
        else:
            for l in s.keys():
                output +=  space + ' <from from="%s">\n' % l \
                          + dicttoxmlsub(s[l], level+2) \
                          + space + '  </from>\n'
        output += space + '</component>\n'
        return output

def dump_stats(statpath, statcount, stat, statraw):
    newfile = open(statpath + '.new', 'w')
    newfile.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    newfile.write('<!-- created at '+time.strftime('%Y%m%d %H%M%S')+' -->\n')
    newfile.write('<isc version="0.0">\n')
    newfile.write(' <bind10>\n')
    newfile.write('  <total>\n')
    newfile.write(dicttoxml(stat, 3))
    newfile.write('  </total>\n')
    newfile.write('  <each>\n')
    newfile.write(dicttoxml(statraw, 3))
    newfile.write('  </each>\n')
    newfile.write(' </bind10>\n')
    newfile.write('</isc>\n')
    newfile.close()
    loop = statcount
    while(loop > 0):
        old = statpath + '.%d' % loop
        loop -= 1
        new = statpath + '.%d' % loop
        if (os.access(new, os.F_OK)):
            os.rename(new, old)
    if (os.access(statpath, os.F_OK)):
        os.rename(statpath, new)
    os.rename(statpath + '.new', statpath)

def collector(statgroup,step,statpath,statcount):
    cc = ISC.CC.Session()
    print (cc.lname)
    cc.group_subscribe(statgroup)
    cc.group_subscribe(bossgroup, myname)
    wrote_time = -1
    last_wrote_time = -1
    last_recvd_time = -1
    stats = {}
    statstotal = {}
    while 1:
        wait = wrote_time + step - time.time()
        if wait <= 0 and last_recvd_time > wrote_time:
            dump_stats(statpath, statcount, statstotal, stats)
            last_wrote_time = wrote_time;
            wrote_time = time.time();
            wait = last_wrote_time + step - time.time()
            if wait < 0:
                wait = step
        r,w,e = select.select([cc._socket],[],[], wait)
        for sock in r:
            if sock == cc._socket:
                data,envelope = cc.group_recvmsg(False)
                if (envelope['group'] == bossgroup):
                    if ('shutdown' in data):
                        exit()
                if (envelope['group'] == statgroup):
                    # Check received data
                    if (not('component' in data and 'version' in data
                        and 'stats' in data)):
                        continue
                    component = data['component']
                    _from = envelope['from']
                    data['from'] = _from
                    if (not (component in stats)):
                        stats[component] = {}
                    (stats[component])[_from] = data;
                    statstotal[component] = total(stats[component])
                    last_recvd_time = time.time()

if __name__ == '__main__':
    collector('statistics', 10, '/tmp/stats', 100)
