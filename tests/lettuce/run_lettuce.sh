if [ "$1" = "-I" ]; then
    shift
    echo "$@"
    LETTUCE_SETUP_COMPLETED=1 lettuce $@
else
    source ./setup_intree_bind10.sh
    exec lettuce $@
fi
