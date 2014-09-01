# add 80 spaces to end of line
s/$/          /
s/ *$/&&&&&&&&/

# keep 1st 43 chars
s/^\(.\{45\}\).*$/\1/

# delete first 11 spaces
s/^           //
