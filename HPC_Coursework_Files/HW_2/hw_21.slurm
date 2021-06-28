#!/bin/bash -l
#SBATCH --job-name=matrix_multiply	    	 # Job name
#SBATCH --time=2-01:00:00                # Time limit days-hrs:min:sec
#SBATCH --partition=shared		 # Check partitions on the Wiki
#SBATCH --mem=128Gb			 # Memory size
#SBATCH -n 1				 # Number of processors in the node
#SBATCH --mail-user=r_m727@txstate.edu	 # Email me!
#SBATCH --mail-type=end,begin		 # Types of Emails (Start,End)

# Load Module
module load intel/18

# Go to directory
cd /home/r_m727/hw_2

# compiles program
icc -o matrix_multiply hw_21.cpp

# execute program
./matrix_multiply > output.txt

# Unload module
module unload intel/18

# End the Job
exit 0
