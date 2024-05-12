#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stddef.h>

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
	char	**path;
        int     cmd_num;
	int	*pipes;
        t_cmd   *cmds;
}       t_pipex;

#endif
