#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
typedef long long ll;

int main(int argc, char *argv[])
{
    char *input1 = argv[1]; // newfile
    char *input2 = argv[2]; // oldfile
    char *input3 = argv[3]; // directory

    int old_f = open(argv[2], O_RDONLY);
    int new_f = open(argv[1], O_RDONLY);
    int length_old = lseek(old_f, 0, SEEK_END);
    int length_new = lseek(new_f, 0, SEEK_END);

    if (length_old <= 0)
    {
        char arr[] = "Input File is empty\n";
        write(2, arr, strlen(arr));
    }

    if (argc != 4)
    {
        write(2, "Please enter exactly 4 arguments\n", strlen("Please enter exactly 4 arguments\n"));
        return 0;
    }
    char arg1[] = "Assignment";
    // char arg2[] = "Assignment/1_A.txt";
    // char arg3[] = "Assignment/2_A.txt";
    char s1[100], s2[100], s3[100];

    // int k = strlen(argv[1]);
    // strncpy(s,argv[1] + k, strlen(argv[1]));
    strcpy(s1, argv[1]); // s1 has newfile path
    strcpy(s2, argv[2]); // s2 has oldfile path
    strcpy(s3, argv[3]); // s3 has directory path
    char dir_f[100] = "Assignment/";
    char dir_f2[100] = "Assignment/";

    strcat(dir_f2, s1); // newfile
                        // printf("newfile:%s\n", dir_f2); // CORRECT !

    strcpy(dir_f, argv[2]); // oldfile
                            // printf("oldfile:%s\n", dir_f);

    struct stat file1, file2, file3;
    // for directory
    int dir = stat((arg1), &file1);
    int file_old = stat((dir_f), &file2);
    int file_new = stat((dir_f2), &file3);
    if (file_old == -1 || file_new == -1)
    {
        perror("File Error");
    }
    if (dir == -1)
    {
        write(2, ("Directory is created: No\n\n"), strlen("Directory is created: No\n\n"));
    }

    // write(2, "Directory is created: ", strlen("Directory is created: "));
    if (dir == 0 && S_ISDIR(file1.st_mode))
    {
        char arr[] = "Directory is created: Yes\n\n";
        write(1, arr, strlen(arr));

        if (length_old != length_new)
        {
            write(2, ("Whether file contents are reversed in newfile: No\n\n"), strlen("Whether file contents are reversed in newfile: No\n\n"));
        }

        else
        {
            int flag = 1; // correctly reversed file
            lseek(new_f, -1, SEEK_END);

            ll chunk = 1000000;
            ll start = ((length_old - 1) / chunk) * chunk;
            ll length = length_old - start;
            lseek(new_f, start, 0);

            char *new = (char *)malloc(chunk);
            char *old = (char *)malloc(chunk);
            char *r = (char *)malloc(chunk);

            if (length_old < chunk)
            {
                chunk = length_old;
            }

            while (1)
            {
                read(new_f, new, length);
                read(old_f, old, length);

                int st = 0, end = length - 1;
                while (st < length)
                {
                    r[st] = new[end];
                    st++;
                    end--;
                }
                r[length] = '\0';

                if (strncmp(r, old, length) != 0) // mismatch
                {
                    flag = 0;
                    break;
                }
                if (lseek(new_f, 0, SEEK_CUR) - chunk - length < 0)
                    break;
                lseek(new_f, -chunk - length, SEEK_CUR);

                length = chunk;
            }
            // checking if the contents of the file are reverse of each other
            (flag == 0) ? write(2, ("Whether file contents are reversed in newfile: No\n\n"), strlen("Whether file contents are reversed in newfile: No\n\n")) : write(2, ("Whether file contents are reversed in newfile: Yes\n\n"), strlen("Whether file contents are reversed in newfile: Yes\n\n"));
        }

        // else
        // write(2, "No\n", strlen("No\n"));
        // permission for output file1
        if (file_new != -1)
        { // permission under User
            write(2, "User has read permissions on newfile: ", strlen("User has read permissions on newfile: "));
            if (file3.st_mode & S_IRUSR)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "User has write permission on newfile: ", strlen("User has write permission on newfile: "));
            if (file3.st_mode & S_IWUSR)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            write(2, "User has execute permission on newfile: ", strlen("User has execute permission on newfile: "));
            if (file3.st_mode & S_IXUSR)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            // permission under Group
            // write(2,"\n\n",2);
            write(2, "Group has read permissions on newfile: ", strlen("Group has read permissions on newfile: "));
            if (file3.st_mode & S_IRGRP)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "Group has write permission on newfile: ", strlen("Group has write permission on newfile: "));
            if (file3.st_mode & S_IWGRP)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            write(2, "Group has execute permission on newfile: ", strlen("Group has execute permission on newfile: "));
            if (file3.st_mode & S_IXGRP)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            // write(2,"\n\n",2);
            // permission under Others
            write(2, "Others has read permissions on newfile: ", strlen("Others has read permissions on newfile: "));
            if (file3.st_mode & S_IROTH)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "Others has write permission on newfile: ", strlen("Others has write permission on newfile: "));
            if (file3.st_mode & S_IWOTH)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            write(2, "Others has execute permission on newfile: ", strlen("Others has execute permission on newfile: "));
            if (file3.st_mode & S_IXOTH)
            {
                write(2, ("Yes\n\n"), 4);
            }
            else
            {
                write(2, ("No\n\n"), 4);
            }
        }
        // permission for output file2
        if (file_old != -1)
        {
            // permission under User
            write(2, "User has read permissions on oldfile: ", strlen("User has read permissions on oldfile: "));
            if (file2.st_mode & S_IRUSR)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "User has write permission on oldfile: ", strlen("User has write permission on oldfile: "));
            if (file2.st_mode & S_IWUSR)
            {
                write(2, ("Yes\n"), 4);
            }

            else
            {
                write(2, ("No\n"), 4);
            }

            write(2, "User has execute permission on oldfile: ", strlen("User has execute permission on oldfile: "));
            if (file2.st_mode & S_IXUSR)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            // write(2,"\n\n",2);
            //  permission under Group
            write(2, "Group has read permissions on oldfile: ", strlen("Group has read permissions on oldfile: "));
            if (file2.st_mode & S_IRGRP)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "Group has write permission on oldfile: ", strlen("Group has write permission on oldfile: "));
            if (file2.st_mode & S_IWGRP)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            write(2, "Group has execute permission on oldfile: ", strlen("Group has execute permission on oldfile: "));
            if (file2.st_mode & S_IXGRP)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            // write(2,"\n\n",2);
            // permission under Others
            write(2, "Others has read permissions on oldfile: ", strlen("Others has read permissions on oldfile: "));
            if (file2.st_mode & S_IROTH)
            {
                write(2, "Yes\n", strlen("Yes\n"));
            }
            else
            {
                write(2, "No\n", strlen("No\n"));
            }
            write(2, "Others has write permission on oldfile: ", strlen("Others has write permission on oldfile: "));
            if (file2.st_mode & S_IWOTH)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n"), 4);
            }
            write(2, "Others has execute permission on oldfile: ", strlen("Others has execute permission on oldfile: "));
            if (file2.st_mode & S_IXOTH)
            {
                write(2, ("Yes\n"), 4);
            }
            else
            {
                write(2, ("No\n\n"), 4);
            }
        }
        // dir = stat((arg[1]), &file1);

        // if (S_ISDIR(file1.st_mode) != 0)
        //{
        // permission under User
        write(2, "User has read permissions on directory: ", strlen("User has read permissions on directory: "));
        if (file1.st_mode & S_IRUSR)
        {
            write(2, "Yes\n", strlen("Yes\n"));
        }
        else
        {
            write(2, "No\n", strlen("No\n"));
        }
        write(2, "User has write permissions on directory: ", strlen("User has write permissions on directory: "));
        if (file1.st_mode & S_IWUSR)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
        write(2, "User has execute permissions on directory: ", strlen("User has execute permissions on directory: "));
        if (file1.st_mode & S_IXUSR)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
        // write(2,"\n\n",2);
        //  permission under Group
        write(2, "Group has read permissions on directory: ", strlen("Group has read permissions on directory: "));
        if (file1.st_mode & S_IRGRP)
        {
            write(2, "Yes\n", strlen("Yes\n"));
        }
        else
        {
            write(2, "No\n", strlen("No\n"));
        }
        write(2, "Group has write permissions on directory: ", strlen("Group has write permissions on directory: "));
        if (file1.st_mode & S_IWGRP)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
        write(2, "Group has execute permissions on directory: ", strlen("Group has execute permissions on directory: "));
        if (file1.st_mode & S_IXGRP)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
        // permission under Others
        write(2, "Others has read permissions on directory: ", strlen("Others has read permissions on directory: "));
        if (file1.st_mode & S_IROTH)
        {
            write(2, "Yes\n", strlen("Yes\n"));
        }
        else
        {
            write(2, "No\n", strlen("No\n"));
        }
        write(2, "Others has write permissions on directory: ", strlen("Others has write permissions on directory: "));
        if (file1.st_mode & S_IWOTH)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
        write(2, "Others has execute permissions on directory: ", strlen("Others has execute permissions on directory: "));
        if (file1.st_mode & S_IXOTH)
        {
            write(2, ("Yes\n"), 4);
        }
        else
        {
            write(2, ("No\n"), 4);
        }
    }
    else
    {
        write(2, "Directory doesn't exists or the given file is not directory\n", strlen("Directory doesn't exists or the given file is not directory\n"));
    }
    return (0);
}
