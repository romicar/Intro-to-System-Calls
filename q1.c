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

int main(int argc, char *argv[])
{ 
	// error handling for number of arguments
    if (argc != 2)
    {
        write(2,"Please enter exactly 2 arguments\n",strlen("Please enter exactly 4 arguments\n"));
        return 0;
    }
	
	//Creating Directory
	int dir = mkdir("Assignment", 0700);
	/*if (dir == -1)
	{
		perror("Error in creating Directory");
		return 0;
	}*/
	int old_file = open(argv[1], O_RDONLY,0100); //open the file in read mode
	//Creating files inside directory
	char filename[10000];
	char *token = strtok(argv[1], "/");
	//printf("%s\n", token);
	int tokenlen=strlen(token);
	//while (tokenlen !=0)
	//{
	//	strcpy(filename, token);
		//token = strtok(NULL, "/");
	//	tokenlen--;
	//}
	strcpy(filename, token);
	//printf("%s\n", filename);
	char filepath[] = "Assignment/1_";
	strncat(filepath, filename,tokenlen);
	//printf("%s",filename);
	//printf("%s", filepath);
	//int newfile = creat(filepath, 0764);
	int new_file = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0600); //opening the created file
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
	int length = lseek(old_file, 0, SEEK_END);
	if (length <= 0)
	{
		char arr[] = "File is empty\n";
		write(2, arr, strlen(arr));
		return 0;
	}
	lseek(new_file, 0, SEEK_SET);
	//setting Bytes per read
	int bytes_read;
	int a = 0, b;
	if (length >= 100000)
	{
		a = length / 100000;
		b = length % 100000;
		bytes_read = 100000;
	}
	else
	{
		bytes_read = 1;
		a = length / bytes_read;
		b = length % bytes_read;
	}
	lseek(old_file, bytes_read, SEEK_END);

	int size = 1;
	int sum = 0;
	char buffer[10000];
	char new[1000000], old[1000000];
	int i;
	while (a--)
	{
		lseek(old_file, -(size * bytes_read), SEEK_END);
		read(old_file, old, bytes_read);
		int j = bytes_read - 1;
		for (i = 0; i < bytes_read; i++)
		{
			new[i] = old[j];
			j--;
		}
		new[bytes_read] = '\0';

		int w = write(new_file, new, bytes_read);
		size++;

		sum += w;
		//printf("sum: %d\n",sum);
		long double percentage = (long double)(((long double)sum / (long double)length) * 100);
		//printf("%Lf\n",percentage);
		char v[] = "%";
		sprintf(buffer, "\r%0.2Lf%s", percentage, v);
		write(1, buffer, strlen(buffer));
	}
	if (b != 0)
	{

		lseek(old_file, -((size - 1) * bytes_read) - b, SEEK_END);
		bytes_read = b;
		read(old_file, old, bytes_read);

		int j = bytes_read - 1;
		for (int i = 0; i < bytes_read; i++)
		{
			new[i] = old[j];
			j--;
		}
		new[bytes_read] = '\0';
		int w = write(new_file, new, bytes_read);
		sum += w;
		//printf("sum: %d\n",sum);
		long double percentage = (long double)(((long double)sum / (long double)length) * 100);
		//printf("%Lf\n",percentage);
		char v[] = "%";
		sprintf(buffer, "\r%0.2Lf%s", percentage, v);
		write(1, buffer, strlen(buffer));
	}

	close(old_file);
	close(new_file);
	return 0;
}