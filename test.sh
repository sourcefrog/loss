#! /bin/zsh -e

allok=true
for infile in test/parse/*.in
do
    echo $infile ...
    outfile=${infile:r}.out
    if ./loss_parse $infile | diff -u $outfile -
    then
        allok=false
    fi
done

$allok