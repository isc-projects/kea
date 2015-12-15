#!/usr/bin/python
#
# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#
# This script lists obsolete (fully merged) branches. It is useful for periodic
# maintenance of our GIT tree.
#
# It is good idea to use following command before running this script:
#
# git pull
# git remote prune origin
#
# This script requires python 2.7 or 3.
#
# I have limited experience in Python. If things are done in a strange or
# uncommon way, there are no obscure reasons to do it that way, just plain
# lack of experience.
#
#                                                                        tomek

import string
import subprocess
import sys
from optparse import OptionParser

class Branch:
    MERGED = 1
    NOTMERGED = 2
    name = None
    status = NOTMERGED
    last_commit = None


def branch_list_get(verbose):
    """ Generates a list of available remote branches and
        checks their status (merged/unmerged). A branch is merged
        if all changes on that branch are also on master. """

    # call git branch -r (list of remote branches)
    txt_list = subprocess.check_output(["git", "branch", "-r"])

    txt_list = txt_list.split(b"\n")

    # we will store list of suitable branches here
    out = []
    for branch in txt_list:
        # skip empty lines
        if len(branch) == 0:
            continue

        # skip branches that are aliases (something -> something_else)
        if branch.find(b"->") != -1:
            continue

        # don't complain about master
        if branch == b"origin/master":
            continue

        branch_info = Branch()

        # get branch name
        branch_info.name = branch.strip(b" ")
        branch_info.name = branch_info.name.decode("utf-8")

        # check if branch is merged or not
        if verbose:
            print("Checking branch %s" % branch_info.name)

        # get a diff with changes that are on that branch only
        # i.e. all unmerged code.
        cmd = ["git", "diff", "master..." + branch_info.name ]
        diff = subprocess.check_output(cmd)
        if len(diff) == 0:
            # No diff? Then all changes from that branch are on master as well.
            branch_info.status = Branch.MERGED

            # let's get the last contributor with extra formatting
            # see man git-log and search for PRETTY FORMATS.
            # %ai = date, %ae = author e-mail, %an = author name
            cmd = [ "git" , "log", "-n", "1", "--pretty=\"%ai,%ae,%an\"",
                    branch_info.name ]
            offender = subprocess.check_output(cmd)
            offender = offender.strip(b"\n\"")

            # comment out this 2 lines to disable obfuscation
            offender = offender.replace(b"@", b"(at)")
            # Obfuscating a dot does not work too well for folks that use
            # initials
            #offender = offender.replace(b".", b"(dot)")

            branch_info.last_commit = offender.decode("utf-8")

        else:
            # diff is not empty, so there is something to merge
            branch_info.status = Branch.NOTMERGED

        out.append(branch_info)
    return out

def branch_print(branches, csv, print_merged, print_notmerged, print_stats):
    """ prints out list of branches with specified details (using
        human-readable (or CSV) format. It is possible to specify,
        which branches should be printed (merged, notmerged) and
        also print out summary statistics """

    # counters used for statistics
    merged = 0
    notmerged = 0

    # compact list of merged/notmerged branches
    merged_str = ""
    notmerged_str = ""
    for branch in branches:
        if branch.status == Branch.MERGED:
            merged = merged + 1
            if not print_merged:
                continue
            if csv:
                print("%s,merged,%s" % (branch.name, branch.last_commit) )
            else:
                merged_str = merged_str + " " + branch.name
        else:
            # NOT MERGED
            notmerged = notmerged + 1
            if not print_notmerged:
                continue
            if csv:
                print("%s,notmerged,%s" % (branch.name, branch.last_commit) )
            else:
                notmerged_str = notmerged_str + " " + branch.name

    if not csv:
        if print_merged:
            print("Merged branches    : %s" % (merged_str))
        if print_notmerged:
            print("NOT merged branches: %s" % (notmerged_str))

    if print_stats:
        print("#----------")
        print("#Merged    : %d" % merged)
        print("#Not merged: %d" % notmerged)


def parse_args(args=sys.argv[1:], Parser=OptionParser):

    parser = Parser(description="This script prints out merged and/or unmerged"
                    " branches of a GIT tree.")

    parser.add_option("-c", "--csv", action="store_true",
                      default=False, help="generates CSV output")
    parser.add_option("-u", "--unmerged", action="store_true",
                      default=False, help="lists unmerged branches")
    parser.add_option("-m", "--skip-merged", action="store_true",
                      default=False, help="omits listing merged branches")
    parser.add_option("-s", "--stats", action="store_true",
                      default=False, help="prints also statistics")

    (options, args) = parser.parse_args(args)

    if args:
        parser.print_help()
        sys.exit(1)

    return options

def main():
    usage = """%prog
    Lists all obsolete (fully merged into master) branches.
    """

    options = parse_args()
    csv = options.csv
    merged = not options.skip_merged
    unmerged = options.unmerged
    stats = options.stats

    if csv:
        print("branch name,status,date,last commit(mail),last commit(name)")

    branch_list = branch_list_get(not csv)

    branch_print(branch_list, csv, merged, unmerged, stats)

if __name__ == '__main__':
   main()
