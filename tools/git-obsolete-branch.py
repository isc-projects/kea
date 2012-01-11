#!/usr/bin/python
#
# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

#
# This script lists obsolete (fully merged) branches. It is useful for periodic maintenance
# of our GIT tree.

# It is good to use following command before running this script:
#
# git pull
# git remote prune origin
#
# This script requires python 2.7 or 3.
#
# I have limited experience in Python. If things are done in a strange or uncommon way, there
# are no obscure reasons to do it that way, just plain lack of experience.
#
#                                                                        tomek

import string
import subprocess
import sys

class Branch:
    MERGED=1
    NOTMERGED=2
    name = ""
    status = NOTMERGED
    last_commit = ""


def branch_list_get(verbose):
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
        if verbose:
            print("Checking branch %s" % branch_info.name)

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

def branch_print(branches, csv, print_merged, print_notmerged, print_stats):
    merged = 0
    notmerged = 0
    merged_str = ""
    notmerged_str = ""
    for branch in branches:
        if (branch.status==Branch.MERGED):
            merged = merged + 1
            if (not print_merged):
                continue
            if (csv):
                print("%s,merged,%s" % (branch.name, branch.last_commit) )
            else:
                merged_str = merged_str + " " + branch.name
        else:
            # NOT MERGED
            notmerged = notmerged + 1
            if (not print_notmerged):
                continue
            if (csv):
                print("%s,notmerged,%s" % (branch.name, branch.last_commit) )
            else:
                notmerged_str = notmerged_str + " " + branch.name

    if (not csv):
        if (print_merged):
            print("Merged branches    : %s" % (merged_str))
        if (print_notmerged):
            print("NOT merged branches: %s" % (notmerged_str))

    if (print_stats):
        print("#----------");
        print("#Merged    : %d" % merged)
        print("#Not merged: %d" % notmerged)

def show_help():
    print("This script prints out merged and/or unmerged branches of a GIT tree.")
    print("Supported command-line options:")
    print("")
    print("--csv          produce CSV (coma separated value) output")
    print("--unmerged     lists umerged branches")
    print("--skip-merged  do not print merged branches (that are listed by default)")
    print("--stats        prints out statistics")
    print("--help         prints out this help")

def main():
    usage = """%prog
    Lists all obsolete (fully merged into master) branches.
    """

    csv = False;
    merged = True;
    unmerged = False;
    stats = False;

    for x in sys.argv[1:]:
        if x == "--csv":
            csv = True;
        elif x == "--unmerged":
            unmerged = True;
        elif x == "--skip-merged":
            merged = False;
        elif x == "--stats":
            stats = True;
        elif x == "--help":
            show_help()
            return
        else:
            print("Invalid parameter: %s" % x)
            print("")
            show_help()
            return

    if csv:
        print("branch name,status,date,last commit(mail),last commit(name)")

    branch_list = branch_list_get(not csv)

#   Uncomment this to print out also merged branches
#    branch_print(branch_list, False, True, False)

    branch_print(branch_list, csv, merged, unmerged, stats)

if __name__ == '__main__':
   main()
