---
name: A.B.C release checklist
about: Create a new issue using this checklist for each release.
---

# Kea Release Checklist

The Gitlab issue for this checklist can be created using QA script [create-release-checklist-gitlab-issue.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/create-release-checklist-gitlab-issue.py) with the advantage that it crosses out all the bullet points that do not apply to this release.
   * Example command: `GITLAB_TOKEN='...' ./create-release-checklist-gitlab-issue.py 1.2.3 'stable,security'`.

#### Legend

- `A.B.C`: the version being released

When you see the following marks, only do the task if the current release matches the marked release:

- <mark>🟩 Stable</mark>: the first release on a stable branch. `B` is an even number. `C` is 0. `Latest 🟩 Stable` means a version on the stable branch for which there is no other greater stable version.

- <mark>🟨 Maintenance</mark>: any release on a stable branch except the first. `B` is an even number. `C` is not 0.

- <mark>🏗️ Dev</mark>: any release from the `master` and `main` branches. `B` is an odd number.

- <mark>🟥 Security</mark>: any release that contains changes that were assigned a CVE number.

#### General Guidelines

- <mark>🟩 Stable or 🟨 Maintenance</mark>: Use dedicated Jenkins folder `kea-A-B` instead of `kea-dev`.

- <mark>🟩 Stable or 🟨 Maintenance</mark>: Run QA scripts from branch `vA_B` of `qa-dhcp` instead of `master`.

- <mark>🟥 Security</mark>: If releasing from the `master` branch, use `kea-cve` instead of `kea-dev`.

- <mark>🟥 Security</mark>: The release will be done from the `isc-private/kea` repo.

## Pre-Release Preparation (QA)

Some of these checks and updates can be made before the actual freeze.

