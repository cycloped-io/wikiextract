#!/bin/bash

cut -f 5 $1 | sort --parallel=10 | uniq -c > $2.tsv
cut -b 9- $2.tsv > $2.txt
