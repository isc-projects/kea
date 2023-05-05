#!/bin/bash
work_file=`mktemp`
for file in `find ./ | grep -v "\.git" | grep -v "_build" | grep -v "\/man\/" | grep "\.rst\|\.json" | grep -v "api\.rst" | sort`; do
	json=0
	comment=0
	line_num=0
	echo "processing: $file"
	while read line; do
		line_num=$((line_num+1))
		if [ $comment -eq 0 -a $json -eq 0 -a `echo "$line" | grep -e "^\[A-Za-z]+" | wc -l` -eq 1 ]; then
			continue
                elif [ $comment -eq 0 -a `echo "$line" | grep -e "\/\*" | grep -v -e "\*\/" | wc -l` -eq 1 ]; then
			comment=1
			echo "" >> $work_file
			continue
                elif [ $comment -eq 1 -a `echo "$line" | grep "\*\/" | wc -l` -eq 1 ]; then
			comment=0
			echo "" >> $work_file
			continue
		elif [ $comment -eq 0 -a $json -eq 0 -a `echo "$line" | grep "^\s*{\|^\s*\".*{" | grep -v "}" | grep -v "key\|pre" | wc -l` -eq 1 ]; then
			json=1
			# ignore any map name before top level map
			line=`echo "$line" | sed "s/.*{/{/g"`
			echo "" > $work_file
		elif [ $comment -eq 0 -a $json -eq 1 -a `echo "$line" | grep -e "^\s*[A-Za-z]" | wc -l` -eq 1 ]; then
			json=0
			cat $work_file | jq . > /dev/null
			if [ $? -ne 0 ]; then
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
				if [ `echo "$file" | grep "\.json" | wc -l` -eq 0 ]; then
					echo "$line" | cut -d "#" -f 1 | sed "s/\.\.\./\"placeholder\": 0/g" | sed "s/\/\/ .*//g" | sed "s/<?.*?>//g" >> $work_file
				else
					echo "$line" | cut -d "#" -f 1 | sed "s/\/\/ .*//g" | sed "s/<?.*?>//g" >> $work_file
				fi
			fi
		fi
	done <<< $(cat $file | sed ':a;N;$!ba;s/,\s*\n\s*\.\.\.//g' | sed 's/\\\"/\\\\\"/g' | sed 's/\\\\,/\\\\\\\\,/g')
	if [ $comment -eq 0 -a $json -eq 1 ]; then
		cat $work_file | jq . > /dev/null
		if [ $? -ne 0 ]; then
			echo "file $file contains invalid JSON near line $line_num"
			echo "===start of JSON block==="
			cat $work_file
			echo "====end of JSON block===="
		fi
	fi
done
rm $work_file
