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

'''
This file implements user management program. The user name and 
its password is appended in csv file.
'''
import random
from hashlib import sha1
import csv
import getpass
import getopt
import sys

VERSION_NUMBER = 'bind10'
DEFAULT_FILE = 'passwd.csv'

def gen_password_hash(password):
    salt = "".join(chr(random.randint(33, 127)) for x in range(64))
    saltedpwd = sha1((password + salt).encode()).hexdigest()
    return salt, saltedpwd

def username_exist(name, filename):
    # The file may doesn't exist.
    exist = False
    csvfile = None
    try:
        csvfile = open(filename)        
        reader = csv.reader(csvfile)
        for row in reader:
            if name == row[0]:
                exist = True               
                break
    except Exception:
        pass
            
    if csvfile:    
        csvfile.close()
    return exist

def save_userinfo(username, pw, salt, filename):
    csvfile = open(filename, 'a')
    writer = csv.writer(csvfile)
    writer.writerow([username, pw, salt])
    csvfile.close()
    print("add user success!")

def usage():
    print('''Usage: usermgr [options]
           -h, --help \t Show this help message and exit
           -f, --file \t Specify the file to append user name and password
           -v, --version\t Get version number
           ''')           

def main():
    filename = DEFAULT_FILE
    try: 
        opts, args = getopt.getopt(sys.argv[1:], 'hvf:', 
                                   ['help', 'file=', 'version=']) 
    except getopt.GetoptError as err: 
        print(err) 
        usage() 
        sys.exit(2)
    for op, param in opts:        
        if op in ('-h', '--help'): 
            usage()
            sys.exit()
        elif op in ('-v', '--version'): 
            print(VERSION_NUMBER)
            sys.exit()                     
        elif op in ('-f', "--file"):
            filename = param
        else: 
            assert False, 'unknown option' 
            usage()
    
    try:
        while True :
            name = input("Desired Login Name:")
            if username_exist(name, filename):
                 print("The usename already exist!")
                 continue

            while True:
                pwd1 = getpass.getpass("Choose a password:")
                pwd2 = getpass.getpass("Re-enter password:")
                if pwd1 != pwd2:
                    print("password is not same, please input again")
                else:
                    break;
            
            salt, pw = gen_password_hash(pwd1)
            save_userinfo(name, pw, salt, filename)
            inputdata = input('continue by input \'y\' or \'Y\':')
            if inputdata not in ['y', 'Y']:
                break                
                
    except KeyboardInterrupt:
        pass                


if __name__ == '__main__':
    main()

