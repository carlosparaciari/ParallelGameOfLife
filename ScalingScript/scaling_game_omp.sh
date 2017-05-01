#!/bin/sh

old=1
touch time.txt

for new in 1 10 100 500 1000 2000 5000 10000
do
   echo "$old $new"
   sed -i -e "s/time_steps ${old}/time_steps ${new}/g" ./input/config_turing.dat
   echo "Time for $new time steps." >> time.txt
   (time ./golGameApp -c ./input/config_turing.dat ./input/turing_machine_seed.life) 2>> time.txt
   rm turing_evolution_*
   rm config.yaml
   old=$new
done

sed -i -e "s/time_steps ${old}/time_steps 1/g" ./input/config_turing.dat
