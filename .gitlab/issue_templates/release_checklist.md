---
name: Release Checklist
about: Create a new issue using this checklist for each release
---

# Kea Release Process
## Introduction
The Kea release process (for the base version of Kea and the hooks) is different to that of DHCP. At the moment, Kea has only one supported release at a time, so the process tries to ensure that any modifications needed for a release take place on the master branch, rather than on a version-specific one. The basic steps for a release are:

1) Announce a code freeze for the master branch that will last until actual tarball release
2) Do all necessary changes to the master branch for the release
3) Create release tarball from master branch
4) After sanity checks made by the QA and development teams, either we continue or we accept changes on master to fix issues if needed and go back to the previous step.
5) Create a release branch (for beta) or merge master to existing release branch (for final) and tag release on it. (???)
6) Sign and upload tarballs
7) Announce that freeze time on master branch is over.
8) Release tarballs are prepared by Jenkins job: https://jenkins.isc.org/job/kea-master-tarball-internal/. When given tarball is accepted for releasing it is pushed to repo.isc.org using Jenkins job: https://jenkins.isc.org/job/kea-release-upload-internal/

## Pre-Release Preparation
Some of those checks and updates can be made before actual freeze, but it's reasonable to announce freeze now!

- [ ] 1. Check Jenkins results:
* Number of unit tests and system tests failing
* Is there a change in system tests pass rate? *Notify the development team of the overall Jenkins status
* Look into tarball check report " Kea Build Checks" on last tarball build and check if there is nothing suspicious (add/removed files, etc), verify that with developers:
* Compare current release package with code in repository
* Compare current release package with previous release package

