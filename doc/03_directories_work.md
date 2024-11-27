- [[#getcwd]]
- [[#chdir]]
## getcwd

Una función simple que nos devuelve el path de trabajo actual. 

Su prototipo es:

```c
 **char *getcwd(char** _buf_**[.**_size_**], size_t** _size_**);**
```

Y un ejemplo de uso:

```c
#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}
```

Este sería el output que genera el ejemplo:

![[Pasted image 20241127123251.png]]

## chdir

Con esta función podemos cambiar el actual directorio de trabajo llamando al proceso del directorio especificado en el `path`.

Su prototipo es:

```c
**#include <unistd.h>**

**int chdir(const char ***_path_**);**
```

Retornará 0 en caso de que el cambio sea OK y -1 si ha fallado.

Un ejemplo de uso (incremento el ejemplo anterior para mas visibilidad):

```c
#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>

int main() {
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;	
	}

	if (chdir("/home/ziko/") < 0)
		printf("Error changing directory\n");
	else
		printf("Directory change OK\n");

	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;	
	}
	return 0;
}
```

Y este sería el output que me generaría:

![[Pasted image 20241127125032.png]]

> Nótese que después de la ejecución del programa, sigo en mi directorio de trabajo, sólo cambia para el trabajo del propio programa, no para la bash que estemos usando en ese momento, es decir, no sirve para ordenar a bash cambios de directorios, si no que es una temporalidad durante la ejecución del programa.