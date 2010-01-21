'''
This file implements user management program. The user name and 
its password is saved in csv file.
'''

import random
from hashlib import sha1

import csv

class PasswordHash(object):
    def __init__(self, password_):
        self.salt = "".join(chr(random.randint(33, 127)) for x in range(64))
        self.saltedpw = sha1((password_ + self.salt).encode()).hexdigest()

    def check_password(self, password_):
        """checks if the password is correct"""
        return self.saltedpw == sha1((password_ + self.salt).encode()).hexdigest()

# Note: a secure application would never store passwords in plaintext in the source code
def check_username(name):
    csvfile = open('passwd.csv')
    ret = 0
    reader = csv.reader(csvfile, delimiter = "\t", quoting = csv.QUOTE_MINIMAL)
    for row in reader:
        if name == row[0]:
            ret = 1
            break
    
    csvfile.close()
    return ret

def save_info(name,pw,salt):
    csvfile = open('passwd.csv', 'a')
    writer = csv.writer(csvfile, delimiter = "\t", quoting = csv.QUOTE_MINIMAL)
    writer.writerow([name, pw, salt])
    csvfile.close()

def register():
    flag = True
    # create the file if it doesn't exist
    csvfile = open('passwd.csv', "w")
    csvfile.close()
    while flag :
        username = input("username:")
        passwd = input("passwd:")
        if check_username(username):
             print("the usename already exist!")
        else :
            pwhash = PasswordHash(passwd)
            save_info(username,pwhash.saltedpw, pwhash.salt)
            print("register success!")
            flag = False       

register()

