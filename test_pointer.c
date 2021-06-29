#include <stdio.h>
#include <stdlib.h>

typedef struct s_arg
{
	int count;
//	int i;
} t_arg ;

int main(void)
{
	t_arg *var;

	//var = (t_arg *)malloc(sizeof(t_arg) * 5);
	var->count = 5;
	printf("%d", var->count);
}