- [ ] 2. Is the distcheck passing on kea and kea+premium (https://jenkins.isc.org/job/kea-master-distcheck/)?
* Highlight any issues that require fixing.

- [ ] 3. Check perflab if there is no critical errors there (https://perflab.isc.org/)
- [ ] 4. Make sure that there is no pending ticket to merge! (Use GitLab https://gitlab.isc.org/isc-projects/kea/merge_requests and https://gitlab.isc.org/isc-private/kea-premium/merge_requests or contact the development team).
- [ ] 5. Check the Known Issues list, is there something that suppose to be fixed before release and was omitted?
- [ ] 6. Check versioning:
* Ask the development team if the library versions are being updated (there is a step to check it later).
* Ask the development team if the HOOKS_VERSION is being updated.
- [ ] 7. Create Release Notes on Kea GitLab wiki using standard template, update all dates and versions. This wiki page should created under "release notes" folder, like this one: release-notes-1.5-final
- [ ] 8. Check if there is a Release Checklist ready. If not, create new one using this template (page could have been created, check Releases section at the bottom of this page)

## The following steps may involve changing files in the repository. If any files will be updated, create a Kea ticket for them and make the changes on a separate branch.

- [ ] Check User's Guide sections:
* Chapter 1. Introduction
- On what platforms we are running tests using Jenkins? Update Supported Platforms
- Did we add any additional 3rd party software? Update if needed
- Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
* Chapter 2. Quick Start
- Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
* Chapter 3. Installation
- Check installation hierarchy
- Check and update Building Requirements
- Check configure options against what ./configure -h says

- [ ] 2. Check !ChangeLog entries in Kea main and premium:
* Spelling, missing numbers, trailing whatspaces? (some of that is checked in every build of tarball-internal Jenkins job)
* Update Release Notes with !ChangeLog entries

- [ ] 3. Check AUTHORS, INSTALL, README files in Kea main and premium.
- [ ] 4. Update information in sources about copyright dates, new version, etc. This is done manually using script https://gitlab.isc.org/isc-private/qa-dhcp/blob/master/kea/build/prepare_kea_release.sh

- [ ] 5. Regenerate parsers using docs.isc.org:
* download kea repo
```
cd kea; autoreconf -fi; ./configure --with-log4cplus=/home/wlodek/log4cplus --enable-generate-parser (log4cplus in /home/wlodek should be available for everyone, if not - download your own)
export PATH=/home/fdupont/bin:$PATH
cd ~/kea/src/bin/dhcp4; touch *.yy; make parser
cd ~/kea/src/bin/dhcp6; touch *.yy; make parser
cd ~/kea/src/bin/d2; touch *.yy; make parser
cd ~/kea/src/bin/agent; touch *.yy; make parser
cd ~/kea/src/bin/netconf/; touch *.yy; make parser
cd ~/kea/src/lib/eval; touch *.yy; make parser
```

TODO: we should regenerate all of them or just the one that been modified?
If changes were made, commit the change, push the branch to the main repository and request a review. Once the changes have been approved, merge the branch to master.


## Build selection and upload package
That is the last moment to freeze code!

- [ ] 1. Update release version in configure.ac and remove -git suffix, and commit the change on master. From that moment all tarball builds can be officially released.
- [ ] 2. Go to tarball-internal Jenkins job and pick last tarball build - it will be a release candidate.
- [ ] 3. Tarball checks before requesting sanity checks from dev team
* Download tarballs from picked jenkins build
Untar packages:
* Check sizes - is new package reasonable?
* Check installation tree, compare it with previous release
* Check installed lib versions
* which were updated? (save results)
* any of the lib from current release has lower number then corresponding lib from previous release? (!)
* Uninstall Kea, check what left (there should be just configuration files)
* Check if all of installed binaries has man page
* if not, is it in the tarball?
* are man page up-to-date?
* Check if documentation is properly formatted, has correct versions and dates.
* it's advised to search for previous version numbers, some of them are statically added in statements that are no longer valid

- [ ] 4. If all seems to be ok then upload tarballs to repo.isc.org
* Go to release-upload Jenkins job
* Click "Build with Parameters"
* In field "Tarball" select picked tarball build
* In field "Release_Candidate" pick:
* rc1 if this is the first selected build for release, it will push selected tarballs to repo.isc.org, to folder suffixed with indicated rc#
* next rc# if this is a respin after some fixes (note: it is not possible to pick previous rc number - it will result in error)
* final if the last rc number was ok, this will push selected tarbal to repo.isc.org, to folder with no suffixes

- [ ] 5. If none of the results force you to fix and rebuild package, send sanity check request by an email to dhcp-team@isc.org and qa@isc.org with indicating paths with tarballs on repo.isc.org asking for sanity checks

## Sanity checks proposals:
- [ ] Check documentation:
* users guide:
- dates, versions, installation instructions both for kea and premium, formatting
if you have time - read as much as you can.
* man pages:
- dates, versions, is it up-to-date? or usage changed between releases?
- does every binary has it's own .8 page?
- [ ] Check tarball content:
* compare tarball against repo (does some of the not included files should actually be included?)
* does premium tarballs include correct hooks? (any missing files?)
- [ ] compile:
* configure warnings?
* build warnings?
- [ ] run unit tests with various db backends, install (check tree), uninstall (check tree)
- [ ] Check example configurations
- [ ] Check release notes (not included in tarball)
- [ ] Check AUTHORS, INSTALL, COPYING, README files
- [ ] Check db update scripts:
* tarball inlcude the last one? (compare with repo)

## Releasing tarballs:
- [ ] 1. Write an email to signers@isc.org requesting signatures of final tarballs on repo.isc.org indicating release folders. - Attach SHA256 checksums from tarball-internal logs.
- [ ] 2. Make release branch (e.g. v1_5_0 one branch for beta and final, with tags for both releases)
- [ ] 3. Upload Release Notes to repo.isc.org
- [ ] 4. When release packages are signed then upload them from repo.isc.org to ftp:
* make-available --public --symlink=cur /data/shared/sweng/kea/releases/1.4.0-beta
* make-available --private /data/shared/sweng/kea/releases/premium-1.4.0-beta/
* make-available --private /data/shared/sweng/kea/releases/subscription-1.4.0-beta/
- [ ] 5. Contact support or marketing to upload packages to www.isc.org/downloads
- [ ] 6. Contact marketing to upload premium packages to 'products' in web store
- [ ] 7. Contact support to deliver premium and subscriber-only hooks to Kea support subscribers
- [ ] 8. For final release - Release Notes should contain changlogs since previous stable release (beta +final)
- [ ] 9. Modify Release Notes to Announcement
- fold -sw 73 Kea140betaReleaseNotes.txt > Announcement
- change header
- change ftp links to ww.isc.org/downloads
- send it to yourself to check if it's ok
- [ ] 10. Prepare article on kb.isc.org
- change editing mode to HTML, copy release notes between <pre></pre>
- ask support to publish this document
- [ ] Send announcements on:
* kea-users@lists.isc.org
* kea-announce@lists.isc.org
* dhcp-announce@lists.isc.org
- [ ] 11.Notify marketing 
* announce via social media
* publish any blog post that is planned
* Update kea.isc.org 
* Update Wikipedia page release info
* Add new hooks to downloadable products (if applies)
* Update subscription data sheet with any new hook (if applies)
* Inform sales about what the release may mean to them
- [ ] 12. Check KnownIssues list on kea.isc.org https://kea.isc.org/wiki/KeaKnownIssues
ssh kea.isc.org /var/www/kea-docs
- [ ] 13. update page: https://wiki.isc.org/bin/view/Main/KeaReleaseDates
- [ ] 14. update page: https://wiki.isc.org/bin/view/Main/EngineeringReleaseSchedule
