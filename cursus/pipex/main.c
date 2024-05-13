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
void	execute(t_pipex *data, int i)
{
	int	fd_in;
	int	fd_out;

	if (data->cmds[i].first)
	{
		fd_in = open(data->in_file, O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(data->pipes[i * 2 - 2], STDIN_FILENO);
		close(data->pipes[i * 2 - 2]);
	}
	if (data->cmds[i].last)
	{
		fd_out = open(data->out_file, O_WRONLY);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
	{
		dup2(data->pipes[i * 2 + 1], STDOUT_FILENO);
		close(data->pipes[i * 2 + 1]);
	}
	if (execve(data->cmds[i].path, data->cmds[i].cmd_flags, data->env) == -1)
		perror("execve");
}

//Searches for the PATH environment variable and stores it
void	get_path(char **env, t_pipex *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	data->path = ft_split(env[i] + 5, ':');
	if (!data->path)
		error_exit("Malloc error\n"); //TODO free data
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
		if (!complete_path)
			error_exit("Malloc error"); //TODO free data
		final_path = ft_strjoin(complete_path, cmd);
		if (!final_path)
			error_exit("Malloc error"); //TODO free data
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
char	**get_cmd_flags(char *arg, t_pipex *data)
{
	char	**cmd_flags;

	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error_exit("Malloc error\n"); //TODO free data
	return (cmd_flags);
}

//Create the necessary pipes for communication between processes
void	generate_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_num)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			error_exit("Error creating pipes.\n"); //TODO free data
		i++;
	}
}

//Initializes the structures with the necessary data
void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	if (argc < 5)
		error_exit("ARGS ERROR\n"); //TODO free data
	get_path(env, data);
	data->cmd_num = argc - 3;
	data->cmds = malloc((data->cmd_num) * sizeof(t_cmd));
	data->out_file = ft_strdup(argv[argc - 1]);
	data->in_file = ft_strdup(argv[1]);
	data->pipes = malloc(data->cmd_num * 2 * sizeof(int));
	if (!data->cmds || !data->pipes || !data->out_file || !data->in_file)
		error_exit("Malloc error\n"); //TODO free data
	generate_pipes(data);
	i = 0;
	while (i < data->cmd_num)
	{
		data->cmds[i].first = 0;
		data->cmds[i].last = 0;
		data->cmds[i].cmd_flags = get_cmd_flags(argv[2 + i], data);
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
	int	i;
	int	pid;
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
		error_exit("Malloc error\n");
	init_data(data, argc, argv, env);
	check_args(argc, argv, data);
	i = 0;
	while (i < data->cmd_num)
	{
		pid = fork();
		if (pid == 0)
			execute(data, i);
		else if (pid == -1)
			perror("fork"); //TODO free data
		i++;
	}
	wait(NULL);
	//TODO FREE DATA
	return (0);
}
