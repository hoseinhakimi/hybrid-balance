# #!/bin/sh
echo "How Many Ensembles:"
read STEPS
echo "Network Size:"
read SIZE
echo "G:"
read G
echo "Ensembles:"
read ENS

g++ -o main main.cpp -lpthread
for temp in $(seq 0 $STEPS); do
  ./main << EOF
  $SIZE
  0
  0
  $G
  0
  $ENS
EOF
done
cd ../outputs/data
filename=$SIZE"_"$G.csv
cat headers.csv "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv > $filename
rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv
cd ../../src


# cat headers.csv > $filename
# for i in $(seq 0 3); do
#   cat $filename "r_"$SIZE"_"$i.csv  > $filename
  # rm "r_"$SIZE"_"$i.csv
# done
