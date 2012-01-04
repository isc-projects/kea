#!/usr/bin/python

# This script lists obsolete (fully merged) branches. It is useful for periodic maintenance
# of our GIT tree.
#
# This script requires python 2.7 or 3.
#
# I have limited experience in Python. If things are done in a strange or uncommon way, there
# are no obscure reasons to do it that way, just plain lack of experience. :)
#
#                                                                        tomek

import string
import subprocess

class Branch:
    MERGED=1
    NOTMERGED=2
    name = ""
    status = NOTMERGED
    last_commit = ""


def branch_list_get():
    txt_list = subprocess.check_output(["git", "branch", "-r"])

    txt_list = txt_list.split(b"\n")

    out = []
    for branch in txt_list:
        if len(branch) == 0:
            continue
        if branch.find(b"->") != -1:
            continue
        if branch == b"origin/master":
            continue

        branch_info = Branch()

        # get branch name
        branch_info.name = branch.strip(b" ")
        branch_info.name = branch_info.name.decode("utf-8")

        # check if branch is merged or not
        print ("Checking branch %s" % branch_info.name)
        cmd = ["git", "diff", "master..." + branch_info.name ]
        diff = subprocess.check_output(cmd)
        if (len(diff) == 0):
            branch_info.status = Branch.MERGED
            # let's get the last contributor
            cmd = [ "git" , "log", "-n", "1", "--pretty=\"%ai,%ae,%an\"", branch_info.name ]

            offender = subprocess.check_output(cmd)
            offender = offender.strip(b"\n\"")

            # comment out this 2 lines to disable obfuscation
            offender = offender.replace(b"@", b"(at)")
            offender = offender.replace(b".", b"(dot)")

            branch_info.last_commit = offender.decode("utf-8")

        else:
            branch_info.status = Branch.NOTMERGED

        out.append(branch_info)
#        return (out)
    return (out)

def branch_print(branches, print_merged, print_notmerged, print_stats):
    merged = 0
    notmerged = 0
    for branch in branches:
        if (branch.status==Branch.MERGED):
            merged = merged + 1
            if (not print_merged):
                continue
            print("%s,merged,%s" % (branch.name, branch.last_commit) )
        else:
            # NOT MERGED
            notmerged = notmerged + 1
            if (not print_notmerged):
                continue
            print("%s,notmerged,%s" % (branch.name, branch.last_commit) )

    if (print_stats):
        print("#----------");
        print("#Merged    : %d" % merged)
        print("#Not merged: %d" % notmerged)

def main():
    usage = """%prog
    Lists all obsolete (fully merged into master) branches.
    """

    print("branch name,status,date,last commit(mail),last commit(name)")

    branch_list = branch_list_get()

#   Uncomment this to print out also merged branches
#    branch_print(branch_list, False, True, False)

    branch_print(branch_list, True, False, True)

if __name__ == '__main__':
   main()
