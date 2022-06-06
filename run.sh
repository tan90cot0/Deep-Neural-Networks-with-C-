#!/bin/bash
	if [[ $? == 0 ]]; then
	
		#g++ -c -Wall -Werror -fpic -I/usr/include/mkl libaudio.cpp 
		#g++ -c -Wall -Werror -fpic -I$(MKL_BLAS_PATH)/include libaudio.cpp 
		g++ -c -Wall -Werror -fpic libaudio.cpp 
		#g++ -shared -o libaudio.so libaudio.o -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
		g++ -shared -o libaudio.so libaudio.o
		g++ -L. -Wall -o yourcode.out yourcode.cpp -laudio
		#export LD_LIBRARY_PATH=/home/aryan/Desktop/Assignment_1.3:$LD_LIBRARY_PATH
		#./yourcode.out mfcc_features/ca4d5368_nohash_5.txt out.txt
		
	fi
