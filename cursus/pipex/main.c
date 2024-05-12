#include "pipex.h"

//Writes an error message and ends the program
void	error_exit(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

//Checks the arguments and permissions of input and output files
void	check_args(int argc, char **argv, t_pipex *data)
{
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
	else
	{
		if (open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
			perror("open");
	}
}

//Manages the incoming and outgoing fd's and executes the command
void	execute(int pid, int pipe[2], t_pipex *data, int i)
{
	int	fd_in;
	int	fd_out;

        if (pid == 0) //Child
        {
		printf("Child_%d: %s\n", i, data->cmds[i].cmd_flags[0]);
                if (data->cmds[i].first)
		{
		//	close(pipe[0]);
			fd_in = open(data->in_file, O_RDONLY);
                	dup2(fd_in, STDIN_FILENO);
                	close(fd_in);
                	dup2(pipe[1], STDOUT_FILENO);
		//	close(pipe[1]);
		}
		else if (data->cmds[i].last)
		{
		//	close(pipe[1]);
			dup2(pipe[0], STDIN_FILENO);
			if (data->out_file)
			{
			fd_out = open(data->out_file, O_WRONLY);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			}
		//	close(pipe[0]);
		}
		close(pipe[0]);
		close(pipe[1]);
		if (execve(data->cmds[i].path, data->cmds[i].cmd_flags, data->env) == -1)
			perror("execve");
	}
        else if (pid == -1)
                perror("fork");
}

//Searches for the PATH environment variable and stores it
void	get_path(char **env, t_pipex *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			printf("%s\n", env[i]);
			break;

		}
		i++;
	}
	data->path = ft_split(env[i] + 5, ':');
	if (!data->path)
		error_exit("Malloc error\n");
}

//Search within the environment paths where the command is located
char	*get_cmd_path(t_pipex *data, char *cmd)
{
	int	i;
	char	*complete_path;
	char	*final_path;

	i = 0;
	while (data->path[i])
	{
		complete_path = ft_strjoin(data->path[i], "/");
		final_path = ft_strjoin(complete_path, cmd);
		free(complete_path);
		complete_path = NULL;
		if (access(final_path, F_OK) != -1)
				return (final_path);
		free(final_path);
		final_path = NULL;
		i++;
	}
	return (NULL);
}

//Split command name and flags
char	**get_cmd_flags(char *arg)
{
	char	**cmd_flags;

	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error_exit("Malloc error\n");
	return (cmd_flags);	
}

//Initializes the structures with the necessary data
void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	if (argc < 5)
		error_exit("ARGS ERROR\n");
	get_path(env, data);
	data->cmd_num = argc - 3;
	data->cmds = malloc((data->cmd_num) * sizeof(t_cmd));
	data->out_file = ft_strdup(argv[argc - 1]);
	data->in_file = ft_strdup(argv[1]);	
	if (!data->cmds)
		error_exit("Malloc error\n");
	i = 0;
	while (i < data->cmd_num)
	{
		data->cmds[i].first = 0;
		data->cmds[i].last = 0;
		data->cmds[i].cmd_flags = get_cmd_flags(argv[2 + i]);
		data->cmds[i].path = get_cmd_path(data, data->cmds[i].cmd_flags[0]);
		i++;
	}
	data->cmds[0].first = 1;
	data->cmds[data->cmd_num - 1].last = 1;
	data->env = env;
}

//Main function
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

	data = malloc(sizeof(t_pipex));
	if (!data)
		error_exit("Malloc error\n");
	printf("Before init data\n");
	init_data(data, argc, argv, env);
	printf("after init data\n");
	check_args(argc, argv, data);
	printf("After check_args()\n");
	if (pipe(fd) == -1)
		error_exit("PIPE ERROR\n");
	i = 0;
	while (i < data->cmd_num)
	{
		pid = fork();
		execute(pid, fd, data, i);
		i++;
	}
	wait(NULL);
	//CLEANUP TODO
	return (0);
}
