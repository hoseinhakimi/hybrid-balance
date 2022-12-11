# #!/bin/sh
echo "Temperature Steps Count:"
read STEPS
echo "Temperature offset:"
read OFFSET
echo "Temperature Steps Value:"
read TEMPSTEPS
echo "Network Size:"
read SIZE
echo "H:"
read H
echo "G:"
read G
echo "Ensembles:"
read ENS
echo "Randomness:"
read R
g++ -o main main.cpp -lpthread
# for r in $(seq 0 2); do
for temp in $(seq 0 $STEPS); do
  ./main << EOF
  $SIZE
  $(($temp+$OFFSET))
  $TEMPSTEPS
  $H
  $G
  $R
  $ENS
EOF
done
cd ../outputs/data
filename=$SIZE"_"$G"_"$H.csv
cat headers.csv "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv > $filename
cd ../../src
# done
cd ../outputs/data
rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv
