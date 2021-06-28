#!/bin/bash -l
#SBATCH --job-name=hello-hybrid	    	 # Job name
#SBATCH --time=0-00:01:00                # Time limit days-hrs:min:sec
#SBATCH --partition=parallel		 # Check partitions on the Wiki
#SBATCH --mem-per-cpu=1Gb		 # Memory size
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=6		 # Number of processors in the node
#SBATCH --mail-user=r_m727@txstate.edu	 # Email me!
#SBARCH --mail-type=end,begin		 # Types of Emails (Start,End)

# Load Module
module load intelmpi/18

# Go to directory
cd /home/r_m727/MPIMatrix

# compiles program
mpicc -o mpimatrix -fopenmp mpimatrix.c -std=c99

# execute with 5 processes
mpirun -np 6 ./mpimatrix > mpimatrix.txt

# Unload module
module unload intelmpi/18

# End the Job
exit 0
