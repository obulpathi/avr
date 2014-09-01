#!/bin/bin

banner:
	banner -w 46 bullz > banner.hex

uniform:banner.hex
	sed -f uniform.sed banner.hex > uniform.hex

addfile:
	sed -f genadd.sed rom.hex > addfile.hex
	echo "Crimp addfile to contain the same number of lines as uniform.hex"

fixadd:addfile.hex uniform.hex
	paste addfile.hex uniform.hex > tmp.hex
	sed 's/\t//' tmp.hex > fixadd.hex

hexify:fixadd.hex
	sed -f hexify.sed fixadd.hex > hexify.hex
	echo ":00000001FF" >> hexify.hex

fixchksum:hexify.hex
	# fix checksums of the records
	fixchksum hexify.hex
	mv hexify-fixed.hex easter-egg.hex

hide:
	flash easter-egg.hex
