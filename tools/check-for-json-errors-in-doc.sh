#!/bin/sh

# Usage:
# check-for-json-errors-in-doc.sh [--all] [<file1>, <file2>, ...]

set -eu

# Change directory to the root of the repository.
script_path=$(cd "$(dirname "${0}")" && pwd)
cd "${script_path}/.." || exit 1

# Parse parameters.
if test ${#} -gt 0; then
  if test "${1}" = '--all'; then
    files='doc src'
  else
    files="${*}"
  fi
else
  # By default, check only modified files.
  files=$(git diff --name-only "$(git merge-base origin/master HEAD)")

  # If there is nothing to check, exit early. Otherwise, it checks everything.
  if test -z "${files}"; then
    exit 0
  fi
fi

exit_code=0
work_file=$(mktemp)

# Get the files.
# shellcheck disable=SC2086
# SC2086: Double quote to prevent globbing and word splitting.
# Reason: There may be multiple files in ${files} so we explicitly want it expanded to not be treated as a single long file name.
files=$(find ${files} -type f \( -name '*.rst' -or -name '*.json' \) -and -not -path '*/_build/*' -and -not -path '*/man/*' | sort -uV)
for file in ${files}; do
  json=0
  comment=0
  line_num=0
  echo "processing: $file"
  IFS=
  content=$(tr '\n' '\r' < "${file}" | sed -r 's/,[[:blank:]]*\r[[:blank:]]*\.\.\.//g' | sed -r 's/\\[[:blank:]]*\r[[:blank:]]*//g' | tr '\r' '\n')
  content="${content}
"
  stop_at=$(printf '%s' "${content}" | wc -l)
  while true; do
    line_num=$((line_num + 1))
    if test "${line_num}" -gt "${stop_at}"; then
      break
    fi
    line=$(printf '%s' "${content}" | head -n "${line_num}" | tail -n 1)
    if [ $comment -eq 0 ] && [ $json -eq 0 ] && [ "$(echo "$line" | grep -c "^[A-Za-z]+\|^\s*\`")" -eq 1 ]; then
      # ignore line if it starts with 'A-Za-z' or spaces followed by '`'
      continue
    elif [ $comment -eq 0 ] && [ "$(echo "$line" | grep "/\*" | grep -cv "\*/")" -eq 1 ]; then
      # if the line contains /* and it does not contain */ on the same line
      comment=1
      echo >> "${work_file}"
      continue
    elif [ $comment -eq 1 ] && [ "$(echo "$line" | grep -c "\*/")" -eq 1 ]; then
      # if the line contains */
      comment=0
      echo >> "${work_file}"
      continue
    elif [ $comment -eq 0 ] && [ $json -eq 0 ] && [ "$(echo "$line" | grep "^\s*{\|^\s*\".*{\|^\s*\[\s*$" | grep -cv "}")" -eq 1 ]; then
      # if this is not a comment and the line starts with spaces followed by '{' or by '"' followed by "{"
      json=1
      # ignore any map name before top level map
      line=$(printf '%s' "${line}" | sed 's/.*{/{/g')
      echo > "${work_file}"
    elif [ $comment -eq 0 ] && [ $json -eq 1 ] && [ "$(echo "$line" | grep -c "^\s*[A-Za-z]\|^\s*\`")" -eq 1 ]; then
      # if the line is not a comment and the line starts with spaces followed by 'A-Za-z' or followed by "`" and the parser is processing a json structure
      json=0
      if ! jq . "${work_file}" > /dev/null; then
        # if the jq tool returned error
        echo "file $file contains invalid JSON near line $line_num"
        echo "===start of JSON block==="
        cat "${work_file}"
        echo "====end of JSON block===="
        exit_code=1
      fi
    fi
    if [ $comment -eq 0 ] && [ $json -eq 1 ]; then
      if [ "$(echo "$line" | grep -c "^\s*\.\.\s")" -eq 1 ]; then
        echo >> "${work_file}"
      else
        if [ "$(echo "$file" | grep -c "\.json")" -eq 0 ]; then
          # if file is .rst the following replace in line are done:
          # 1. delete everything after '#'
          # 2. delete everything after //
          # 3. ignore <?include?>
          # 4. replace all '[ <DATA> ]' with '[ "<DATA>" ]' where DATA contains: '-' and 'A-Za-z0-9' and ' '
          # 5. replace all ' <DATA>:' with ' "<DATA>":'
          # 6. replace all ': <DATA>' with ': "<DATA>"'
          # 7. replace '   ...' with '   "placeholder": "value"'
          # 8. replace ', ... ' with ' '
          # 9. replace '   <DATA>' with '   "placeholder": "value"'
          # 10. replace ' <DATA>' with ' "placeholder"'
          printf '%s' "${line}" | cut -d "#" -f 1 | sed 's/\/\/ .*//g' | sed 's/<?.*?>//g' | sed 's/\[ <\([-A-Za-z0-9 ]*\)> \]/\[ \"<\1>\" \]/g' | sed 's/ <\(.*\)>:/ \"<\1>\":/g' | sed 's/: <\(.*\)>/: \"<\1>\"/g' | sed 's/   \.\.\./   \"placeholder\": \"value\"/g' | sed 's/, \.\.\. / /g' | sed 's/   <\(.*\)>/   \"placeholder\": \"value\"/g' | sed 's/ <\(.*\)>/ \"placeholder\"/g' >> "${work_file}"
        else
          # if file is .json the following replace in line are done:
          # 1. delete everything after '#'
          # 2. delete everything after //
          # 3. ignore <?include?>
          printf '%s' "${line}" | cut -d "#" -f 1 | sed 's/\/\/ .*//g' | sed 's/<?.*?>//g' >> "${work_file}"
        fi
      fi
    fi
  done
  if [ $comment -eq 0 ] && [ $json -eq 1 ]; then
    # if the file ended but the parser is processing a json structure
    if ! jq . "${work_file}" > /dev/null; then
      # if the jq tool returned error
      echo "file $file contains invalid JSON near line $line_num"
      echo "===start of JSON block==="
      cat "${work_file}"
      echo "====end of JSON block===="
      exit_code=1
    fi
  fi
done
rm "${work_file}"

exit ${exit_code}
