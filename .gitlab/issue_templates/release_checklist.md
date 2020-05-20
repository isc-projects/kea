---
name: Release Checklist
about: Create a new issue using this checklist for each release
---

# Kea Release Checklist

This is thoroughly documented on https://wiki.isc.org/bin/view/QA/KeaReleaseProcess

1. [ ] Make this issue confidential :exclamation: :exclamation: :exclamation: :exclamation:

## Pre-Release Preparation
Some of those checks and updates can be made before actual freeze.

1. Check Jenkins results:
   1. [ ] Check Jenkins jobs if they look ok (distcheck, etc)
   1. [ ] Check Jenkins Tests Report: https://jenkins.isc.org/job/kea-1.7/job/jenkins-tests-report/
   1. [ ] Check tarball check report: https://jenkins.isc.org/job/kea-1.7/job/tarball-internal/Kea_20Build_20Checks/
1. [ ] Check Perflab for drops in performance there (https://perflab.isc.org/)
1. Check versioning, ask the development team if
   - the library versions are being updated
   - the HOOKS_VERSION is being updated;
   - [ ] create an issue for that for developers in Gitlab
1. Prepare Release Notes
   1. [ ] Create Release Notes on Kea GitLab wiki and notify @tomek about that. It should be created under "release notes" folder, like this one: https://gitlab.isc.org/isc-projects/kea/wikis/release%20notes/Release-notes-1.5-final
   1. [ ] Finish release notes and conduct its review
1. [ ] Run https://jenkins.isc.org/job/kea-1.7/job/release-pkgs-upload-internal/ and https://jenkins.isc.org/job/kea-1.7/job/release-pkgs-check-internal/ for testing repos to check if they work correctly.

The following steps may involve changing files in the repository.

1. [ ] If not done already, then bump up Kea version in configure.ac (format: `1.x.y-git`, ie. do not drop -git)
1. [ ] Create a Kea issue for code changes that will be made due to the following checks
1. Check User's Guide sections:
   1. Chapter 1. Introduction
      1. [ ] On what platforms we are running tests using Jenkins? Update Supported Platforms in platforms.rst file.
      1. [ ] Did we add any additional 3rd party software? Update if needed
      1. [ ] Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
   1. Chapter 2. Quick Start
      1. [ ] Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
   1. Chapter 3. Installation
      1. [ ] Check installation hierarchy
      1. [ ] Check and update Building Requirements
      1. [ ] Check configure options against what ./configure -h says
1. [ ] Check ChangeLog entries in Kea main and premium: spelling, trailing whatspaces, etc.
1. [ ] Check AUTHORS, INSTALL, README files in Kea main and premium.
   -  AUTHORS: update credits
   -  README: check "provides" with Release Notes, User Guide (1.3 Kea Software)
1. [ ] Update information in sources about copyright dates, new version, etc, script: https://gitlab.isc.org/isc-private/qa-dhcp/blob/master/kea/build/prepare_kea_release.sh
1. [ ] Regenerate parsers using docs.isc.org, script: https://gitlab.isc.org/isc-private/qa-dhcp/blob/master/kea/build/regen-parsers.sh.

If changes were made, commit the change, push the branch to the main repository and request a review. Once the changes have been approved, merge the branch to master.

## Build selection and upload package
That is the last moment to freeze code!

1. [ ] Go to tarball-internal Jenkins job and pick last tarball built - it will be a release candidate.
1. [ ] Check tarball before requesting sanity checks from dev team
   1. Download tarballs from picked jenkins build
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
1. [ ] If all seems to be ok then upload tarballs to repo.isc.org
   1. Go to release-upload Jenkins job
   1. Click "Build with Parameters"
   1. In field "Tarball" select picked tarball build
   1. In field "Release_Candidate" pick:
      1. rc1 if this is the first selected build for release, it will push selected tarballs to repo.isc.org, to folder suffixed with indicated rc#
      1. next rc# if this is a respin after some fixes (note: it is not possible to pick previous rc number - it will result in error)
      1. final if the last rc number was ok, this will push selected tarbal to repo.isc.org, to folder with no suffixes
1. [ ] If none of the results force you to fix and rebuild package, send sanity checks request

## Sanity Checks

1. [ ] Create Sanity Checks announcement, put there:
   - a link to sanity checks steps: https://wiki.isc.org/bin/view/QA/KeaReleaseProcess, "4. Sanity Checks" chapter
   - a link to an issue created in next step
   - tarballs locations with SHA256 checksums
   - rpm/deb packages locations and versions
1. [ ] Create a GitLab issue for sanity checks, put there the announcement
1. [ ] Send the announcement to dhcp-team@isc.org

## Releasing Tarballs
1. [ ] Update Release Notes with ChangeLog entries
1. [ ] Upload final tarballs to repo.isc.org
   1. Go to release-upload Jenkins job again
   1. Click "Build with Parameters"
   1. In field "Tarball" select picked tarball build
   1. In field "Release_Candidate" pick final
1. [ ] When the upload is completed then copy SHA checksums from the log and write an email to signers@isc.org requesting signatures
   of final tarballs on repo.isc.org indicating release folders. Attach SHA checksums to the request.
1. [ ] Upload final RPM & DEB packages to cloudsmith.io
   1. Go to https://jenkins.isc.org/job/kea-1.7/job/pkg/
   1. Pick the build for selected tarball in previous steps
   1. Go to https://jenkins.isc.org/job/kea-1.7/job/release-pkgs-upload-internal/
   1. Click "Build with Parameters" link
   1. Pick your selected pkg build in Packages field, and select "prodcion" in Repository_Type field and click Build button.
   1. When it finishes run check: https://jenkins.isc.org/job/kea-1.7/job/release-pkgs-check-internal/
1. [ ] Create git tags `Kea-1.x.y` in Kea main and premium repositories
1. Update ReadTheDocs
   1. [ ] Trigger rebuilding docs on https://readthedocs.org/projects/kea/builds
   1. [ ] Publish currently released version
   1. [ ] For stable releases change change default version to point to this stable release
