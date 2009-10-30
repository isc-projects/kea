#!/bin/sh

# given a directory, copy all needed parts from boost into the
# current branch

# usage example:
# cd /tmp
# tar xzvf /location/of/boost/tarball
# cd /home/user/svn/bind10/trunk
# tools/import_boost.sh /tmp/boost-version
# svn commit

# need new boost stuff?
# add files to list 'ere
FILES="
boost/assert.hpp
boost/call_traits.hpp
boost/checked_delete.hpp
boost/config
boost/config.hpp
boost/current_function.hpp
boost/detail/*.hpp
boost/exception
boost/integer_traits.hpp
boost/lexical_cast.hpp
boost/limits.hpp
boost/memory_order.hpp
boost/mpl
boost/preprocessor
boost/shared_ptr.hpp
boost/smart_ptr
boost/smart_ptr.hpp
boost/static_assert.hpp
boost/throw_exception.hpp
boost/type_traits
"

TARGET="ext"

if [ $# -ne 1 ]
then
    echo "Usage: boost_import.sh <boost directory>"
    exit
fi

if [ ! -d $TARGET/boost ]
then
    echo "This does not appear to be the main trunk/branch directory"
    exit
fi


DIR=$1

do_cmd()
{
    echo $@
    $@
}


#echo "cp ${DIR}/boost/shared_ptr.hpp boost/"
for FILE in ${FILES}
do
TGT=`echo ${FILE} | sed 's/[^\/]*$//'`
cmd="mkdir -p ${TARGET}/${TGT}"
do_cmd ${cmd}
cmd="cp -r ${DIR}/${FILE} ${TARGET}/${TGT}"
do_cmd ${cmd}
done


