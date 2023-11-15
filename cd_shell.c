#include "viceroh.h"

/**
* cd_shell - changes current dir.
*
* @datash: important data
* Return: 1 is returned on sucess
*/
int cd_shell(data_shell *datash)
{
char *dir;
int ishome, ishome2, isddash;

dir = datash->args[1];

if (dir != NULL)
{
ishome = _strcmp("$HOME", dir);
ishome2 = _strcmp("~", dir);
isddash = _strcmp("--", dir);
}

if (dir == NULL || !ishome || !ishome2 || !isddash)
{
cd_home(datash);
return (1);
}

if (_strcmp("-", dir) == 0)
{
cd_prev(datash);
return (1);
}

if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
{
cd_do(datash);
return (1);
}

cd(datash);

return (1);
}
