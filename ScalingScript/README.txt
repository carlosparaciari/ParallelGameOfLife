The script scaling_game_omp.sh measure the time the golGameApp takes to evolve
an initila seed for n time steps.

Specifically, the seed frame is the one of a Turing machine, in a 1716x1649 grid.
The frame is evolved 1 10 100 500 1000 2000 3000 5000 10000 times, and time is
measured each times.

Note: While the script removes the output files of golGameApp at the end of each
new cycle, during the cycle these files occupy a substantial amount of space
(for the 1000 time steps it should be around 400Mb).
  
To run the script, just write in the command line (while in the build folder)

> cp ./bin/golGameApp ./ScalingScript/
> cd ./ScalingScript/ 
> chmod u+x ./scaling_game_omp.sh
> ./scaling_game_omp.sh
