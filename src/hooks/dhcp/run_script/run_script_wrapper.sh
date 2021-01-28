if test ${#} -lt 2; then
       echo "Usage: ${0} script_name function_name"
       echo "     All variables used by the script must be available"
       echo "     as environment variables."
       echo "     All variables specified in the 'hook_parameters'"
       echo "     variable will be printed to stdout."
       exit 1
fi

script_name=${1}
function_name=${2}

source ${script_name} ${function_name}

for parameter in ${hook_parameters}; do
	echo "${parameter}=${!parameter}"
done
