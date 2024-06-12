#!/bin/bash

cut -f 5 $1 | awk '{$1=$1};1' | sort --parallel=${WIKI_JOBS} | uniq -c > $2.tsv
awk '$1 >= 3 {print $2}' $2.tsv > $2.txt