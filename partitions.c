#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef	struct storage
{
	char*				str;
	int					size;
} calcul;

#define ANSI_Color_Black	"\x1b[30m"
#define ANSI_Color_Red		"\x1b[31m"
#define ANSI_Color_Green	"\x1b[32m"
#define ANSI_Color_Yellow	"\x1b[33m"
#define ANSI_Color_Blue		"\x1b[34m"
#define ANSI_Color_Magenta	"\x1b[35m"
#define ANSI_Color_Cyan		"\x1b[36m"
#define ANSI_Color_White	"\x1b[37m"
#define ANSI_Color_Reset	"\x1b[0m"

#define	ANSI_Background_Black	"\x1b[40m"
#define	ANSI_Backgroung_Red		"\x1b[41m"


int		calculator(int all_size, float pourcentage)
{
	float	size;
	int		res;

	size = (float)all_size;
	size = (size * pourcentage) / 100;
	res = (int)size;
	return (res);
}

int my_atoi(char* str)
{
	int res;

	res = 0;
	while (str && *str)
	{
		if (*str >= '0' && *str <= '9')
		{
			res = res * 10 + *str - 48;
			str++;
		}
		else
			return (0);
	}
	return (res);
}

calcul*	create_node(char* str)
{
	calcul*	node;
	int		size;
	int		z;

	z = 0;
	if (!str)
		return (NULL);
	size = strlen(str);
	node = (calcul *)malloc(sizeof(calcul));
	if (!node)
		return (NULL);
	node->str = malloc(sizeof(char) * (size + 1));
	if (!node->str)
		return (NULL);
	while (str && str[z])
	{
		node->str[z] = str[z];
		z++;
	}
	node->str[z] = '\0';
	node->size = 0;
	return (node);
}

void bonus_part(int all_size, int size_used)
{
	calcul*	var = create_node("var");
	calcul*	srv = create_node("srv");
	calcul*	tmp = create_node("tmp");
	calcul*	var_log = create_node("var-log");
	int size;

	var->size = calculator(all_size, 9.74);
	srv->size = calculator(all_size, 9.74);
	tmp->size = calculator(all_size, 9.74);
	size = all_size - (size_used + var->size + srv->size + tmp->size);
	var_log->size = size;
	printf(ANSI_Color_Green "  %s\t\t", var->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", var->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t\t", srv->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", srv->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t\t", tmp->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", tmp->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t", var_log->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", var_log->size);
	printf(ANSI_Color_Blue "\n|");
}

void mandatory_part(int all_size)
{
	calcul*	boot = create_node("boot");
	calcul*	root = create_node("root");
	calcul*	swap = create_node("swap");
	calcul*	home = create_node("home");
	int	size_used;

	size_used = 0;
	if (all_size >= 31539)
	{
		boot->size = calculator(all_size, 1.59);
		root->size = calculator(all_size, 32.48);
		swap->size = calculator(all_size, 7.47);
		home->size = calculator(all_size, 16.24);
		size_used = boot->size + root->size + swap->size + home->size;
	
	}
	else
	{
		boot->size = calculator(all_size, 5.95);
		root->size = calculator(all_size, 35.00);
		swap->size = calculator(all_size, 11.92);
		size_used = all_size  - (boot->size + root->size + swap->size + home->size);
		home->size = size_used;
	}
	printf(ANSI_Color_Green "  %s\t\t", boot->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", boot->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t\t", root->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", root->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t\t", swap->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", swap->size);
	printf(ANSI_Color_Blue "\n|");
	printf(ANSI_Color_Green "  %s\t\t", home->str);
	printf(ANSI_Color_Blue "|\t");
	printf(ANSI_Color_Green "%d MB", home->size);
	printf(ANSI_Color_Blue "\n|");
	if (all_size >= 31539)
		bonus_part(all_size, size_used);
}

void partition_ruslt()
{
	char	str[5];
	int		all_size;

	printf(ANSI_Color_Green "\t\tSet up partition\n");
	printf(ANSI_Color_Blue "1 ==> Gonfigure the Logical Volume Manager\n2 ==> Create volume group\n");
	do
	{
		printf(ANSI_Color_Green "\nEnter size of your partition on MB = ");
		scanf("%s", str);
		all_size = my_atoi(str);
		if (!all_size)
			printf(ANSI_Color_Red "size is numeric!!!");
		else if (all_size < 8192)
			printf(ANSI_Color_Yellow "size is small!!!");
	}
	while (all_size < 8192);
	printf(ANSI_Color_Blue "___________________________________________\n|\n|");
	printf(ANSI_Color_Green "\t Global Storage = %d MB\n", all_size);
	printf(ANSI_Color_Blue "|__________________________________________\n|");
	mandatory_part(all_size);

}

int		main(void)
{
//	printf(ANSI_Color_Red "Red\n");
//	printf(ANSI_Color_Green "Green\n");
//	printf(ANSI_Color_Yellow "Yellow\n");
//	printf(ANSI_Color_Blue "Blue\n");
//	printf(ANSI_Color_Magenta "Magenta\n");
//	printf(ANSI_Color_Cyan "Cyan\n");
	partition_ruslt();
}
