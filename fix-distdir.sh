#!/bin/sh
#
# Removed the dependency of the distdir target on BUILT_SOURCES
# This is added by automake >= 1.16 but makes dist* targets to
# require prior build of the message compiler

if grep -q 'distdir: $(BUILT_SOURCES)' $1 ; then
   sed 's/distdir: $(BUILT_SOURCES)/distdir:/' < $1 > /tmp/fix-distdir-temp
    mv /tmp/fix-distdir-temp $1
fi
exit 0

