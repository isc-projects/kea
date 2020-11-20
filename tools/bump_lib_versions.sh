#!/bin/bash
set -x

old_release_tag=${1}
new_release_tag=${2}

is_stable_release() {
	version=$(echo ${1} | cut -d . -f2)
	if [ $((version % 2)) -eq 0 ]; then
		echo 1;
	else
		echo 0;
	fi
}

find_latest_stable_release_tag() {
	tag_pattern=${1}
	for version in $(git tag | grep ${tag_pattern} | tac); do
		if [ $(is_stable_release ${version}) -eq 1 ]; then
			echo ${version}
			return
		fi
	done
}

is_old_tag_stable_release=$(is_stable_release ${old_release_tag})
is_new_tag_stable_release=$(is_stable_release ${new_release_tag})

# if any file has changed in a specific library director
# there are 4 possible cases
# 1. old release is stable and new release is stable
#    new_version = old_version + 1
# 2. old release is stable and new release is development
#    new_version = old_version + 11
# 3. old release is development and new release is development
#    if latest development has already added 10 it means that the old_release version is different than latest_stable version
#        new_version = old_version + 1
#    else it means that the old_release has not incremented the version since latest_stable
#        new_version = old_version + 11
# 4. old release is development and new release is stable
#    illegal as there should only be stable to stable bump lib versions

if [ ${is_old_tag_stable_release} -eq 0 && ${is_new_tag_stable_release} -eq 1 ]; then
	echo "illegal bumb lib versions from development release to stable release"
	exit 1
fi

latest_stable_release_tag=$(find_latest_stable_release_tag $(echo ${old_release_tag} | cut -d . -f1))
increment_extra=10
increment=1

for lib in $(git diff ${old_release_tag} --name-only src/lib/ | cut -d "/" -f 3 | uniq); do
	old_version=$(cat src/lib/${lib}/Makefile.am | grep "\-version\-info" | tr -s ' ' | rev | cut -d " " -f 1 | rev | cut -d ":" -f 1)
	new_version=$((old_version + ${increment}))
	if [ ${is_new_tag_stable_release} -eq 0 ]; then
		if [ ${is_old_tag_stable_release} -eq 1 ] || [ $(git diff ${latest_stable_release_tag} ${old_release_tag} src/lib/${lib}/Makefile.am | grep "\-version\-info" | wc -l) -eq 0 ]; then
			new_version=$((new_version + ${increment_extra}))
		fi
	fi
	sed -i "s/version-info .*/version-info ${new_version}:0:0/" src/lib/${lib}/Makefile.am
done

