#!/bin/bash -l
#SBATCH --job-name=add-values	    	 # Job name
#SBATCH --time=0-00:01:00                # Time limit days-hrs:min:sec
#SBATCH --partition=shared		 # Check partitions on the Wiki
#SBATCH --mem=2Gb			 # Memory size
#SBATCH -n 1				 # Number of processors in the node
#SBATCH --mail-user=r_m727@txstate.edu	 # Email me!
#SBATCH --mail-type=end,begin		 # Types of Emails (Start,End)

# Load Module
module load intel/18

# Go to directory
cd /home/r_m727/addvalues

# compiles program
icc -o add-values addvalues.cpp

# execute program
./add-values > output.txt

# Unload module
module unload intel/18

# End the Job
exit 0
