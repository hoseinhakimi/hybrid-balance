#!/bin/sh

STEPS=20
echo "What is the size of the network you want to simulate?"
read SIZE
g++ -o main main.cpp -lpthread
for i in $(seq 1 $STEPS); do
  ./main << EOF
  $SIZE
  $i
EOF
done


