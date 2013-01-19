#! /bin/bash -e
for f
do
    indent -kr --indent-label0 -nut -brf -di1 -npsl -ncs -T loss_object -T loss_string -T FILE -T loss_cons -l 76 $f
done
