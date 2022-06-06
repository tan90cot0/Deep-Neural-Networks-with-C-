							COP290 - Subtask 3
					   	  Arush Utkarsh and Aryan Dua
					   	            6/3/22
					   
					   
****NOTE- The mkl and openblas implementation were working on this computer but not with the environment variables. If need be, we can demonstrate the output using the libraries in the demo session. We have commented out the relevant portions. We were facing a problem with setting the path variables, as I have a MacBook and it was really difficult trying to do it. We just reverted back to the original implementation at the 11th hour.

					   
					 	 Instructions to check the output:
1. Open the terminal inside this folder
2. Enter "make"
3. Type ./yourcode.out audiosamplefile outputfile 
   for example:- (./yourcode.out  mfcc_features/ca4d5368_nohash_5.txt out.txt)
4. The top 3 keywords with the highest softmax probabilities are stored in out.txt in the format  mfcc_features/ca4d5368_nohash_5.txt yes unknown left 0.999690 0.000288 2.21e-5



							Code Structure:-
								
1. The functions used were already made in the previous subtasks. 
2. The shared library provides an API in the format of a function pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred); which takes a pointer to the audiofile name and pointer to an array of pred_t structures and stores the top 3 keywords woith highest softmax probabilities in the location of the pred_t array. It then returns a pointer to that array which is same as the input pointer.
	
	
	
			
							Errors Handled:
								
1. If a wrong input command is entered, through the command line, it will gracefully catch the error and display how the input should be ideally entered.
2. We have removed the incompatible matrix dimensions error as in this subtask the trained weights and biases and features are given to us. Since they are trained, they would be of the required size, which is why we took them to be ideal.
3. File not found error.
4. If the number of command line arguments are not ideal.


						
