#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct s_cmd
{
        char    **cmd_flags;
        char    *path;
        int     first;
        int     last;
}       t_cmd;

typedef struct s_pipex {
        char    *in_file;
        char    *out_file;
        char    **env;
        int     cmd_num;
        t_cmd   *cmds;
}       t_pipex;

char	**ft_split(char const *str, char c);

#endif
