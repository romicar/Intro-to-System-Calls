#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/file.h>

// first two parts correct !

int main(int argc, char *argv[])
{
    // error handling for number of arguments
    if (argc != 4)
    {
        write(2,"Please enter exactly 4 arguments\n",strlen("Please enter exactly 4 arguments\n"));
        return 0;
    }

    // Creating Directory
    int dir = mkdir("Assignment", 0700);
    /*if (dir == -1)
    {
        perror("Error in creating Directory");
        return 0;
    }*/
    int old_file = open(argv[1], O_RDONLY); // open the file in read mode
    // Creating files inside directory
    char filename[10000];
    char *token = strtok(argv[1], "/");
    // printf("%s\n", token);
    int tokenlen = strlen(token);
    // while (tokenlen !=0)
    //{
    //	strcpy(filename, token);
    // token = strtok(NULL, "/");
    //	tokenlen--;
    // }
    strcpy(filename, token);
    // printf("%s\n", filename);
    char filepath[] = "Assignment/2_";
    strncat(filepath, filename, tokenlen);
    // printf("%s",filename);
    // printf("%s", filepath);
    // int newfile = creat(filepath, 0764);
    int new_file = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0600); // opening the created file

    if (old_file == -1)
    {
        write(2, "Error in opening input file\n", strlen("Error in opening input file\n"));
        return 0;
    }
    if (new_file == -1)
    {
        write(2, "Error in opening output file\n", strlen("Error in opening output file\n"));
        return 0;
    }
    /*if (new_file < 0 || old_file < 0 || dir < 0)
    {
        return 0;
    }*/
    int length = lseek(old_file, 0, SEEK_END); // length of the file
    // printf("%d\n",length);
    if (length <= 0)
    {
        char arr[] = "File is empty\n";
        write(2, arr, strlen(arr));
        return 0;
    }

    // given arguments
    int input1 = atoi(argv[2]);
    int input2 = atoi(argv[3]);
    // printf("%d %d\n",input1,input2);


    int bytes_read = 1;

    lseek(new_file, 0, SEEK_SET);

    int size = 1;
    char buffer[10000];

    // printf("%d\n",length);


    int bytes_written = 0;

    int window = input1;

    lseek(old_file, 0, SEEK_SET);
    // printf("\n");
    while (bytes_written < window)
    {
        int bytes_read = read(old_file, buffer, window);

        // printf("%s", buffer1);

        if (bytes_read == 0)
        {
            break;
        }

        for (int i = 0; i < window / 2; i++)
        {
            char tmp = buffer[i];
            buffer[i] = buffer[window - i - 1];
            buffer[window - i - 1] = tmp;
        }

        write(new_file, buffer, bytes_read);
        bytes_written += bytes_read;
        long double percentage = (long double)(((long double)bytes_written / (long double)length) * 100);
        char v[] = "%";
		sprintf(buffer, "\r%0.2Lf%s", percentage, v);
		write(2, buffer, strlen(buffer));
        // printf("%d %d\n", bytes_read, bytes_written);
    }

    lseek(old_file, input1, SEEK_SET);
    int READ = read(old_file, buffer, input2 - input1 + 1);
    buffer[READ] = '\0';
    write(new_file, buffer, READ);

    char buffer1[10000] = "\0";

    // setting Bytes per read
    //bytes_written = 0;

    window = length - input2;

    // printf("\n");
    while (bytes_written < window)
    {
        int bytes_read = read(old_file, buffer1, window);

        // printf("%s", buffer1);

        if (bytes_read == 0)
        {
            break;
        }

        for (int i = 0; i < strlen(buffer1) / 2; i++)
        {
            char tmp = buffer1[i];
            buffer1[i] = buffer1[strlen(buffer1) - i - 1];
            buffer1[strlen(buffer1) - i - 1] = tmp;
        }

        write(new_file, buffer1, bytes_read);
        bytes_written += bytes_read;

        long double percentage = (long double)(((long double)bytes_written / (long double)length) * 100);
        char v[] = "%";
		sprintf(buffer, "\r%0.2Lf%s", percentage, v);
		write(2, buffer, strlen(buffer));
        // printf("%d %d\n", bytes_read, bytes_written);
    }

    close(old_file);
    close(new_file);
    return 0;
}