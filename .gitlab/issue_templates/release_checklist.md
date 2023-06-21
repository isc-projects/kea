---
name: a.b.c release checklist
about: Create a new issue using this checklist for each release.
---

# Kea Release Checklist

This is thoroughly documented in [the Kea Release Process guide](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess).

## Pre-Release Preparation

Some of those checks and updates can be made before the actual freeze.
For new stable releases or maintenance releases, please don't use `kea-dev` build farm. Use dedicated build farm for each release cycle.

1. Check Jenkins results:
   1. [ ] Check Jenkins jobs for failures: [distcheck](https://jenkins.aws.isc.org/job/kea-dev/job/distcheck/), etc...
   1. [ ] Check [Jenkins Tests Report](https://jenkins.aws.isc.org/job/kea-dev/job/jenkins-tests-report/).
   1. [ ] Check [tarball check report](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/Kea_20Build_20Checks/)
1. [ ] Check [Performance Test Results](https://jenkins.aws.isc.org/job/kea-dev/job/performance/) in Jenkins for drops in performance.
1. Check versioning, ask the development team if:
   - the library versions are being updated
   - `KEA_HOOKS_VERSION` is being updated
   - [ ] create an issue for that for developers in Gitlab
   - script: [./tools/bump-lib-versions.sh](https://gitlab.isc.org/isc-projects/kea/-/blob/master/tools/bump-lib-versions.sh) Kea-q.w.e Kea-a.b.c (where `a.b.c` is the version to be released and `q.w.e` is the version previous to that)
1. [ ] Look at the issue numbers in commit descriptions. Add to ChangeLog a mention about any change with visible impact that had not been mentioned already.
1. If any changes have been done to database schemas, then:
   1. [ ] Check that a previously released schema has not been changed.
   1. [ ] Check that the additions to `dhcpdb_create.*sql`, and nothing more nor less than what was added in this release, is present in a `upgrade_*_to_*.sh.in` script that should also have been added in this release.
1. Prepare Release Notes
   1. [ ] Create Release Notes on Kea GitLab wiki and notify @tomek about that. It should be created under "release notes" directory, like this one: https://gitlab.isc.org/isc-projects/kea/-/wikis/release%20notes/release-notes-2.1.0
   1. [ ] Finish release notes and conduct its review. Also please notify @sgoldlust or @vicky that release notes are ready for review.
1. [ ] Check that packges can be uploaded to cloudsmith.
   1. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
   1. Click `Build with Parameters`.
   1. Pick the latest pkg build in the `Packages` field, and the corresponding tarball build in the `Tarball` field, leave the rest as they are `PrivPubRepos: "private"`, `TarballOrPkg: "packages"`, `TestProdRepos: "testing"` and click `Build`.
   1. If a new Cloudsmith repository is used, then:
      1. [ ] Make sure freeradius packages are uploaded to the Cloudsmith repository or copied from a previous repository.
      1. [ ] Make sure access tokens have been synchronized from previous Cloudsmith repositories and to the [check-pkgs.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/pkgs-check/check-pkgs.py) QA tool.
1. [ ] Check if ReadTheDocs can build Kea documentation. Alternatively, look for failures in emails if you know that the ReadTheDocs webhook is working.
   1. Trigger rebuilding docs on [readthedocs.org](https://readthedocs.org/projects/kea/builds) and wait for the build to complete.

The following steps may involve changing files in the repository.

1. [ ] Run [update-code-for-release.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/build/update-code-for-release.py) <br>
   Example command: `GITLAB_TOKEN='...' ./update-code-for-release.py 1.9.7 --repo-dir ~/isc/repos/kea/` Use `--upload` to commit changes. <br>
   Help: `GITLAB_TOKEN="..." ./update-code-for-release.py --help`<br>
   This script makes the following changes and actions:
   1. run prepare_kea_release.sh that does:
        1. add release entries in ChangeLogs
        1. update Kea version in configure.ac
        1. update copyright years in files that were changed in current year
        1. sort message files
        1. regenerate message files headers
   2. regenerate parsers using Bison from Docker<br>
   With `--upload`:
   3. create an issue in GitLab for release changes in kea repo
   4. create branches and merge requests for kea and kea-premium
   5. commit the changes in both repos
   6. checkout created branches in both repos
   7. commit and push the changes to GitLab server
1. Check manually User's Guide sections:
   1. Chapter 1. Introduction
      1. [ ] On what platforms we are running tests using Jenkins? Update Supported Platforms in platforms.rst file.
      1. [ ] Did we add any additional 3rd party software? Update if needed
      1. [ ] Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
   1. Chapter 2. Quick Start
      1. [ ] Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
   1. Chapter 3. Installation
      1. [ ] Check installation hierarchy (this is also automatically checked at the end of [ut-extended job](https://jenkins.aws.isc.org/job/kea-dev/job/ut-extended/))
      1. [ ] Check and update Build Requirements
      1. [ ] Check configure options against what `./configure -h` says
1. [ ] Check ChangeLog entries in Kea main and premium: spelling, trailing whitespaces, etc.
1. [ ] Check AUTHORS, INSTALL, README files in Kea main and premium.
   -  AUTHORS: update credits
   -  README: check "provides" with Release Notes, User Guide (1.3 Kea Software)
1. [ ] If changes were made, commit the change, push the branch to the main repository and request a review. Once the changes have been approved, merge the MR to master.

## Build selection, tarballs upload and sanity checks

This is the last moment to freeze code! :snowflake:

1. [ ] Go to [build-tarball](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/) Jenkins job and pick the last tarball built - it will be a release candidate.
1. [ ] Check tarball before requesting sanity checks from the development team.
   1. Download tarballs from picked Jenkins build
   1. Check hook libraries.
      1. Are there any new hook libraries installed in this release?
         1. Are they in the proper tarball? Premium or subscription?
         1. Do they have their own package?
   1. Check sizes - is the new package reasonable?
   1. Check installation tree, compare it with the previous release
   1. Check installed libraries.
      1. which were updated? (save results)
      1. Do any of the libraries from the current release have lower version than in the previous release?
   1. Uninstall Kea, check what left (there should be just configuration files)
   1. Check if each of the installed binaries has a man page.
      1. If not, is the binary included in the tarball? That might explain it.
      1. Are man pages up to date?
   1. Check if documentation is properly formatted, has correct versions and dates.
      1. It's advised to search for previous version numbers, some of them are statically added in statements that are no longer valid.
1. [ ] Upload tarballs to repo.isc.org using Jenkins and send sanity checks request.
   1. Go to [release-tarball-upload](https://jenkins.aws.isc.org/job/kea-dev/job/release-tarball-upload/) Jenkins job.
   1. Click `Build with Parameters`.
   1. In field `Tarball` select picked tarball build.
   1. In field `Pkg` select the corresponding pkg job.
   1. In field `Release_Candidate` pick:
      1. `rc1` if this is the first selected build for release, it will push the selected tarballs to repo.isc.org, to a directory suffixed with indicated rc#
      1. next rc# if this is a respin after some fixes (note: it is not possible to pick previous rc number - it will result in an error)
   1. Submit the job that will automatically:
      1. Upload the tarballs <br>
      and if this is not the final version:
      1. Create a GitLab issue for sanity checks, put there the announcement
      1. Send Sanity Checks announcement on the Kea/DHCP channel on Mattermost.<br>
      The announcement includes:
         - a link to chapter 4 Sanity Checks of the release process: [KeaReleaseProcess - SanityChecks](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess#4.%20Sanity%20Checks)
         - a link to the GitLab issue
         - tarballs locations with SHA256 checksums
         - rpm/deb packages locations and versions


## Releasing Tarballs and Packages

1. [ ] Update Release Notes with ChangeLog entries
1. [ ] Mark Jenkins jobs with release artifacts to be kept forever and update description of build by adding there version of released kea (e.g. Kea-2.2.2): <br>
   Go to the following Jenkins jobs, click release build and then, on the build page, click `Keep this build forever` button and edit description: <br>
   1. [build-tarball](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/)
   1. [pkg job](https://jenkins.aws.isc.org/job/kea-dev/job/pkg/)
1. [ ] Upload final tarballs to repo.isc.org.
   1. Go to [release-tarball-upload](https://jenkins.aws.isc.org/job/kea-dev/job/release-tarball-upload/) Jenkins job.
   1. Click `Build with Parameters`.
   1. In field `Tarball` select picked tarball build.
   1. In field `Pkg` select the corresponding pkg job.
   1. In field `Release_Candidate` pick `final`. <br>
   This job will also:
      - open an issue on [the signing repository](https://gitlab.isc.org/isc-private/signing/-/issues) for signing final tarballs on repo.isc.org
      - create Git tags `Kea-a.b.c` in Kea main and premium repositories
      - if release engineer is holding personal signing key, please use [sign, verify, and upload script](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/build/sign_kea_and_upload_asc.sh)
      - if release enginner do NOT have signing key, please contact team member.
1. [ ] Upload final RPM & DEB packages, tarballs and sign files to cloudsmith.io
   1. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
   1. Click `Build with Parameters`.
   1. Pick your selected pkg build in the `Packages` field, the corresponding tarball build in the `Tarball` field, `PrivPubRepos: "both"`, `TarballOrPkg: "both"`, `TestProdRepos: "production"` and click `Build`.
      - This step also verifies sign files.
   1. When it finishes run check: [releases-pkgs-check](https://jenkins.aws.isc.org/job/kea-dev/job/release-pkgs-check/).
1. [ ] Update ReadTheDocs
   1. Trick ReadTheDocs into pulling the latest tags. Click `Build version` on [readthedocs.org](https://readthedocs.org/projects/kea/builds).
   1. Publish currently released version. On the `Versions` tab, scroll down to `Activate a version`, search for `kea-a.b.c` and click `Activate`.
   1. If it's a stable release, change the default version to point to this stable release. `Admin -> Advanced Settings -> Default version* -> Kea-a.b.c`.
1. [ ] Create an issue and a merge request to bump up Kea version in `configure.ac` to next development version which could be, based on just released version `a.b.c`:
    * `a.b.z-git` where `z == c + 1` most of the time, or
    * `a.y.0-git` where `y == b + 2` if a new development series starts, or
    * `x.1.0-git` where `x == a + 1` when the released minor version `b` is 9 and `a.b.c` was the last version in the development series and a new development version is coming up next.
1. [ ] Send a request for publishing the release on the Support Mattermost channel linking the Signing issue and the release checklist issue.


### On the Day of Public Release

 - [ ] ***(Support)*** Wait for clearance from Security Officer to proceed with the public release (if applicable).
 - [ ] ***(Support)*** Confirm that the tarballs have the checksums mentioned on the signing ticket.
 - [ ] ***(Support)*** Place tarballs in public location on FTP site.
 - [ ] ***(Support)*** Publish links to downloads on ISC website.
 - [ ] ***(Support)*** Write release email to *kea-announce*.
 - [ ] ***(Support)*** Write email to *kea-users* (if a major release).
 - [ ] ***(Support)*** Send eligible customers updated links to the Subscription software FTP site.
 - [ ] ***(Support)*** If it is a new `major.minor` version, SWENG will have created a new repo in Cloudsmith, which will need the customer tokens migrated from an existing repo. Then update support customers that this new private repo exists.
 - [ ] ***(Support)*** Update tickets in case of waiting for support customers.
 - [ ] ***(Support)*** Inform Marketing of the release.
 - [ ] ***(Marketing)*** If a new Cloudsmith repository is used, update the Zapier scripts.
 - [ ] ***(Marketing)*** Upload Premium hooks tarball to SendOwl. Create a new product if a new branch, otherwise update existing product. Send notifications to existing subscribers of the new version.
 - [ ] ***(Marketing)*** Announce on social media.
 - [ ] ***(Marketing)*** Update [Wikipedia entry for Kea](https://en.wikipedia.org/wiki/Kea_(software)).
 - [ ] ***(Marketing)*** Write blog article (if a major release).
 - [ ] ***(Marketing)*** Update [Kea page on web site if any new hooks](https://www.isc.org/kea/).
 - [ ] ***(Marketing)*** Update Kea Premium and Kea Subscription data sheets if any new hooks.
 - [ ] ***(Marketing)*** Update [significant features matrix](https://kb.isc.org/docs/en/aa-01615) (if any significant new features).
 - [ ] ***(Marketing)*** Update [Kea documentation page in KB](https://kb.isc.org/docs/en/kea-administrator-reference-manual).
