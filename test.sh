#! /bin/zsh -e

failed=false
for infile in test/parse/*.in
do
    echo $infile ...
    outfile=${infile:r}.out
    ./loss_parse $infile | diff -u $outfile - || failed=true
done
$failed && exit 1

for infile in test/eval/*.scm
do
    echo $infile ...
    outfile=${infile:r}.out
    ./loss $infile | diff -u $outfile - || failed=true
done
$failed && exit 1

echo victory!