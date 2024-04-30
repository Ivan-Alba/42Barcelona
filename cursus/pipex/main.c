#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!cpy)
		return (NULL);
	while (s[i] != '\0')
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

void	error_exit(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

void	check_args(int argc, char **argv, t_pipex *data)
{
	int	i;

	if (argc < 5)
		error_exit("ARGS ERROR\n");
	i = 0;
	while (i < data->cmd_num)
	{
		data->cmds[i].cmd_flags = ft_split(argv[i + 2], ' ');
		if (!data->cmds[i].cmd_flags)
			error_exit("Malloc error\n");
		printf("Command %d: %s\n", i, data->cmds[i].cmd_flags[0]);
		i++;
	}
	if (access(data->in_file, F_OK) == -1 || access(data->in_file, R_OK) == -1)
	{
		printf("Error infile: %s\n", data->in_file);
		data->in_file = NULL;
		perror(argv[1]);
	}
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc -1], W_OK) == -1)
	{
		data->out_file = NULL;
		perror(argv[argc - 1]);
	}
}

void	execute(int pid, int pipe[2], t_pipex *data, int i)
{
	int	fd_in;
	int	fd_out;

        if (pid == 0) //Child
        {
                if (data->cmds[i].first)
		{
			fd_in = open(data->in_file);
                	dup2(fd_in, STDIN_FILENO);
                	close(fd_in);
                	dup2(pipe[1], STDOUT_FILENO);
		}
		close(pipe[0]);
		close(pipe[1]);
                execve("/bin/cat", data->cmds[i].cmd_flags, data->env);
        }
        else if (pid == -1)
                perror("fork");
	else
		wait(NULL);	
}

void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	data->in_file = ft_strdup(argv[1]);
	data->out_file = ft_strdup(argv[argc - 1]);
	printf("INFILE: %s\n", data->in_file);
	data->cmd_num = argc - 3;
	//data->cmds = malloc((data->cmd_num) * sizeof(t_cmd));
	printf("INFILE: %s\n", data->in_file);
	if (!data->cmds)
		error_exit("Malloc error\n");
	while (i < data->cmd_num)
	{
		data->cmds[i].first = 0;
		data->cmds[i].last = 0;
		data->cmds[i].path = NULL;
		data->cmds[i].cmd_flags = NULL;
		i++;
	}
	data->cmds[0].first = 1;
	data->cmds[data->cmd_num - 1].last = 1;
	data->env = env;
}

int	main(int argc, char **argv, char **env)
{
	/*
	 * init_pipex()
	 * check_args
	 * parse_cmd()
	 * parse_args()
	 * while(cmds)
	 * 	exec()
	 * cleanup()
	 * */

	int	i;
	int	pid;
	int	fd[2];
	t_pipex	*data;

	data = malloc(sizeof(t_pipex *));
	if (!data)
		error_exit("Malloc error\n");
	init_data(data, argc, argv, env);
	check_args(argc, argv, data);

	printf("After check_args()\n");
	i = 0;
	if (pipe(fd) == -1)
		error_exit("PIPE ERROR\n");
	while (i < data->cmd_num)
	{
		pid = fork();
		execute(pid, fd, data, i);
		i++;		
	}

	/*if (pid == 0) //Child
	{
		close(fd[0]);
		int fd_o = open(argv[1]);
		dup2(fd_o, STDIN_FILENO);
		close(fd_o);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/bin/cat", cmd, env);
	}
	else if (pid == -1)
		perror("fork");
	else
	{
		close(fd[1]);
		wait(NULL); 
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		int fd_out = open(argv[argc - 1]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		printf("aqui\n");
		execve("/bin/cat", cmd, env);
	}*/
	return (0);
}
