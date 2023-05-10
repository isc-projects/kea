#!/bin/bash
work_file=`mktemp`
for file in `find ./ | grep -v "\.git" | grep -v "_build" | grep -v "\/man\/" | grep "\.rst\|\.json" | sort`; do
	json=0
	comment=0
	line_num=0
	echo "processing: $file"
	while IFS= read line; do
		line_num=$((line_num+1))
		if [ $comment -eq 0 -a $json -eq 0 -a `echo "$line" | grep -e "^[A-Za-z]+\|^\s*\\\`" | wc -l` -eq 1 ]; then
			# ignore line if it starts with 'A-Za-z' or spaces followed by '`'
			continue
		elif [ $comment -eq 0 -a `echo "$line" | grep -e "\/\*" | grep -v -e "\*\/" | wc -l` -eq 1 ]; then
			# if the line contains /* and it does not contain */ on the same line
			comment=1
			echo "" >> $work_file
			continue
		elif [ $comment -eq 1 -a `echo "$line" | grep "\*\/" | wc -l` -eq 1 ]; then
			# if the line contains */
			comment=0
			echo "" >> $work_file
			continue
		elif [ $comment -eq 0 -a $json -eq 0 -a `echo "$line" | grep "^\s*{\|^\s*\".*{" | grep -v "}" | grep -v "key\|pre" | wc -l` -eq 1 ]; then
			# if this is not a commend and the line starts with spaces followed by '{' or by '"' followed by "{"
			# ignore dns config:
			#      key "key.four.example.com." {
			#          algorithm hmac-sha224;
			#          secret "bZEG7Ow8OgAUPfLWV3aAUQ==";
			#      };
			# ignore detailed html:
			#			.. raw:: html
			#    <details><summary>Expand here!</summary>
			#    <pre>{
			#    ...
			#    }</pre>
			#    </details><br>
			json=1
			# ignore any map name before top level map
			line=`echo "$line" | sed "s/.*{/{/g"`
			echo "" > $work_file
		elif [ $comment -eq 0 -a $json -eq 1 -a `echo "$line" | grep -e "^\s*[A-Za-z]\|^\s*\\\`" | wc -l` -eq 1 ]; then
			# if the line is not a comment and the line starts with spaces followed by 'A-Za-z' or followed by "`" and the parser is processing a json structure
			json=0
			cat $work_file | jq . > /dev/null
			if [ $? -ne 0 ]; then
				# if the jq tool returned error
				echo "file $file contains invalid JSON near line $line_num"
				echo "===start of JSON block==="
				cat $work_file
				echo "====end of JSON block===="
			fi
		fi
		if [ $comment -eq 0 -a $json -eq 1 ]; then
			if [ `echo "$line" | grep -e "^\s*\.\.\s" | wc -l` -eq 1 ]; then
				echo "" >> $work_file
			else
					# if file is .json the following replace in line are done:
					# 1. delete everything after '#'
					# 2. delete everything after //
					# 3. ignore <?include?>
					# 4. replace all '[ <DATA> ]' with '[ "<DATA>"]' where DATA contains: '-' and 'A-Za-z0-9' and ' '
					# 5. replace all ' <DATA>:' with ' "<DATA>":'
					# 6. replace all ': <DATA>' with ': "<DATA>"'
					# 7. replace '   ...' with '   "placeholder": "value"
					# 8. replace ', ... ' with ' '
					# 9. replace '   <DATA>' with '   "placeholder": "value"'
					# 10. replace ' <DATA>' with ' "placeholder"'
				if [ `echo "$file" | grep "\.json" | wc -l` -eq 0 ]; then
					echo "$line" | cut -d "#" -f 1 | sed "s/\/\/ .*//g" | sed "s/<?.*?>//g" | sed "s/\[ <\([-A-Za-z0-9 ]*\)> \]/\[ \"<\1>\" \]/g" | sed "s/ <\(.*\)>:/ \"<\1>\":/g" | sed "s/: <\(.*\)>/: \"<\1>\"/g" | sed "s/   \.\.\./   \"placeholder\": \"value\"/g" | sed "s/, \.\.\. / /g" | sed "s/   <\(.*\)>/   \"placeholder\": \"value\"/g" | sed "s/ <\(.*\)>/ \"placeholder\"/g" >> $work_file
				else
					# if file is .rst the following replace in line are done:
					# 1. delete everything after '#'
					# 2. delete everything after //
					# 3. ignore <?include?>
					echo "$line" | cut -d "#" -f 1 | sed "s/\/\/ .*//g" | sed "s/<?.*?>//g" >> $work_file
				fi
			fi
		fi
	done <<< $(cat $file | sed ':a;N;$!ba;s/,\s*\n\s*\.\.\.//g' | sed 's/\\\"/\\\\\"/g' | sed 's/\\\\,/\\\\\\\\,/g')
	if [ $comment -eq 0 -a $json -eq 1 ]; then
		# if the file ended but the parser is processing a json structure
		cat $work_file | jq . > /dev/null
		if [ $? -ne 0 ]; then
			# if the jq tool returned error
			echo "file $file contains invalid JSON near line $line_num"
			echo "===start of JSON block==="
			cat $work_file
			echo "====end of JSON block===="
		fi
	fi
done
rm $work_file
