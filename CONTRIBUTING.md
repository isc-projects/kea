# Kea Contributor's Guide

So you found a bug in Kea or plan to develop an extension and want to send us a patch? Great! This
document will explain how to contribute your changes smoothly.

Here's a quick list of how to contribute a patch:

1. **create account** on [gitlab](https://gitlab.isc.org)
2. **open an issue** in [Kea project](https://gitlab.isc.org/isc-projects/kea/issues/new), make sure
   it describes what you want to fix and **why**
3. **ask someone from the ISC team to give you permission to fork Kea** (ask @tomek, @vicky, @ondrej
   or @godfryd or basically anyone from the Kea dev team)
4. **fork Kea code**: go to Kea project page, click [Fork button](https://gitlab.isc.org/isc-projects/kea/forks/new).
   If you can't, you didn't complete step 3.
5. **Implement your fix or feature, push code** to your repo. Make sure it compiles, has unit-tests,
   is documented and does what it's supposed to do.
6. **Open Merge Request**: go to Kea project [merge requests page](https://gitlab.isc.org/isc-projects/kea/merge_requests),
   click [New merge request](https://gitlab.isc.org/isc-projects/kea/merge_requests/new). If you
   don't see the button, you didn't complete step 3.
7. **Participate in the code review**: Once you submit the MR, someone from ISC will eventually get
   to the issue and will review your code. Please make sure you respond to comments. It's likely
   you'll be asked to update the code.

For a much more detailed description with details, see the sections below.

## Ideas for beginners

If you're not an experienced C++ programmer, you can still help Kea in many ways. To help newcomers get
involved in the project, we try to mark easy tickets with `beginner` label. Examples of such tasks may be
elimination of compilation warnings, adding or fixing logging messages, improving the build
system to not leave unnecessary files, conduct some experiments and improve documentation. You can see the
list of all tickets with that label [here](https://gitlab.isc.org/isc-projects/kea/-/issues?scope=all&utf8=%E2%9C%93&state=opened&label_name[]=beginner).

Don't be discouraged if a ticket that looks interesting to you is not marked for beginners. It may require
a bit of DHCP protocol or C++ programming knowledge, but they're definitely all doable. If in doubt, ask on
[kea-dev](https://lists.isc.org/mailman/listinfo/kea-dev) list for suggestions or guidance.

## A bit of a legal warning

With the modern open source movement, it is very easy to contribute patches and people often don't think
about the legal implications. Is the code you're about to contribute really yours? If you work
for a company and you developed it during your work hours, it's likely to be owned by the company you work
for. Are they OK with you contributing this? Are they OK with the fact that this will be open source and other
users and companies, even possibly a competitor, may use it?

Kea adopted Developer Certificate of Origin, which is a nice half a page document by Linux foundation. You can
read it on [developercertificate.org page](https://developercertificate.org/). By contributing your patch, you confirm that you follow
and agree with DCO.

Here's the text:

```
Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```

## Writing a patch

Before you start working on a patch or a new feature, it is a good idea to discuss it first with Kea
developers.  You can post your questions to the [kea-dev](https://lists.isc.org/mailman/listinfo/kea-dev)
or [kea-users](https://lists.isc.org/mailman/listinfo/kea-users) mailing lists. The kea-users is
intended for users who are not interested in the internal workings or development details of Kea: it
is OK to ask for feedback regarding new design or the best proposed solution to a certain
problem. This is the best place to get user's feedback. The internal details, questions about the
code and its internals are better asked on kea-dev.

OK, so you have written a patch? Great! Before you submit it, make sure that your code
compiles. This may seem obvious, but there's more to it. You have surely checked that it compiles on
your system, but Kea is a portable software. Besides Linux, it is compiled and used on relatively
uncommon systems like OpenBSD. Will your code compile and work there? What about endianness? It is
likely that you used a regular x86 architecture machine to write your patch, but the software is
expected to run on many other architectures, such as arm64. You may take a look at [system specific build
notes](https://kb.isc.org/docs/installing-kea).

### Coding guidelines

Does your patch conform to [Kea coding
guidelines](https://gitlab.isc.org/isc-projects/kea/wikis/coding-guidelines)?  You can submit a
patch that does not adhere to them, but that will reduce its chances of being accepted.  If the
deviations are minor, one of the Kea engineers who does the review will likely fix the issues.
However, if there are lots of issues, the reviewer may simply reject the patch and ask you to fix it
before re-submitting.

Placed in the root of the repository are files that formally describe the coding
guidelines above as close as possible. They are `.clang-format` and
`.uncrustify.cfg` used by `clang-format` and `uncrustify` respectively. If you
want to format code automatically, you will need to have at least one of these
tools installed. Since by default, these tools look for the closest style file
located in one of the parent directories or, otherwise, in a default location,
there are a couple of helpful scripts i.e. `./tools/clang-format.sh` and
`./tools/uncrustify.sh` to assure you that the Kea-owned file is used. They
accept any number of customized parameters that would be passed to the
underlying tool followed by any number of files and/or directories. Passing
directories will have all non-generated C++ files under it formatted.

IDEs often offer support for code formatting tools. For example, in Visual
Studio Code, you may install `Clang-Format` and `crustless` through the Command
Palette (`Ctrl + Shift + P` by default), `Extensions: Install Extensions`.
Then open a source file, select code that you want formatted, open the Command
Palette, and choose `Format Selection`. You might go through an onboarding step
where you choose the formatter in the case you have both installed, but that
should be it.

When using these tools, it can be tempting to format entire files at once. In
the interest of preserving git history as much as possible, it is recommended
that you only format code that you have added or changed. This is much easier
done in an IDE, but as long as the tool supports it, it can be done using the
provided scripts e.g.:

```bash
./tools/clang-format.sh --lines=13:37 ./src/lib/dhcpsrv/alloc_engine.cc
```

Uncrustify does not seem to have a line-range-limiting option at the time of
this writing.

## Running unit-tests

One of the ground rules in Kea development is that every piece of code has to be tested. We now have
an extensive set of unit-tests for almost every line of code. Even if you are fixing something
small, like a single line fix, you are encouraged to write unit-tests for that change. That is even
more true for new code: if you write a new function, method or a class, you definitely should write
unit-tests for it.

To ensure that everything is tested, ISC uses a development method called [Test Driven Development
(TDD)](https://en.wikipedia.org/wiki/Test-driven_development). In TDD, a feature is developed
alongside the tests, preferably with the tests being written first. In detail, a test is written for
a small piece of functionality and run against the existing code. (In the case where the test is a
unit test for a function, it would be run against an empty (unimplemented) function.) The test
should fail.  A minimal amount of code is then written, just enough to get the test to pass. Then
the process is repeated for the next small piece of functionality. This continues until all the
functionality has been implemented.

This approach has two advantages:

 - By writing a test first and then only enough code to pass the test, that code is fully tested. By
   repeating this process until the feature is fully implemented, all the code gets test
   coverage. You avoid the situation where not enough tests have been written to check all the
   code.

 - By running the test before the code implementing the function is written and observing the test
   fail, you can detect the situation where a bug in the test code will cause it to pass regardless
   of the code being tested.

Initially, some people unfamiliar with that approach react with "but my change is simple and I
tested that it works". That approach is both insufficient and short-sighted. It is insufficient,
because manual testing is by definition laborious and can't really be done on the multitude of
systems we run Kea on. It is short-sighted, because even with your best intentions you will not be
able to dedicate any significant amount of time for repeated testing of your improved code. The old
ISC DHCP has two decades of history behind it and we hope to make Kea last similar time span. Over
such long periods, code tends to be refactored several times. The change you made may be affected by
some other change or by the code that hasn't been written yet.

See Building Kea with Unit Tests for instructions on how to run unit-tests. If you happen to touch
any database related code, make sure you compile your code with –with-mysql, –with-pgsql and/or
–with-cql as needed. For example, if you change something substantial, make sure the other
compilation options still work.

If you happen to add new files or have modified any Makefile.am files, it is also a good idea to
check if you haven't broken the distribution process:

```bash
make distcheck
```

There are other useful switches which can be passed to configure. It is always a good idea to use
`–enable-logger-checks`, which does sanity checks on logger parameters. Use `–-enable-debug` to
enable various additional consistency checks that reduce performance but help during development. If
you happen to modify anything in the documentation, use `–-enable-generate-docs`. If you are
modifying DHCP code, you are likely to be interested in enabling a non-default database backends for
DHCP. Note that if the backend is not enabled, the database-specific unit-tests are skipped.  To
enable the MySQL backend, use the switch `–with-mysql`; for PostgreSQL, use `–with-pgsql` and for
Cassandra use `--with-cql`. A complete list of all switches can be obtained with the command:

```bash
./configure --help
```

## Submitting Merge Request (also known as sending your patch the right way)

The first step in writing the patch or new feature should be to get the source code from our Git
repository.  The procedure is very easy and is [explained
here](https://gitlab.isc.org/isc-projects/kea/wikis/processes/gitlab-howto).  While it is possible
to provide a patch against the latest stable release, it makes the review process much easier if it
is for latest code from the Git master branch.

ISC uses [gitlab](https://gitlab.isc.org) to manage its source code. While we also maintain presence
on [github](https://github.com/isc-projects/kea), the process of syncing gitlab to github is mostly
automated and Kea devs rarely look at github.

ISC's gitlab has been a target for spammers in the past, so it is now set up defensively. In
particular, new users can't fork the code on their own and it requires someone from ISC to manually
grant the ability to fork projects.  Fortunately, this is easy to do and we glady do this for anyone
who asks and provides a good reason. "I'd like to fix bug X or develop feature Y" is an excellent
reason. The best place for asking is either kea-dev or asking in a comment in your issue. Make sure
you put a name tag (@tomek, @godfryd, @vicky or @ondrej). When you write a comment in an issue or
merge request and add a name tag on it, the user is automatically notified.

Once you fork the Kea code in gitlab, you have your own copy and you can commit your changes there
and push them to your copy of Kea repo. Once you feel that your patch is ready, go to Kea project
and [submit a Merge Request](https://gitlab.isc.org/isc-projects/kea/merge_requests/new).

If you can't access this link or don't see New Merge Request button on the [merge requests
page](https://gitlab.isc.org/isc-projects/kea/merge_requests), please ask on kea-dev and someone
will help you out.

## Send Pull Request on github

If you can't send the patch on gitlab, the next best preferred way is to send pull request (PR) on
[github](https://github.com/isc-projects/kea).

This is almost as good as sending MR on gitlab. The downside is that Kea devs don't look at github
too frequently, so it may be a while before we notice it. And when we do, the chances are we will be
busy with other things. With gitlab, your MR will stare at us the whole time, so we'll get round to
it much quicker. But we understand that there are some cases where people may prefer github over
gitlab.

See the excellent documentation on github: https://help.github.com/articles/creating-a-pull-request/
for details. In essence, you need github account (spam/hassle free, takes one minute to set
up). Then you can fork the Kea repository, commit changes to your repo and ask us to pull your
changes into official Kea repository. This has a number of advantages. First, it is made against a
specific code version, which can be easily checked with git log command. Second, this request pops
up instantly on our list of open pull requests and will stay there. The third benefit is that the
pull request mechanism is very flexible. Kea engineers (and other users, too) can comment on it,
attach links, mention other users etc. You as a submitter can augment the patch by committing extra
changes to your repository. Those extra commits will appear instantly in the pull request. This is
really useful during the review. Finally, Kea developers can better assess all open pull requests
and add labels to them, such as "enhancement", "bug", or "unit-tests missing". This makes our life
easier. Oh, and your commits will later be shown as yours in github history. If you care for that
kind of things, once the patch is merged, you'll be automatically listed as contributor and Kea will
be listed as project you have contributed to.

## If you really can't do MR on gitlab or PR on github...

Well, you are out of luck. There are other ways, but those are really awkward and the chances of
your patch being ignored are really high. Anyway, here they are:

- [create an issue in the Kea Gitlab](https://gitlab.isc.org/isc-projects/kea/issues/new) and attach
  your patch to it. Sending a patch has a number of disadvantages. First, if you don't specify the
  base version against which it was created, one of Kea developers will have to guess that or go
  through a series of trials and errors to find that out. If the code doesn't compile, the reviewer
  will not know if the patch is broken or maybe it was applied to incorrect base code. Another
  frequent problem is that it may be possible that the patch didn't include any new files you have
  added.  If we happen to have any comments that you as submitter are expected to address (and in
  the overwhelming majority of cases, we have), you will be asked to send an updated patch. It is
  not uncommon to see several rounds of such reviews, so this can get very complicated very
  quickly. Please don't add your issue to any milestone. Kea team has a process of going through
  issues unassigned to any milestone. Kea developers review new issues once a week and assign them
  to specific milestones. Please do not add issues to working milestones directly. Having an issue
  in gitlab ensures that the patch will never be forgotten and it will show up on our gitlab
  reports. It's not required, but much appreciated if you send a short note to the kea-dev mailing
  list explaining what you did with the code and announce the issue number.

- Send a patch to the kea-dev list. This is the third preferred method, if you can't or don't want
  to use gitlab and github. If you send a patch to a mailing list in a wrong time, e.g. shortly
  before a release, Kea developers may miss it or perhaps they will see it and then forget about
  it. Nevertheless, it is still doable and we successfully accepted patches that way. It just takes
  more time from everyone involved, so it's a slower process in general.

- Send a tarball with your modified code. This is really the worst way one can contribute a
  patch. It has a number of disadvantages. In particular, someone will need to find out which
  version the code was based on and generate the patch. It's not rocket science, but it may be a
  very mundane thing to do if the Kea developer does not know the version in advance. The mailing
  list has a limit on the message size (for good reasons), so you'll likely need to upload it
  somewhere first. Kea developers often don't pick up new issues instantly, so it may have to wait
  weeks before the tarball is looked at. The tarball does not benefit from most of the advantages
  mentioned for github, like the ability to easily update the code, have a meaningful discussion or
  see what the exact scope of changes are. Nevertheless, if we given a choice of getting a tarball
  or not getting a patch at all, we prefer tarballs. Just keep in mind that processing a tarball is
  really cumbersome for Kea developers, so it may take significantly longer than other ways.

## Going through a review

Once you make your patch available using one of the ways above, the action is on one of the Kea
developers. We need an issue. While we can create it on our own, we prefer the original submitter
fill them in as he or she has the best understanding of the purpose of the change and may have any
extra information about OS, version, why it was done this specific way etc. If there is no MR and no
gitlab issue, you risk the issue not showing up on ISC radars. Depending on the subjective
importance and urgency as perceived by the ISC engineer, the issue or PR will be assigned to one of
the milestones.

Sooner or later, one of Kea developers will do the review. Here's the tricky part. One of Kea
developers will review your patch, but it may not happen immediately. Unfortunately, developers are
usually working under a tight schedule, so any extra unplanned review work may take a while. Having
said that, we value external contributions very much and will do whatever we can to review patches
in a timely manner. Don't get discouraged if your patch is not accepted after first review. To keep
the code quality high, we use the same review processes for external patches as we do for internal
code. It may take some cycles of review/updated patch submissions before the code is finally
accepted. The nature of the review process is that it emphasizes areas that need improvement. If you
are not used to the review process, you may get the impression that the feedback is negative.  It is
not: even the Kea developers seldom see reviews that say "All OK please merge".

Once the process is almost complete, the developer will likely ask you how you would like to be
credited.  The typical answers are by first and last name, by nickname, by company name or
anonymously. Typically we will add a note to the ChangeLog and also set you as the author of the
commit applying the patch and update the contributors section in the AUTHORS file. If the
contributed feature is big or critical for whatever reason, it may also be mentioned in release
notes.

Sadly, we sometimes see patches that are submitted and then the submitter never responds to our
comments or requests for an updated patch. Depending on the nature of the patch, we may either fix
the outstanding issues on our own and get another Kea developer to review them or the issue may end
up in our Outstanding milestone. When a new release is started, we go through the issues in
Outstanding, select a small number of them and move them to whatever the current milestone is. Keep
that in mind if you plan to submit a patch and forget about it. We may accept it eventually, but
it's much, much faster process if you participate in it.

#### Thank you for contributing your time and experience to the Kea project!
