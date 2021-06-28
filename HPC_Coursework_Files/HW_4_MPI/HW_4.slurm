#!/bin/bash -l
#SBATCH --job-name=HW_4	    	 # Job name
#SBATCH --time=0-00:10:00                # Time limit days-hrs:min:sec
#SBATCH --partition=parallel		 # Check partitions on the Wiki
#SBATCH --mem-per-cpu=1Gb		 # Memory size
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=26	 # Number of processors in the node
#SBATCH --mail-user=r_m727@txstate.edu	 # Email me!
#SBARCH --mail-type=end,begin		 # Types of Emails (Start,End)

# Load Module
module load intelmpi/18

# Go to directory
cd /home/r_m727/HW_42

# compiles program
mpicxx -o HW_4 -fopenmp HW_4.cpp

# execute with 26 processes
mpirun -np 26 ./HW_4 > HW_4.txt

# Unload module
module unload intelmpi/18

# End the Job
exit 0
