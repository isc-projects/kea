---
name: a.b.c release checklist
about: Create a new issue using this checklist for each release.
---

# Kea Release Checklist

This is thoroughly documented in [the Kea Release Process guide](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess).

## Pre-Release Preparation

Some of these checks and updates can be made before the actual freeze. For new stable releases or maintenance releases, please don't use the `kea-dev` build farm; use a dedicated build farm for each release cycle.

1. [ ] Check Jenkins results:
   1. [ ] Check Jenkins jobs for failures: [distcheck](https://jenkins.aws.isc.org/job/kea-dev/job/distcheck/), etc...
   1. [ ] Check [Jenkins Tests Report](https://jenkins.aws.isc.org/job/kea-dev/job/jenkins-tests-report/).
   1. [ ] Check [tarball check report](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/Kea_20Build_20Checks/)
1. [ ] Check [Performance Test Results](https://jenkins.aws.isc.org/job/kea-dev/job/performance/lastSuccessfulBuild/artifact/qa-dhcp/kea/performance-jenkins/report.html) in Jenkins for drops in performance.
1. [ ] Create a Gitlab issue for bumping up library versions and `KEA_HOOKS_VERSION` and notify developers.
   * In case of no developers available, it can be done by running: [./tools/bump-lib-versions.sh](https://gitlab.isc.org/isc-projects/kea/-/blob/master/tools/bump-lib-versions.sh) Kea-q.w.e Kea-a.b.c (where `a.b.c` is the version to be released and `q.w.e` is the version previous to that).
1. [ ] Look at the issue numbers in commit descriptions. Add to ChangeLog a mention about any change with visible impact that had not been mentioned already.
1. [ ] If any changes have been done to database schemas, then:
   1. [ ] Check that a previously released schema has not been changed.
   1. [ ] Check that the additions to `dhcpdb_create.*sql`, and nothing more nor less than what was added in this release, is present in a `upgrade_*_to_*.sh.in` script that should also have been added in this release.
1. [ ] Prepare release notes.
   1. [ ] Create release note on Kea GitLab wiki and notify @tomek. It should be created under the `Release-Notes` directory, like this one: https://gitlab.isc.org/isc-projects/kea/-/wikis/Release-Notes/release-notes-2.3.4
   1. [ ] Finish release notes and conduct its review.
   1. [ ] Notify support that release notes are ready for review. To avoid conflicts in edits wait with next step after review is done.
   1. [ ] Notify @sgoldlust or @vicky that release notes are ready for review. Due to time difference please do this at least 36 hours before planned release.
1. [ ] Check that packages can be uploaded to cloudsmith.
   1. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
   1. Click `Build with Parameters`.
   1. Pick the latest pkg build in the `Packages` field, and the corresponding tarball build in the `Tarball` field, leave the rest as they are `PrivPubRepos: "private"`, `TarballOrPkg: "packages"`, `TestProdRepos: "testing"` and click `Build`.
   1. If a new Cloudsmith repository is used, then:
      1. [ ] Make sure freeradius packages are uploaded to the Cloudsmith repository or copied from a previous repository.
      1. [ ] Make sure access tokens have been synchronized from previous Cloudsmith repositories and to the [check-pkgs.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/pkgs-check/check-pkgs.py) QA tool.
1. [ ] Check if ReadTheDocs can build Kea documentation. Alternatively, look for failures in emails if you know that the ReadTheDocs webhook is working.
   1. Trigger rebuilding docs on [readthedocs.org](https://readthedocs.org/projects/kea/builds) and wait for the build to complete.

The following steps may involve changing files in the repository.

1. [ ] Run [update-code-for-release.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/build/update-code-for-release.py) \
   Example command: `GITLAB_TOKEN='...' ./update-code-for-release.py 2.3.4 --repo-dir ~/isc/repos/kea/`. \
   Help: `GITLAB_TOKEN='...' ./update-code-for-release.py --help`. \
   The script requires an explicit flag for stable and maintenances releases e.g. `--repo-branch v2_4`. \
   The script makes the following changes and actions:
   1. Runs [prepare_kea_release.sh](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/build/prepare_kea_release.sh) that:
      1. Adds release entries in ChangeLogs.
      1. Updates Kea version in configure.ac.
      1. Updates copyright years in files that were changed in current year.
      1. Sorts message files.
      1. Regenerates message files headers.
   1. Regenerates parsers using Bison from Docker
1. [ ] Run the script again with the `--upload-only` flag which:
   1. Creates an issue in GitLab for release changes in kea repo.
   1. Creates branches and merge requests for kea and kea-premium.
   1. Commits the changes in both repos.
   1. Checks out created branches in both repos.
   1. Commits and pushes the changes to GitLab server.
1. [ ] Check manually User's Guide sections:
   1. [ ] Chapter 1. Introduction
      1. [ ] On what platforms we are running tests using Jenkins? Update Supported Platforms in platforms.rst file.
      1. [ ] Did we add any additional 3rd party software? Update if needed.
      1. [ ] Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
   1. [ ] Chapter 2. Quick Start
      1. [ ] Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
   1. [ ] Chapter 3. Installation
      1. [ ] Check installation hierarchy (this is also automatically checked at the end of [ut-extended job](https://jenkins.aws.isc.org/job/kea-dev/job/ut-extended/)).
      1. [ ] Check and update Build Requirements.
      1. [ ] Check configure options against what `./configure -h` says.
1. [ ] Check ChangeLog entries in Kea main and premium: spelling, trailing whitespaces, etc.
1. [ ] Check AUTHORS, INSTALL, README files in Kea main and premium.
   - AUTHORS: update credits
   - README: check "provides" with Release Notes, User Guide (1.3 Kea Software)
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
      1. Upload the tarballs.
      1. Create a GitLab issue for sanity checks, put the announcement there.
      1. Send Sanity Checks announcement on the Kea/DHCP channel on Mattermost.\
         The announcement includes:
         - a link to chapter 4 Sanity Checks of the release process: [KeaReleaseProcess - SanityChecks](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess#4.%20Sanity%20Checks)
         - a link to the GitLab issue
         - tarballs locations with SHA256 checksums
         - rpm/deb packages locations and versions

## Releasing Tarballs and Packages

Now it's time to publish the code.

 1. [ ] Update Release Notes with ChangeLog entries.
 1. [ ] Mark Jenkins jobs with release artifacts to be kept forever and update description of build by adding there version of released kea (e.g. `Kea-2.3.4`).
    1. Go to the following Jenkins jobs, click release build and then, on the build page, click `Keep this build forever` button and edit description:
       1. [build-tarball](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/).
       1. [pkg job](https://jenkins.aws.isc.org/job/kea-dev/job/pkg/).
 1. [ ] Upload final tarballs to repo.isc.org.
    1. Go to [release-tarball-upload](https://jenkins.aws.isc.org/job/kea-dev/job/release-tarball-upload/) Jenkins job.
    1. Click `Build with Parameters`.
    1. In field `Tarball` select picked tarball build.
    1. In field `Pkg` select the corresponding pkg job.
    1. In field `Release_Candidate` pick `final`. This job will also:
       - Open an issue on [the signing repository](https://gitlab.isc.org/isc-private/signing/-/issues) for signing final tarballs on repo.isc.org.
       - Create Git tags `Kea-a.b.c` in Kea main and premium repositories.
       - Create Gitlab releases `Kea-a.b.c` in Kea main and premium repositories.
 1. [ ] Sign tarballs with the personal key, by running [sign_kea_and_upload_asc.sh](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/build/sign_kea_and_upload_asc.sh) which signs, verifies signatures and uploads them.
    - If release engineer does NOT have signing key, please contact team member.
 1. [ ] Confirm that the tarballs have the checksums mentioned on the signing ticket.
 1. [ ] Wait for clearance from Security Officer to proceed with the public release (if applicable). If this is a security release, next steps will be impacted by CVE checklist.
 1. [ ] Login to repo.isc.org and upload final tarball to public ftp using make-available script (only OPS can remove incorrectly uploaded tarballs).
    * [ ] For premium tarballs use `--private` option.
      * For newest stable release use `--symlink=cur` option.
      * Example command: `make-available --public --symlink=cur /data/shared/sweng/kea/releases/2.3.4`.
    * [ ] save links to all premium tarballs and put them into signing ticket as a comment.
 1. [ ] Upload final RPM & DEB packages, tarballs and sign files to cloudsmith.io:
    1. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
    1. Click `Build with Parameters`.
    1. Pick your selected pkg build in the `Packages` field, the corresponding tarball build in the `Tarball` field, `PrivPubRepos: "both"`, `TarballOrPkg: "both"`, `TestProdRepos: "production"` and click `Build`.
       - This step also verifies sign files.
    1. When it finishes run check: [releases-pkgs-check](https://jenkins.aws.isc.org/job/kea-dev/job/release-pkgs-check/).
 1. [ ] Check that Docker images can be uploaded to Cloudsmith. Run [build-upload-docker](https://jenkins.aws.isc.org/job/kea-dev/job/build-upload-docker/).
    * Make sure the right package job is selected under `Packages`.
    * Tick `Upload`.
    * Leave `TestProdRepos` to `testing`.
    * Leave `versionTag` ticked.
    * Tick `latestTag` if this is a stable or a maintenance release.
    * If this is a stable or maintenance release, change `KeaDockerBranch` to the appropriate branch.
    * Press `Build`.
 1. [ ] Build and upload Docker images to Cloudsmith. Run [build-upload-docker](https://jenkins.aws.isc.org/job/kea-dev/job/build-upload-docker/) with the same actions as above except change `TestProdRepos` to `production`.
 1. [ ] Update ReadTheDocs:
    1. Trick ReadTheDocs into pulling the latest tags. Click `Build version` on [readthedocs.org](https://readthedocs.org/projects/kea/builds).
    1. Publish currently released version. On the `Versions` tab, scroll down to `Activate a version`, search for `kea-a.b.c` and click `Activate`.
    1. If it's a stable release, change the default version to point to this stable release. `Admin -> Advanced Settings -> Default version* -> Kea-a.b.c`.
 1. [ ] Create an issue and a merge request to bump up Kea version in `configure.ac` to next development version which could be, based on just released version `a.b.c`:
    * `a.b.z-git` where `z == c + 1` most of the time, or
    * `a.y.0-git` where `y == b + 2` if a new development series starts, or
    * `x.1.0-git` where `x == a + 1` when the released minor version `b` is 9 and `a.b.c` was the last version in the development series and a new development version is coming up next.
1. [ ] Contact Marketing team, and find a member who will continue work on this release:
    1. [ ] Assign this ticket to person who will continue.
    1. [ ] Share link to signing ticket either directly or as a comment in this issue.

## Marketing

1. [ ] Publish links to downloads on ISC website.
1. [ ] Update the supported versions document in the Salesforce portal (if there are stable versions released), and update the Kea document in the portal.
1. [ ] If it is a new `major.minor` version, SWENG will have created a new repo in Cloudsmith, which will need the customer tokens migrated from an existing repo. Verify that the KB on installing from Cloudsmith has also been updated, then update the Kea document in the SF portal and notify support customers that this new private repo exists.
1. [ ] If a new Cloudsmith repository is used, make sure that the Zapier scripts are updated.
   * If those are not updated, there was an error made during preparation for new stable release. Please contact QA team and coordinate fix.
1. [ ] Upload Premium hooks tarball to SendOwl. Create a new product if a new branch, otherwise update existing product. Send notifications to existing subscribers of the new version.
1. [ ] Write release email to _kea-announce_.
1. [ ] Write email to _kea-users_ (if a major release).
1. [ ] Announce on social media.
1. [ ] Update [Wikipedia entry for Kea](https://en.wikipedia.org/wiki/Kea\_(software)).
1. [ ] Write blog article (if a major release).
1. [ ] Update [Kea page on website if any new hooks](https://www.isc.org/kea/).
1. [ ] Update Kea Premium and Kea Subscription data sheets if any new hooks.
1. [ ] Update [significant features matrix](https://kb.isc.org/docs/en/aa-01615) (if any significant new features).
1. [ ] Contact Support team, find a person who will continue this release and assign this issue to them.

## Support

1. [ ] Update tickets in case of waiting for support customers.
1. [ ] Close this ticket