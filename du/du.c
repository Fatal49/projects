#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

int du(const char *reldirpath, ino_t **inodearr, size_t *inodearrSize);
char* append(const char *str, const char *strToAppend);

int main(int argc, char **argv) {
    size_t inodearrSize = 5;
    ino_t *inodearr = malloc(sizeof(ino_t) * inodearrSize);
    if (inodearr == NULL) {
        perror("malloc"); 
        exit(EXIT_FAILURE);
    }

    if (argc == 1)
        fprintf(stdout, "%d\t%s\n", du(".", &inodearr, &inodearrSize), "."); 
    else if (argc == 2)
        fprintf(stdout, "%d\t%s\n", du(argv[1], &inodearr, &inodearrSize), argv[1]); 
    else if (argc > 2) {
        fprintf(stdout, "Usage: %s <pathname>\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    free(inodearr);
    exit(EXIT_SUCCESS);
}

char* append(const char *str, const char *strToAppend) {
    // Allocate memory for the new str, clear it and get
    // the lengths of the given strs
    char *compstr = malloc(sizeof(char) * (PATH_MAX + NAME_MAX + 2));

    // Error check
    if (compstr == NULL) {
        perror("malloc"); 
        exit(EXIT_FAILURE); 
    }

    memset(compstr, '\0', PATH_MAX + NAME_MAX + 2);
    int strLen = strlen(str), strToAppendLen = strlen(strToAppend);

    // Copy over the first string
    strncpy(compstr, str, strLen);

    // Add a '/' if there is none
    char *ptrToAppendStart;
    if (str[strLen - 1] != '/') {
        compstr[strLen] = '/';
        ptrToAppendStart = compstr + (strLen + 1);
    } else
        ptrToAppendStart = compstr + strLen;

    // Copy over the second string
    strncpy(ptrToAppendStart, strToAppend, strToAppendLen);

    // Return the new string (don't forget to free it)
    return compstr;
}

int du(const char *reldirpath, ino_t **inodearr, size_t *inodearrSize) {
    DIR *dirp;
    struct dirent *de;
    struct stat finfo;
    char *absdirpath;
    int ts = 0, counter = 0;

    // Open the directory
    if ((dirp = opendir(reldirpath)) == NULL) {
        perror("du"); 
        exit(EXIT_FAILURE); 
    }

    // Allocate space and get the absolute path
    // to the given dir
    if ((absdirpath = malloc(sizeof(char) * PATH_MAX)) == NULL) {
        perror("malloc"); 
        exit(EXIT_FAILURE); 
    }
    if (realpath(reldirpath, absdirpath) == NULL) {
        perror("realpath");    
        exit(EXIT_FAILURE); 
    }

    while ((de = readdir(dirp)) != NULL) {
        // Allocate space for the absolute path to the file
        char *absfilepath = append(absdirpath, de->d_name);

        // Get the information about the file
        if (stat(absfilepath, &finfo) != -1) {
            switch (finfo.st_mode & S_IFMT) {
                // If the file is a softlink (Symbolic link)
                case S_IFLNK: ts += finfo.st_blocks; break; 

                // If the file is a regular file (including hard links)
                case S_IFREG: {
                    // If its a regular file or an executable
                    // add its size and break
                    if (finfo.st_nlink <= 1) {
                        ts += finfo.st_blocks;         
                        break;
                    } else {
                        // If space is needed in the array allocate it
                        _Bool found = FALSE;
                        if (counter == (*inodearrSize - 1)) {
                            if ((*inodearr = realloc(*inodearr, *inodearrSize + 5)) == NULL) {
                                perror("realloc"); 
                                exit(EXIT_FAILURE);
                            }
                            *inodearrSize += 5;
                        } 

                        // Search the array for the inode #
                        for (int i = 0; i < *inodearrSize; i++) {
                            // If found break
                            if ((*inodearr)[i] == de->d_ino) {
                                found = TRUE;
                                break;
                            }
                        } 

                        // If not found add it to the array
                        // and add its size
                        if (found == FALSE) {
                            (*inodearr)[counter] = de->d_ino;
                            counter++;
                            ts += finfo.st_blocks;
                        }

                        // Reset the flag
                        found = FALSE;
                    }
                } break; 

                // If the file is a directory
                case S_IFDIR: {;
                    // If the dir is either "." or ".." skip it 
                    if ((strncmp(de->d_name, ".", 1) == 0 && strlen(de->d_name) == 1) || 
                            (strncmp(de->d_name, "..", 2) == 0 && strlen(de->d_name) == 2))
                        break;
                    else {
                        // Get the absolute dir path
                        char *relpath = append(reldirpath, de->d_name); 

                        // Call ourself using the new dir path
                        int dirTotal = du(relpath, inodearr, inodearrSize);

                        // Print the dir size and relative path
                        fprintf(stdout, "%d\t%s\n", dirTotal, relpath);

                        // Free the data and add its size to the total size
                        free(relpath);
                        ts += dirTotal;
                    }
                } break;
            }
        }
        // Free the absolute path to the file
        free(absfilepath);
    }

    // Free up memory
    free(absdirpath);
    return ts;
}
