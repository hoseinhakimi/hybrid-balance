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
# echo "Randomness:"
# read R
g++ -o main main.cpp -lpthread
#for r in $(seq 1 1); do
for temp in $(seq 0 $STEPS); do
  ./main << EOF
  $SIZE
  $(($temp+$OFFSET))
  $TEMPSTEPS
  $H
  $G
  0
  $ENS
EOF
done
#done
cd ../outputs/data
filename=$SIZE"_"$G"_"$H.csv
cat headers.csv "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv  "r_"$SIZE"_4".csv  "r_"$SIZE"_5".csv  > $filename
rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv  "r_"$SIZE"_4".csv  "r_"$SIZE"_5".csv 
cd ../../src
# cd ../outputs/data
# rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv  "r_"$SIZE"_4".csv  "r_"$SIZE"_5".csv 
# g = -0.024 h = 0.000288
