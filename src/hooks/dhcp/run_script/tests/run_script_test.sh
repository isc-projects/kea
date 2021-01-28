echo ${@}

SKIP="false"
if test ! -z ${ADDRESS}; then
	echo "${ADDRESS}"
	SKIP="false"
fi
