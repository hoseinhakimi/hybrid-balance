# #!/bin/sh
echo "Temperature Steps Count:"
read STEPS
echo "Temperature offset:"
read OFFSET
echo "Temperature Steps Value:"
read TEMPSTEPS
echo "Network Size:"
read SIZE
echo "G:"
read G
echo "Ensembles:"
read ENS

g++ -o main main.cpp -lpthread
for r in $(seq 0 0); do
for temp in $(seq 0 $STEPS); do
  ./main << EOF
  $SIZE
  $(($temp+$OFFSET))
  $TEMPSTEPS 
  $G
  $r
  $ENS
EOF
done
cd ../outputs/data
filename=$SIZE"_"$G.csv
cat headers.csv "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv > $filename
cd ../../src
done
cd ../outputs/data
rm "r_"$SIZE"_0".csv "r_"$SIZE"_1".csv "r_"$SIZE"_2".csv "r_"$SIZE"_3".csv

# cat headers.csv > $filename
# for i in $(seq 0 3); do
#   cat $filename "r_"$SIZE"_"$i.csv  > $filename
  # rm "r_"$SIZE"_"$i.csv
# done
