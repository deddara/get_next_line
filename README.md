# get_next_line
### This functions allows you to read a file line by line.
>Function has no memory-leaks. Tested with *valgrind*
### Get starting
 - To use **get_next_line** function simply include a header file `#include "get_next_line.h"`.
 
### Funtion call example:
```
while (get_next_line(fd, &line))
{  
 printf("%s", line);  
 free(line);  
}  
printf("%s\n", line);  
free(line);
```
### Return values: 
- **1** : A line has been read
- **0** : EOF has been reached
- **-1** : An error happened
