#! /bin/bash -e
for f
do
    indent -kr --indent-label0 -nut -brf -di1 -npsl -ncs \
	--honour-newlines \
        -T loss_object -T loss_string -T FILE \
        -l 76 $f
done