1. [ ] <mark>🟥 Security</mark>: Should have been done when the CVE was discovered, but better late then never. Enable the kea-cve/build-tarball job.
1. [ ] <mark>🟥 Security</mark>: Should have been done when the CVE was discovered, but better late then never. Make sure mirroring is turned off for both Github and Gitlab [here](https://gitlab.isc.org/isc-projects/kea/-/settings/repository#js-push-remote-settings). To turn it off, run QA script [toggle-repo-mirroring.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/release/toggle-repo-mirroring.py) for both Kea and Forge \
   Example command: `GITLAB_TOKEN='...' ./toggle-repo-mirroring.py --off isc-projects/kea`.
   Example command: `GITLAB_TOKEN='...' ./toggle-repo-mirroring.py --off isc-projects/forge`.
1. [ ] <mark>🟩 Stable</mark>: Make sure that repositories and pipelines were created according to [the stable_release_preparation checklist](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/.gitlab/issue_templates/stable_release_preparation.md).
1. [ ] Check Jenkins results:
   1. [ ] Check Jenkins jobs for failures: [ut-dist](https://jenkins.aws.isc.org/job/kea-dev/job/ut-dist/), etc...
   1. [ ] Check [Jenkins Tests Report](https://jenkins.aws.isc.org/job/kea-dev/job/jenkins-tests-report/).
   1. [ ] Check [tarball check report](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/Kea_20Build_20Checks/)
1. [ ] <mark>🟨 Maintenance</mark>: Check if any changes in [kea-packaging repository](https://gitlab.isc.org/isc-projects/kea-packaging/) should be backported to the corresponding stable branch.
   1. [ ] Backport changes and link merge request with this issue.
1. [ ] <mark>🟨 Maintenance</mark>: Check if any changes in [Kea Docker repository](https://gitlab.isc.org/isc-projects/kea-docker) should be backported to the corresponding stable branch.
   1. [ ] Backport changes and link merge request with this issue.
1. [ ] Check [Performance Test Results](https://jenkins.aws.isc.org/job/kea-dev/job/performance/lastSuccessfulBuild/artifact/qa-dhcp/kea/performance-jenkins/report.html) in Jenkins for drops in performance.
1. [ ] Create a Gitlab issue for bumping up library versions and `KEA_HOOKS_VERSION` and notify developers.
   * You can use QA script [create-bump-up-lib-versions-gitlab-issue.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/create-bump-up-lib-versions-gitlab-issue.py)
   * Example command: `GITLAB_TOKEN='...' ./create-bump-up-lib-versions-gitlab-issue.py 1.2.3`.
   * In case of no developers available, it can be done by running: [./tools/bump-lib-versions.sh](https://gitlab.isc.org/isc-projects/kea/-/blob/master/tools/bump-lib-versions.sh).
   * Example command: `./tools/bump-lib-versions.sh`
   * <mark>🟩 Stable</mark>: The target version needs to be provided. Call `./tools/bump-lib-versions.sh Kea-A.B.C` instead.
1. [ ] <mark>🟩 Stable</mark>: Update the table in SECURITY.md with the stable branch and the upcoming dev branch.
1. [ ] Look at the issue numbers in the commit descriptions. Add to ChangeLog a mention of any change with visible impact that had not been mentioned already.
1. [ ] If any changes have been made to database schemas, then:
   1. [ ] Check that a previously released schema has not been changed.
   1. [ ] Check that the additions to `dhcpdb_create.*sql`, and nothing more nor less than what was added in this release, is present in a `upgrade_*_to_*.sh.in` script that should also have been added in this release.
1. [ ] Create a draft of the release notes on the [Kea GitLab wiki](https://gitlab.isc.org/isc-projects/kea/-/wikis/home). It should be created under [the Release-Notes directory](https://gitlab.isc.org/isc-projects/kea/-/wikis/Release-Notes), like this one: <https://gitlab.isc.org/isc-projects/kea/-/wikis/Release-Notes/release-notes-2.3.4>.
    1. [ ] <mark>🟥 Security</mark>: Use the private Kea Gitlab wiki instead: <https://gitlab.isc.org/isc-private/kea/-/wikis/Release-Notes>.
1. [ ] Notify Tomek that the draft is ready to be redacted.
1. [ ] Check if ReadTheDocs can build Kea documentation. Alternatively, look for failures in emails if you know that the ReadTheDocs webhook is working.
   1. Trigger rebuilding docs on [readthedocs.org](https://readthedocs.org/projects/kea/builds) and wait for the build to complete.
1. [ ] <mark>🟩 Stable</mark>: A new Cloudsmith repo should have been created. Make sure access tokens have been synchronized from previous Cloudsmith repositories and to the [check-pkgs.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/pkgs-check/check-pkgs.py) QA tool.

The following steps may involve changing files in the repository.

1. [ ] <mark>🟥 Security</mark>: Sync release branches from public repository into private. Run QA script [sync-repos.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/release/sync-repos.py) for both Kea and Forge \
   Example command: `GITLAB_TOKEN='...' ./sync-repos.py --source-project isc-projects/kea --target-project isc-private/kea --branch master`.
   Example command: `GITLAB_TOKEN='...' ./sync-repos.py --source-project isc-projects/forge --target-project isc-private/forge --branch master`.
1. [ ] Run QA script [update-code-for-release.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/update-code-for-release.py) \
   Example command: `GITLAB_TOKEN='...' ./update-code-for-release.py 2.3.4 --repo-dir ~/isc/repos/kea/`. \
   Help: `GITLAB_TOKEN='...' ./update-code-for-release.py --help`. \
   <mark>🟩 Stable or 🟨 Maintenance</mark>: Run from branch `v*_*` of `qa-dhcp`. \
   <mark>🟥 Security</mark>: Pass the `--cve` parameter. \
   The script makes the following changes and actions:
      1. Runs [prepare_kea_release.sh](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/prepare_kea_release.sh) that:
         1. Adds release entries in ChangeLogs.
         1. Updates Kea version in `meson.build`.
         1. Updates copyright years in files that were changed in the current year.
         1. Sort messages in message files in alphabetical order.
         1. Regenerates message files headers.
         1. Merges changelog_unreleased to ChangeLog.
      1. Regenerates BNF grammar.
      1. Regenerates message documentation.
      1. Regenerates parsers using Bison from Docker
1. [ ] Run the script again with the `--upload-only` flag, which:
   1. Create an issue in GitLab for release changes in the kea repo.
   1. Creates branches and merge requests for kea and kea-premium.
   1. Commits the changes in both repos.
   1. Checks out created branches in both repos.
   1. Commits and pushes the changes to the GitLab server.
1. [ ] Check manually the User's Guide sections:
   1. [ ] Chapter 1. Introduction
      1. [ ] On what platforms are we running tests using Jenkins? Update `Supported Platforms` in `platforms.rst` and `SYSTEMS` in `hammer.py`.
      1. [ ] Did we add any additional 3rd party software? Update if needed.
      1. [ ] Is there a new tool installed in bin or sbin released this time? If yes, is it documented?
   1. [ ] Chapter 2. Quick Start
      1. [ ] Has the default installation process changed (for kea and hooks)? If yes, are those changes documented and highlighted in the release notes?
   1. [ ] Chapter 3. Installation
      1. [ ] Check installation hierarchy (this is also automatically checked at the end of [ut-extended job](https://jenkins.aws.isc.org/job/kea-dev/job/ut-extended/)).
      1. [ ] Check and update Build Requirements.
      1. [ ] Check configure options against what `meson configure` says.
1. [ ] Check ChangeLog entries in Kea main and premium: spelling, trailing whitespaces, etc.
1. [ ] Check AUTHORS, INSTALL, README files in Kea main and premium.
   - AUTHORS: update credits
   - README: check "provides" with Release Notes, User Guide (1.3 Kea Software)
1. [ ] If changes were made, commit them, push the branch to the main repository, and request a review. Once the changes have been approved, merge the MR to the master.

## Build selection, tarballs upload, and sanity checks (QA)

This is the last moment to freeze the code! :snowflake:

1. [ ] Go to [build-tarball](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/) Jenkins job and pick the last tarball built - it will be a release candidate.
1. [ ] Check tarball before requesting sanity checks from the development team.
   1. Download tarballs from the picked Jenkins build
   1. Check hook libraries.
      1. Are there any new hook libraries installed in this release?
         1. Are they in the proper tarball? Core or subscriber?
         1. Do they have their own package?
   1. Check sizes - is the new package reasonable?
   1. Check the installation tree, and compare it with the previous release
   1. Check installed libraries.
      1. which were updated? (save results)
      1. Do any of the libraries from the current release have a lower version than in the previous release?
   1. Uninstall Kea, and check what is left (there should be just configuration files)
   1. Check if each of the installed binaries has a man page.
      1. If not, is the binary included in the tarball? That might explain it.
      1. Are man pages up to date?
   1. Check if documentation is properly formatted and has correct versions and dates.
      1. It's advised to search for previous version numbers, some of them are statically added in statements that are no longer valid.
1. [ ] Upload tarballs to repo.isc.org using Jenkins and send sanity checks request.
   1. Go to [release-tarball-upload](https://jenkins.aws.isc.org/job/kea-dev/job/release-tarball-upload/) Jenkins job.
   1. Click `Build with Parameters`.
   1. In the field `Tarball`, select the picked tarball build.
   1. In the field `Pkg`, select the corresponding pkg job.
   1. In field `Release_Candidate` pick:
      1. `rc1` if this is the first selected build for release, it will push the selected tarballs to repo.isc.org, to a directory suffixed with indicated rc#
      1. next rc# if this is a respin after some fixes (note: it is not possible to pick the previous rc number - it will result in an error)
   1. [ ] <mark>🟥 Security</mark>: Tick the `CVE` parameter.
   1. Submit the job that will automatically:
      1. Upload the tarballs.
      1. Create a GitLab issue for sanity checks. Put the announcement there.
      1. Send Sanity Checks announcement on the Kea/DHCP channel on Mattermost.\
         The announcement includes:
         - a link to chapter 4 Sanity Checks of the release process: [KeaReleaseProcess - SanityChecks](https://wiki.isc.org/bin/view/QA/KeaReleaseProcess#4.%20Sanity%20Checks)
         - a link to the GitLab issue
         - tarballs locations with SHA256 checksums
         - apk, deb, rpm packages locations and versions
1. [ ] Upload packages to the testing Cloudsmith repos.
   1. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
   1. Click `Build with Parameters`.
   1. Pick the latest pkg build in the `Packages` field, and the corresponding tarball build in the `Tarball` field. Set `PrivPubRepos: "both"`. Leave the rest as they are: `TarballOrPkg: "packages"`, `TestProdRepos: "testing"` and click `Build`.
   1. [ ] <mark>🟥 Security</mark>: Tick the `CVE` parameter.
1. [ ] Run Jenkins job [releases-pkgs-check](https://jenkins.aws.isc.org/job/kea-dev/job/release-pkgs-check/) on the packages uploaded to the testing repos.

## Releasing Tarballs and Packages (QA)

Now it's time to publish the code.

1. [ ] Update Release Notes with ChangeLog entries.
1. [ ] Sanitize the release notes with script `sanitize-release-notes.sh` from kea.wiki. Review the output of `git diff --color-words`. If it looks good, commit and push.
    * Example: `./Release-Notes/sanitize-release-notes.sh release-notes-3.2.0.md`
1. Mark Jenkins jobs with release artifacts to be kept forever and update description of build by adding there version of released Kea `Kea-A.B.C`).
    * Go to the following Jenkins jobs, click release build and then, on the build page, click `Keep this build forever` button and edit the description:
        1. [ ] [build-tarball](https://jenkins.aws.isc.org/job/kea-dev/job/build-tarball/).
        1. [ ] [pkg job](https://jenkins.aws.isc.org/job/kea-dev/job/pkg/).
1. [ ] Confirm with Tomek that the release notes are ready.
1. [ ] Notify Marketing that the release notes are ready for review.
1. [ ] Create a signed tag. Run QA script [sign-tag.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/release/sign-tag.py) for project `isc-projects/kea`.
    1. [ ] <mark>🟥 Security</mark>: Run it for project `isc-private/kea` instead.
    * It will create tags automatically for other repos of interest too.
    * <mark>🟩 Stable</mark>: It will also create stable branches.
    * Example command: `./sign-tag.py --project isc-projects/kea --tag Kea-2.3.4 --branch master --key 0259A33B5F5A3A4466CF345C7A5E084CACA51884`
    * To get the fingerprint, run `gpg --list-keys wlodek@isc.org`.
1. [ ] Upload final tarballs & release notes to repo.isc.org.
    1. Go to [release-tarball-upload](https://jenkins.aws.isc.org/job/kea-dev/job/release-tarball-upload/) Jenkins job.
    1. Click `Build with Parameters`.
    1. In the field `Tarball`, select the picked tarball build.
    1. In the field `Pkg`, select the corresponding pkg job.
    1. In the field `Release_Candidate`, pick `final`. This job will also:
       - Open an issue on [the signing repository](https://gitlab.isc.org/isc-private/signing/-/issues) for signing final tarballs on repo.isc.org.
       - Create Gitlab releases `Kea-A.B.C` in Kea main and premium repositories.
    1. [ ] <mark>🟥 Security</mark>: Tick the `CVE` parameter.
1. [ ] Sign the tarballs. Run QA script [sign_kea_and_upload_asc.sh](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/sign_kea_and_upload_asc.sh).
    * Example command: `./sign_kea_and_upload_asc.sh 2.3.4 wlodek 0259A33B5F5A3A4466CF345C7A5E084CACA51884`
    * To get the fingerprint, run `gpg --list-keys wlodek@isc.org`.
    * Fallback if it does not work:
        1. Download the tarballs from `repo.isc.org:/data/shared/sweng/kea/releases/x.y.z/*-x.y.z.tar.gz`.
        1. Sign them.
        1. Upload the public signature at `/data/shared/sweng/kea/releases/x.y.z/*-x.y.z.tar.gz.asc`.
1. [ ] Confirm that the tarballs have the checksums mentioned on the signing ticket.
    * Example command: `ssh repo.isc.org 'sha256sum /data/shared/sweng/kea/releases/*2.3.4/*.tar.xz'`
1. [ ] <mark>🟥 Security</mark>: Wait for clearance from Incident Manager to proceed with the private release. Usually on T-5.
1. [ ] Login to repo.isc.org and upload the final tarball to public ftp using the make-available script.
    * [ ] <mark>🟥 Security</mark>: Pass the `--private` flag instead of `--public` even for the core tarball. Save the links. Put them in the CVE ticket as an internal note.
    * [ ] For the subscriber tarball, run again with the `--private` flag instead of `--public`.
    * Example commands:
      * `make-available --public --symlink=cur/2.3 /data/shared/sweng/kea/releases/2.3.4`
      * `make-available --private --symlink=cur/2.3 /data/shared/sweng/kea/releases/subscriber-2.3.4`
    * For more information, use the `--debug` option.
    * To overwrite existing content, use `--force` option.
    * If you made a mistake, contact ASAP someone from the ops team to remove incorrectly uploaded tarballs.
    * [ ] Save the link to the subscriber tarball and put it into the signing ticket as a comment.
1. Upload final APK, DEB & RPM packages, tarballs and signature files to cloudsmith.io:
    1. [ ] If you uploaded packages to testing repo previously, you can copy them over instantaneously. Run script [copy-packages-between-cloudsmith-repos.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/repo-management/copy-packages-between-cloudsmith-repos.py) \
        * Example commands:
            * `./copy-packages-between-cloudsmith-repos.py -v 2.3.4 --from kea-dev-testing --to kea-dev`
            * `./copy-packages-between-cloudsmith-repos.py -v 2.3.4 --from kea-dev-prv-testing --to kea-dev-prv --premium`
        1. [ ] <mark>🟥 Security</mark>: Use only the premium run from the second example, since the core tarballs should also be in the private repo. You could run the command on the core repos too, but it shouldn't do anything.
        1. [ ] Remember to upload tarballs too. Run [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/) with `TarballOrPkg: "tarballs"`. The other parameters should be: `PrivPubRepos: "both"`, `TestProdRepos: "production"`. Click `Build`.
            1. [ ] <mark>🟥 Security</mark>: Tick the `CVE` parameter.
    1. [ ] If you did not upload packages to testing repo previously, start a new upload. Go to [release-upload-to-cloudsmith](https://jenkins.aws.isc.org/job/kea-dev/job/release-upload-to-cloudsmith/).
        1. Click `Build with Parameters`.
        1. Pick your selected pkg build in the `Packages` field, the corresponding tarball build in the `Tarball` field, `PrivPubRepos: "both"`, `TarballOrPkg: "both"`, `TestProdRepos: "production"` and click `Build`.
            - This step also verifies sign files.
        1. [ ] <mark>🟥 Security</mark>: Tick the `CVE` parameter.
1. [ ] Run Jenkins job [releases-pkgs-check](https://jenkins.aws.isc.org/job/kea-dev/job/release-pkgs-check/) on the packages uploaded to the production repo.
1. [ ] <mark>🟥 Security</mark>: Wait for public disclosure. Confirm with the Incident Manager that the disclosure is done.
1. [ ] <mark>🟥 Security</mark>: Run make-available again with `--public` instead of `--private` for the core tarball.
1. [ ] <mark>🟥 Security</mark>: Copy public packages from `-prv` Cloudsmith repo to public.
    * You can use script [copy-missing-public-packages-between-cloudsmith-repos.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/repo-management/copy-missing-public-packages-between-cloudsmith-repos.py) \
      Example command: `./copy-missing-public-packages-between-cloudsmith-repos.py -v 2.3.4`.
    * Or you can use the Cloudsmith GUI. Consider using the filter from the script in the previous bullet point.
1. [ ] Build and upload Docker images to Cloudsmith. Run Jenkins job [build-upload-docker](https://jenkins.aws.isc.org/job/kea-dev/job/build-upload-docker/).
    * Make sure the right package job is selected under `Packages`.
    * Tick `Upload`.
    * Change `TestProdRepos` to `production`.
    * Leave `versionTag` ticked.
    * Leave `versionDateTag` ticked.
    * <mark>Latest 🟩 Stable</mark>: Tick `latestTag`.
    * Press `Build`.
1. [ ] <mark>🟥 Security</mark>: Sync release branches from private repository into public. Run QA script [sync-repos.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/release/sync-braches.py) \
   Example command: `GITLAB_TOKEN='...' ./sync-repos.py --source-project isc-private/kea --target-project isc-projects/kea --branch master`.
   Example command: `GITLAB_TOKEN='...' ./sync-repos.py --source-project isc-private/forge --target-project isc-projects/forge --branch master`.
   1. [ ] It will create issues and merge requests. Ask for review. You could also check that the hashes on the latest commit match for the private and the public repo. In that case, it's safe to say the code is identical and you could merge without review (since it's somewhat time-sensitive because you require this step to regenerate docs on ReadTheDocs).
1. [ ] <mark>🟥 Security</mark>: Tags need to be synced. There isn't a script for this yet. Here is how you can do it manually (change tag name accordingly):
  ```
  git clone git@gitlab.isc.org:isc-private/kea.git
  cd kea
  git remote add public git@gitlab.isc.org:isc-projects/kea.git
  git remote update
  git pull --tags
  git push Kea-2.3.4 public
  ```
1. [ ] <mark>🟥 Security</mark>: Gitlab Releases were not created on public repo because of missing tags. A quick way to create them is to run [add-missing-releases.sh](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/add-missing-releases.sh)
1. [ ] <mark>Latest 🟩 Stable</mark>: Recreate the `stable` tag. Go to [the stable tag](https://gitlab.isc.org/isc-projects/kea/-/tags/stable), click `Delete tag`, then `New tag`, `Tag name`: `stable`, `Create from`: `Kea-A.B.C`.
1. [ ] Update docs on <https://app.readthedocs.org/projects/kea/>.
    1. Click `Add version` -> click `Resync versions` at the bottom -> click on the `Search versions` search bar -> find the tag name in the dropdown menu -> toggle `Active` -> click `Update version`. Wait for the build to complete.
    1. [ ] <mark>Latest 🟩 Stable</mark>: Rebuild the `stable` version. Go to [the stable build](https://app.readthedocs.org/projects/kea/builds/?version__slug=stable), click `Rebuild version`.
1. [ ] <mark>🟥 Security</mark>: Copy release notes from the private Kea wiki to the public Kea wiki.
1. [ ] <mark>🟩 Stable or 🏗️ Dev</mark>: Bump up versions. Run QA script [bump-up-versions-post-release.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/kea/release/bump-up-versions-post-release.py).
   1. [ ] Check if the changes in the `kea-clone` directory that the script created look good.
   1. [ ] Return to the working directory where you called the script from.
   1. [ ] Run again with `--upload-only` which will create an issue and a merge request.
   1. [ ] Ask for review, and eventually and hopefully merge.
1. [ ] Contact the Marketing team, and find a member who will continue work on this release:
    1. [ ] Assign this ticket to the person who will continue.
    1. [ ] Share the link to signing the ticket either directly or as a comment in this issue.

## Marketing

1. [ ] Write blog article (if a major release).
1. [ ] Check that the tarballs are available on Cloudsmith. The downloads page points to downloads.isc.org now, but for packages and especially subscriber-only hooks, users must install from Cloudsmith.
1. [ ] Publish links to downloads on the ISC website. Update release dates and check EOL dates.
1. [ ] <mark>🟥 Security</mark>: Update the security releases version table in the downloads data file on the website. This information is used by Stork to flag new security versions.
1. [ ] <mark>🟩 Stable</mark>: If it is a new `major.minor` version, SWENG will have created a new repo in Cloudsmith, which will need the customer tokens migrated from an existing repo. Verify that the KB on installing from Cloudsmith has also been updated. When posting a new Stable major version, you will also need to update the Cloudsmith repo location on the downloads page.
   * If the tokens were not migrated, contact QA team and coordinate fix.
1. [ ] Announce release to support subscribers using the read-only Kea Announce queue, if a major version or other significant change to stable version.  Note that this announcement is different from the public announcement because you want to include the -prv repo information for the subscription hooks.
1. [ ] Send announcement email to _kea-announce_. Highlight breaking changes, if any. NB - we use Printing press for this now.
1. [ ] Update "Release Schedule" document in RT with current versions and next planned release.
1. [ ] Send announcement email to _kea-users_ (if a major release). Highlight breaking changes, if any.
1. [ ] Announce on social media.
1. [ ] Update [Wikipedia entry for Kea](https://en.wikipedia.org/wiki/Kea\_(software)).
1. [ ] Update [Kea page on website if any new hooks](https://www.isc.org/kea/).
1. [ ] Update Kea Subscription data sheet if any new hooks.
1. [ ] Update [significant features matrix](https://kb.isc.org/docs/en/aa-01615) (if any significant new features).
1. [ ] Contact Support team, find a person who will continue this release and assign this issue to them.

## Support

1. [ ] Update tickets if any support customers are waiting for the release. [:link:](https://wiki.isc.org/bin/view/Main/KeaReleaseSupportUpdateTix)

## QA

1. [ ] <mark>🟥 Security</mark>: Disable the kea-cve/build-tarball job.
1. [ ] <mark>🟥 Security</mark>: Mirroring can be turned back on for both Github and Gitlab. You an check it [here](https://gitlab.isc.org/isc-projects/kea/-/settings/repository#js-push-remote-settings). To turn it on, run QA script [toggle-repo-mirroring.py](https://gitlab.isc.org/isc-private/qa-dhcp/-/blob/master/release/toggle-repo-mirroring.py) for both Kea and Forge \
   Example command: `GITLAB_TOKEN='...' ./toggle-repo-mirroring.py --on isc-projects/kea`.
   Example command: `GITLAB_TOKEN='...' ./toggle-repo-mirroring.py --on isc-projects/forge`.
1. [ ] Close the signing ticket.
1. [ ] Close this ticket.
