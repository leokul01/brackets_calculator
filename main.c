#include "ft_prototypes.h"

int		main(int argc, char **argv)
{
	if (argc == 2)
		ft_putnbr(eval_expr(argv[1]));
	ft_putchar('\n');
	return (0);
}
