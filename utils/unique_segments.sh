#!/bin/bash

cut -f 7 $1 | sort --parallel=10 | uniq -c > $2
