#! /bin/zsh -e

for infile in test/parse/*.in
do
    echo $infile ...
    outfile=${infile:r}.out
    ./loss_parse $infile | diff -u $outfile -
done


for infile in test/eval/*.scm
do
    echo $infile ...
    outfile=${infile:r}.out
    ./loss $infile | diff -u $outfile -
done

echo victory!