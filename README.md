# Introduction to System Calls
It is part of the first assignment of the OSN course in Monsoon 2021 <br>
Motivate of these questions were to establish a strong understanding of the various system-calls<br>

## System-Calls used
- The system calls used to complete these questions are `write`,`read`,`perror`,`open`,`close`,`mkdir`,`lseek` and `stat`
-  The use of printf and scanf are restricted.
Use of sprintf is only allowed for formatting strings and printing progress.
Use of string.h library is permitted

# Ques 1
1. We are given a file and we need to reverse the content of that file and store the new file in the directory Assignment created under current working directory
2. Need to print a progress bar

# Ques 2
1. We are given a file, a starting index and an ending index. We need to reverse the entire file leaving the portion which starts from starting index and ends at ending index.
2. Also we are required to print the progress bar.

# Ques 3
Given a file name 
1. We need to check if the directory Assignment exist or not
2. Need to check for 2 files in Assignment directory that are <input_file> and <1_input_file>.
3. Need to print the permissions of the two files and Assignment directory.
4. We need to check if <1_input_file> is the reverse of input_file> or not.

----

# Assumptions: 
## For Question 1:
1. file to be reversed should be present in the same folder.
2. Gives error if file is empty.
3. Read, write and execute permissions are given to users for the created directory.
4. Read permission is given to user,group and others for the input file.
4. Read and write permisssion is given to user for the output file.
5. In case Assignment directory is already present the overwrites the file each time the command is run with same file name.
6. Might take some time to run on big files.
7. Ensure that the input files do not have a new line character at the end.

### Compile
`gcc q1.c `<br>
`./a.out <input_file_path>`<br>

----

## For Question 2:

1. Same as  question 1.


### Compile
`gcc q2.c `<br>
`./a.out <input_file_path> start_char end_char `<br>

----

## For Question 3:
1. Assumed that it will give results for only 2 files i.e.,A.txt and 1_A.txt and Assignment directory given that input file is A.txt.
2. Assumed that the input text file will be moved to the Assignment folder for running this question otherwise it can't detect the input file and just shows the results for output file and directory.
3. Ensure that the input files do not have a new line character at the end.

### Compile
`gcc q3.c `<br>
`./a.out <new_file> <old_file> <directory>`<br>

----



