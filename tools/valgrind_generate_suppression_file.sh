#!/bin/sh

# shellcheck disable=SC2044
# SC2044 (warning): For loops over find output are fragile. Use find -exec or a while read loop.
# reason: They're fine. We don't use spaces in file names.

set -eu

# Print usage.
print_usage() {
  printf \
'Usage: %s {{options}}
Options:
  [-d|--debug]                 enable debug mode, showing every executed command
  [-k|--keep]                  do not remove meson generated files
  [-h|--help]                  print usage (this text)
' \
    "$(basename "${0}")"
}

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]             enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]              print usage (this text).
    '-h'|'--help') print_usage; exit 0 ;;

    # [-k|--keep]              do not remove meson generated files
    '-k'|'--keep') keep_files=true ;;

    # Unrecognized argument
    *)
    printf "ERROR: Unrecognized argument '%s'\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

# Default parameters
test -z "${keep_files+x}" && keep_files=false

# Script can be called from wherever, and it changes directory to repo root.
script_parent_dir=$(cd "$(dirname "${0}")" && pwd)
cd "${script_parent_dir}/.."

if test ! -d build; then
    echo "Directory 'build' not found, but it was expected. Did you run 'meson setup build'?"
    exit 1
fi

partial_suppression_files=$(find build -type f -name '*valgrind-supp-*' -and -not -name '*txt.supp*')
if test -z "${partial_suppression_files}"; then
    echo "No partial suppression files found. Did you run 'meson test -C build --setup valgrind_gen_suppressions'?"
    exit 1
fi

for i in ${partial_suppression_files}; do
    found=$(grep -c "<suppression>" "$i" || true)
    if [ "$found" -eq 0 ]; then
        continue
    fi
    # remove useless data
    xmlstarlet sel -t -v "/valgrindoutput/error/suppression/rawtext" "$i" | grep "\S" | sed 's/&lt;/</g; s/&gt;/>/g; s/&amp;/\&/g; s/&quot;/"/g; s/&apos;/'"'"'/g' >"$i-txt.supp"
    # extract the binary path and name
    found_in_path=$(xmlstarlet sel -t -v "/valgrindoutput/args/argv/exe" "$i" | sed "s|.*src|src|")
    # insert a comment with the binary path and name
    sed -i "s|<insert_a_suppression_name_here>|<insert_a_suppression_name_here>\n   # detected in $found_in_path|g" "$i-txt.supp"
    # split the file
    csplit -s -z -f "$i-txt.supp-part." "$i-txt.supp" '/{/' '{*}'
done

echo "" >build/valgrind_suppression.supp
for i in $(find build -type f -name '*txt.supp-part.*'); do
    # compute md5sum
    label=$(grep -v "insert_a_suppression_name_here" "$i" | grep -v "# detected in " | md5sum | cut -d " " -f 1)
    # update label
    sed -i "s/<insert_a_suppression_name_here>/valgrind_hash_$label/g" "$i"
    # check if hash is present
    match=$(grep -c "$label" build/valgrind_suppression.supp || true)
    if [ "$match" -eq 0 ]; then
        # include entire content if hash not present
        cat "$i" >>build/valgrind_suppression.supp
    else
        # extract the binary path and name
        found_in_path=$(grep " # detected in " "$i" || true)
        # update comment with binary path and name if hash not present
        sed -i "s|valgrind_hash_$label|valgrind_hash_$label\n$found_in_path|g" build/valgrind_suppression.supp
    fi
done
csplit -s -z -f build/valgrind_suppression.supp.part. build/valgrind_suppression.supp '/{/' '{*}'
for i in $(find build -type f -name '*valgrind_suppression.supp.part.*'); do
    name=$(grep "valgrind_hash_" "$i" | tr -d " ")
    if [ -z "$name" ]; then
        continue
    fi
    mv "$i" "build/$name"
done
cat <<EOF >build/valgrind_suppression.supp
# Valgrind suppressions file. Place permanent suppressions that we never
# want to reconsider again into this file. For temporary suppressions
# that we want to revisit in the future, use
# valgrind-suppressions.revisit.
#
# Don't add any "obj:" lines in suppressions as these are likely
# site-specific. Use "..." instead to match these. Look at the other
# suppressions as examples.
#
# In case you want to make sense of the following symbols, demangle them
# with a command like: c++filt < valgrind-suppressions
EOF
for i in $(find build -type f -name '*valgrind_hash_*' | sort -V); do
    cat "$i" >>build/valgrind_suppression.supp
done
# remove files
find build -type f -name '*valgrind_hash_*' -exec rm -rf {} ';'
find build -type f -name '*txt.supp-part.*' -exec rm -rf {} ';'
find build -type f -name '*valgrind_suppression.supp.part.*' -exec rm -rf {} ';'
if [ "${keep_files}" = 'false' ]; then
    find build -type f -name '*valgrind-supp-*' -exec rm -rf {} ';'
fi
mv build/valgrind_suppression.supp src/valgrind.supp
