#define _XOPEN_SOURCE 700


#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <getopt.h>
#include <malloc.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <string.h>
#include <unistd.h>


static int add_flag = 0;
static int del_flag = 0;
static int list_flag = 0;

void add_whitelist(const char *path)
{
    char value[2] = "1";

    if (setxattr(path, "security.whitelisted", value, strlen(value), 0) == -1)
        perror("setxattr");
}

void del_whitelist(const char *path)
{
    if (removexattr(path, "security.whitelisted") != 0)
        perror("removexattr");
}

int print_entry(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{

    if (typeflag == FTW_F)
    {
        int length = getxattr(filepath, "security.whitelisted", NULL, 0);

        if (length > 0)
            printf("%s\n", filepath);
    }

    return 0;
}
void list_whitelist(const char *directory)
{

#ifndef USE_FDS
#define USE_FDS 15
#endif


    int result = nftw(directory, print_entry, USE_FDS, FTW_PHYS);

    if (result > 0)
        perror("nftw");
}


int main(int argc, char **argv)
{
    int c;

    while (1)
    {
        static struct option long_options[] =
        {
            {"add",  no_argument, &add_flag, 1},
            {"del",  no_argument, &del_flag, 1},
            {"list", no_argument, &list_flag, 1},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:

            if (long_options[option_index].flag != 0)
                break;

        case '?':
            break;

        default:
            abort();
        }
    }

    if ((add_flag == 0) && (del_flag == 0) && (list_flag == 0))
        list_flag = 1;

    if (add_flag)
    {
        while (optind < argc)
            add_whitelist(argv[optind++]) ;
    }

    if (del_flag)
    {
        while (optind < argc)
            del_whitelist(argv[optind++]) ;
    }

    if (list_flag)
    {
        if (optind < argc)
        {
            while (optind < argc)
                list_whitelist(argv[optind++]);
        }
        else
        {
            list_whitelist(".");
        }
    }

    exit(0);
}
