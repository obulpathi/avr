#!/bin/sed

# keep 1st 43 chars
s/^\(.\{9\}\).*$/\1/

# number each line of a file (number on left, right-aligned)
# sed = filename | sed 'N; s/^/     /; s/ *\(.\{6,\}\)\n/\1  /'
#N; s/^/     /; s/ *\(.\{6,\}\)\n/\1  /

# add EOF record to the file
# echo ":00000001FF" >> fixadd.hex
