#!/bin/sh

# given a directory, copy all needed parts from boost into the
# current branch

# only run this to update boost! (i.e. almost never)

# usage example:
# cd /tmp
# tar xzvf /location/of/boost/tarball
# cd /home/user/svn/bind10/trunk
# tools/import_boost.sh /tmp/boost-version
# svn commit

# need new boost stuff?
# add files to list 'ere
FILES="
boost/*.hpp
boost/algorithm
boost/asio
boost/bind
boost/config
boost/concept
boost/detail
boost/exception
boost/function
boost/mpl
boost/preprocessor
boost/range
boost/smart_ptr
boost/type_traits
boost/utility
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


