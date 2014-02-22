#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
	char c;
	char *str1 = "First call\n";
	char *str2 = "Second call\n";

	printf("I am the target and my pid is: %d\n", getpid());
	write(1, str1, strlen(str1));
	read(0, &c, 1);
	write(1, str2, strlen(str2));
	return (0);
}