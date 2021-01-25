---
name: Release Checklist
about: Create a new issue using this checklist for each release
---

# Kea Release Checklist

This is thoroughly documented in [the Kea Release Process guide](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess).

## Pre-Release Preparation

Some of those checks and updates can be made before actual freeze.

1. Check Jenkins results:
   1. [ ] Check Jenkins jobs for failures: [distcheck](https://jenkins.isc.org/job/kea-dev/job/distcheck/), etc...
   1. [ ] Check [Jenkins Tests Report](https://jenkins.isc.org/job/kea-dev/job/jenkins-tests-report/).
   1. [ ] Check [tarball check report](https://jenkins.isc.org/job/kea-dev/job/tarball-internal/Kea_20Build_20Checks/)
1. [ ] Check [Performance Test Results](https://jenkins.isc.org/job/kea-dev/job/performance/KeaPerformanceReport/) in Jenkins for drops in performance.
1. Check versioning, ask the development team if:
   - the library versions are being updated
   - `KEA_HOOKS_VERSION` is being updated
   - [ ] create an issue for that for developers in Gitlab
   - script: [./tools/bump-lib-versions.sh](https://gitlab.isc.org/isc-projects/kea/-/blob/master/tools/bump-lib-versions.sh) Kea-q.w.e Kea-a.b.c (where `a.b.c` is the version to be released and `q.w.e` is the version previous to that)
1. Prepare Release Notes
   1. [ ] Create Release Notes on Kea GitLab wiki and notify @tomek about that. It should be created under "release notes" directory, like this one: https://gitlab.isc.org/isc-projects/kea/-/wikis/release%20notes/release-notes-1.9.2
   1. [ ] Finish release notes and conduct its review
1. [ ] Run [release-pkgs-upload-internal](https://jenkins.isc.org/job/kea-dev/job/release-pkgs-upload-internal/) and [release-pkgs-check-internal](https://jenkins.isc.org/job/kea-dev/job/release-pkgs-check-internal/) to test repositories for correctness.

The following steps may involve changing files in the repository.

1. [ ] Create a Kea issue for code changes that will be made due to the following checks:
1. Check User's Guide sections:
   1. Chapter 1. Introduction
      1. [ ] On what platforms we are running tests using Jenkins? Update Supported Platforms in platforms.rst file.
      1. [ ] Did we add any additional 3rd party software? Update if needed
      1. [ ] Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
   1. Chapter 2. Quick Start
      1. [ ] Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
   1. Chapter 3. Installation
      1. [ ] Check installation hierarchy
      1. [ ] Check and update Build Requirements
      1. [ ] Check configure options against what `./configure -h` says
1. [ ] Check ChangeLog entries in Kea main and premium: spelling, trailing whatspaces, etc.
1. [ ] Check AUTHORS, INSTALL, README files in Kea main and premium.
   -  AUTHORS: update credits
   -  README: check "provides" with Release Notes, User Guide (1.3 Kea Software)
1. [ ] Update information in sources about copyright dates, new version, etc, script: [prepare_kea_release.sh](https://gitlab.isc.org/isc-private/qa-dhcp/blob/master/kea/build/prepare_kea_release.sh).
1. [ ] Regenerate parsers using docs.isc.org, script: [regen-parsers.sh](https://gitlab.isc.org/isc-private/qa-dhcp/blob/master/kea/build/regen-parsers.sh).

If changes were made, commit the change, push the branch to the main repository and request a review. Once the changes have been approved, merge the branch to master.

## Build selection and upload package

This is the last moment to freeze code! :snowflake:

1. [ ] Go to [tarball-internal](https://jenkins.isc.org/job/kea-dev/job/tarball-internal/) Jenkins job and pick last tarball built - it will be a release candidate.
1. [ ] Check tarball before requesting sanity checks from the development team.
   1. Download tarballs from picked Jenkins build
   1. Check sizes - is new package reasonable?
   1. Check installation tree, compare it with previous release
   1. Check installed lib versions
      1. which were updated? (save results)
      1. any of the lib from current release has lower number then corresponding lib from previous release? (!)
   1. Uninstall Kea, check what left (there should be just configuration files)
   1. Check if all of installed binaries has man page
      1. if not, is it in the tarball?
      1. are man page up-to-date?
   1. Check if documentation is properly formatted, has correct versions and dates.
      1. it's advised to search for previous version numbers, some of them are statically added in statements that are no longer valid
1. [ ] Upload tarballs to repo.isc.org using Jenkins
   1. Go to [release-tarball-upload-internal](https://jenkins.isc.org/job/kea-dev/job/release-tarball-upload-internal/) Jenkins job.
   1. Click "Build with Parameters"
   1. In field "Tarball" select picked tarball build
   1. In field "Release_Candidate" pick:
      1. rc1 if this is the first selected build for release, it will push selected tarballs to repo.isc.org, to a directory suffixed with indicated rc#
      1. next rc# if this is a respin after some fixes (note: it is not possible to pick previous rc number - it will result in error)
      1. final if the last rc number was ok, this will push selected tarball to repo.isc.org, to a directory with no suffixes
1. [ ] If none of the results force you to fix and rebuild package, send sanity checks request if not already triggered automatically by `release-tarball-upload-internal`.

## Sanity Checks

1. [ ] Create Sanity Checks announcement, put there:
   - a link to chapter 4 Sanity Checks of the release process: [KeaReleaseProcess - SanityChecks](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess#4.%20Sanity%20Checks)
   - a link to an issue created in next step
   - tarballs locations with SHA256 checksums
   - rpm/deb packages locations and versions
1. [ ] Create a GitLab issue for sanity checks, put there the announcement
1. [ ] Send the announcement to dhcp-team@isc.org

## Releasing Tarballs

1. [ ] Update Release Notes with ChangeLog entries
1. [ ] Upload final tarballs to repo.isc.org
   1. Go to [release-tarball-upload-internal](https://jenkins.isc.org/job/kea-dev/job/release-tarball-upload-internal/) Jenkins job.
   1. Click "Build with Parameters"
   1. In field "Tarball" select picked tarball build
   1. In field "Release_Candidate" pick final
1. [ ] When the upload is completed then copy SHA checksums from the log and write an email to signers@isc.org requesting signatures
   of final tarballs on repo.isc.org indicating release directories. Attach SHA checksums to the request.
1. [ ] Upload final RPM & DEB packages to cloudsmith.io
   1. Go to [release-pkgs-upload-internal](https://jenkins.isc.org/job/kea-dev/job/release-pkgs-upload-internal/).
   1. Click "Build with Parameters" link
   1. Pick your selected pkg build in Packages field, and select `PrivPubRepos: "both"`, `TestProdRepos: "production"` and click Build button.
   1. When it finishes run check: [releases-pkgs-check-internal](https://jenkins.isc.org/job/kea-dev/job/release-pkgs-check-internal/).
1. [ ] Create git tags `Kea-a.b.c` in Kea main and premium repositories.
1. Update ReadTheDocs
   1. [ ] Trigger rebuilding docs on [readthedocs.org](https://readthedocs.org/projects/kea/builds).
   1. [ ] Publish currently released version. On the `Versions` tab, scroll down to `Activate a version`, search for `kea-a.b.c` and click `Activate`.
   1. [ ] For stable releases, change the default version to point to this stable release.


### On the Day of Public Release

 - [ ] ***(Support)*** Wait for clearance from Security Officer to proceed with the public release (if applicable).
 - [ ] ***(Support)*** Place tarballs in public location on FTP site.
 - [ ] ***(Support)*** Publish links to downloads on ISC website.
 - [ ] ***(Support)*** Write release email to *kea-announce*.
 - [ ] ***(Support)*** Write email to *kea-users* (if a major release).
 - [ ] ***(Support)*** Send eligible customers updated links to the Subscription software FTP site.
 - [ ] ***(Support)*** If it is a new major version, sweng will have created a new repo in Cloudsmith, which will need the customer tokens migrated from an existing repo. Then update support customers that this new private repo exists.
 - [ ] ***(Support)*** Update tickets in case of waiting support customers.
 - [ ] ***(QA)*** Inform Marketing of the release.
 - [ ] ***(Marketing)*** Upload Premium hooks tarball to SendOwl. Create a new product if a new branch, otherwise update existing product. Send notifications to existing subscribers of the new version.
 - [ ] ***(Marketing)*** Announce on social media.
 - [ ] ***(Marketing)*** Update [Wikipedia entry for Kea](https://en.wikipedia.org/wiki/Kea_(software)).
 - [ ] ***(Marketing)*** Write blog article (if a major release).
 - [ ] ***(Marketing)*** Update [Kea page on web site if any new hooks](https://www.isc.org/kea/).
 - [ ] ***(Marketing)*** Update Kea Premium and Kea Subscription data sheets if any new hooks.
 - [ ] ***(Marketing)*** Update [significant features matrix](https://kb.isc.org/docs/en/aa-01615) (if any significant new features).
 - [ ] ***(Marketing)*** Update [Kea documentation page in KB](https://kb.isc.org/docs/en/kea-administrator-reference-manual).

## Post-Release, But Before Code Unfreeze

- [ ] Bump up Kea version in `configure.ac` to next development version which could be, based on just released version `a.b.c`:
    * `a.b.z-git` where `z == c + 1` or
    * `a.y.0-git` where `y == b + 1` or
    * `x.1.0-git` where `x == a + 1`
- [ ] Bump up `REF_KEA_VERSION` in `qa-dhcp/kea/jenkins/tarball-internal.jenkinsfile` to `x.y.z` i.e. released version
