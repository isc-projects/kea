#!/bin/sh

# run unittests
# ./meson.sh test -C build --setup valgrind_gen_suppressions
for i in $(find build | grep "valgrind-supp-" | grep -v "txt\.supp")
do
	found=$(grep -c "<suppression>" "$i")
	if [ "$found" -eq 0 ]
	then
		continue
	fi
	# remove useless data
	xmlstarlet sel -t -v "/valgrindoutput/error/suppression/rawtext" "$i" | grep "\S" | sed 's/&lt;/</g; s/&gt;/>/g; s/&amp;/\&/g; s/&quot;/"/g; s/&apos;/'"'"'/g' > "$i-txt.supp"
	# extract the binary path and name
	found_in_path=$(grep "<exe>.*</exe>" "$i" | grep -v "valgrind" | xmlstarlet sel -t -v "/exe" | sed "s|.*src|src|")
	# insert a comment with the binary path and name
	sed -i "s|<insert_a_suppression_name_here>|<insert_a_suppression_name_here>\n   # detected in $found_in_path|g" "$i-txt.supp"
	# split the file
	csplit -s -z -f "$i-txt.supp-part." "$i-txt.supp" '/{/' '{*}'
done
echo "" > build/valgrind_suppression.supp
for i in $(find build/ | grep "txt\.supp-part\.")
do
	# compute md5sum
	label=$(grep -v "insert_a_suppression_name_here" "$i" | grep -v "# detected in " | md5sum | cut -d " " -f 1)
	# update label 
	sed -i "s/<insert_a_suppression_name_here>/valgrind_hash_$label/g" "$i"
	# check if hash is present
	match=$(grep -c "$label" build/valgrind_suppression.supp)
	if [ "$match" -eq 0 ]
	then
		# include entire content if hash not present
		cat "$i" >> build/valgrind_suppression.supp
	else
		# extract the binary path and name
		found_in_path=$(grep " # detected in " "$i")
		# update comment with binary path and name if hash not present
		sed -i "s|valgrind_hash_$label|valgrind_hash_$label\n$found_in_path|g" build/valgrind_suppression.supp
	fi
done
csplit -s -z -f build/valgrind_suppression.supp.part. build/valgrind_suppression.supp '/{/' '{*}'
for i in $(find build/ | grep "valgrind_suppression\.supp\.part\.")
do
	name=$(grep "valgrind_hash_" "$i" | tr -d " ")
	if [ -z "$name" ]
	then
		continue
	fi
	mv "$i" "build/$name"
done
cat << EOF > build/valgrind_suppression.supp
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
for i in $(find build/ | grep "valgrind_hash_" | sort -V)
do
	cat "$i" >> build/valgrind_suppression.supp
done
# remove files
find build/ | grep "valgrind_hash_" | xargs rm -rf
find build/ | grep "txt\.supp-part\." | xargs rm -rf
find build/ | grep "valgrind-supp-" | xargs rm -rf
mv build/valgrind_suppression.supp src/valgrind.supp
