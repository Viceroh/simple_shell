#include "viceroh.h"

/**
* in_cd - checks if : is in the current dir.
* @path: xter pointer
* @i: type int of the pointer
* Return: 1 is returned if cd is searchable and otherwise if its zero
*/
int in_cd(char *path, int *i)
{
if (path[*i] == ':')
return (1);

while (path[*i] != ':' && path[*i])
{
*i += 1;
}

if (path[*i])
*i += 1;

return (0);
}

/**
* _which - it locates the cmd
*
* @cmd: name of the command
* @_environ: The environment var.
* Return: location of cmd.
*/
char *_which(char *cmd, char **_environ)
{
char *path, *ptr_path, *token_path, *dir;
int len_dir, len_cmd, i;
struct stat st;

path = _getenv("PATH", _environ);
if (path)
{
ptr_path = _strdup(path);
len_cmd = _strlen(cmd);
token_path = _strtok(ptr_path, ":");
i = 0;
while (token_path != NULL)
{
if (in_cd(path, &i))
if (stat(cmd, &st) == 0)
return (cmd);
len_dir = _strlen(token_path);
dir = malloc(len_dir + len_cmd + 2);
_strcpy(dir, token_path);
_strcat(dir, "/");
_strcat(dir, cmd);
_strcat(dir, "\0");
if (stat(dir, &st) == 0)
{
free(ptr_path);
return (dir);
}
free(dir);
token_path = _strtok(NULL, ":");
}
free(ptr_path);
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}
if (cmd[0] == '/')
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}

/**
* if_exec - determine if it is  executable
*
* @datash: data struct
* Return: 0 if isnt executable, other if isnt
*/
int if_exec(data_shell *datash)
{
struct stat st;
int i;
char *input;

input = datash->args[0];
for (i = 0; input[i]; i++)
{
if (input[i] == '.')
{
if (input[i + 1] == '.')
return (0);
if (input[i + 1] == '/')
continue;
else
break;
}
else if (input[i] == '/' && i != 0)
{
if (input[i + 1] == '.')
continue;
i++;
break;
}
else
break;
}
if (i == 0)
return (0);

if (stat(input + i, &st) == 0)
{
return (i);
}
get_error(datash, 127);
return (-1);
}

/**
* check_error_cmd - verifies if the user has permission
*
* @dir: destination dir.
* @datash: data struct.
* Return: 1 returned on error zero if not
*/
int check_error_cmd(char *dir, data_shell *datash)
{
if (dir == NULL)
{
get_error(datash, 127);
return (1);
}

if (_strcmp(datash->args[0], dir) != 0)
{
if (access(dir, X_OK) == -1)
{
get_error(datash, 126);
free(dir);
return (1);
}
free(dir);
}
else
{
if (access(datash->args[0], X_OK) == -1)
{
get_error(datash, 126);
return (1);
}
}

return (0);
}

/**
* cmd_exec - lines of commands are executed
*
* @data: Releveant dat
* Return: 1 on success is returned .
*/
int cmd_exec(data_shell *datash)
{
pid_t pd;
pid_t wpd;
int state;
int exec;
char *dir;
(void) wpd;

exec = if_exec(datash);
if (exec == -1)
return (1);
if (exec == 0)
{
dir = _which(datash->args[0], datash->_environ);
if (check_error_cmd(dir, datash) == 1)
return (1);
}

pd = fork();
if (pd == 0)
{
if (exec == 0)
dir = _which(datash->args[0], datash->_environ);
else
dir = datash->args[0];
execve(dir + exec, datash->args, datash->_environ);
}
else if (pd < 0)
{
perror(datash->av[0]);
return (1);
}
else
{
do {
wpd = waitpid(pd, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}

datash->status = state / 256;
return (1);
}
