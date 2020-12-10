# #!/bin/sh
STEPS=20
echo "What is the size of the network you want to simulate?"
read SIZE
echo "What is randomness?"
read RAND
echo "What is theta?"
read THETA
echo "How many Ensembles?"
read ENS
g++ -o main main.cpp -lpthread
for i in $(seq 0 $STEPS); do
  ./main << EOF
  $SIZE
  $i
  $THETA
  $RAND
  $ENS
EOF
done
cd ../outputs/data
filename=$SIZE"_"$RAND"_"$THETA"_3".csv
cat headers.csv "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv > $filename
rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv

# cat headers.csv > $filename
# for i in $(seq 0 3); do
#   cat $filename "r_"$SIZE"_"$i.csv  > $filename
  # rm "r_"$SIZE"_"$i.csv
# done