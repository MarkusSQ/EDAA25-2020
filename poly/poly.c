#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "error.h"
#include "poly.h"

struct poly_t
{
	int size;
	int *coeff;
};

poly_t *new_poly_from_string(const char *str)
{
	int *coeff = NULL;
	int size = 0;
	int digit = 0;
	int sign = 1;
	int i = 0;
	char c;
	while((c = str[i]) != 0) { //kolla om c blir 0 första rundan
		i++;
		if (isdigit(c))
		{
			digit = 10 * digit + (c-'0');
		}
		else if (c != '^' && c != ' ')
		{
			coeff = realloc(coeff, sizeof(int) * (size + 1));
			*(coeff+size++) = sign * ((!digit) ? 1 : digit);
			digit = 0;

			sign = (c == 'x') ? 1 : -(c - 44);
		}
	}
	coeff = realloc(coeff, sizeof(int) * (size + 1));
	*(coeff + size++) = 0;
	

	struct poly_t *poly = malloc(sizeof(struct poly_t));
	poly->coeff = coeff;
	poly->size = size;
	return poly;
}

void free_poly(poly_t *poly)
{
	free(poly->coeff);
	free(poly);
}

poly_t* mul(poly_t *p1, poly_t *p2)
{
	int size1 = p1->size;
	int size2 = p2->size;

	//poly_t *prod = calloc((size1+size2), sizeof(int));

	struct poly_t *prod = calloc((size1+size2), sizeof(int));
	prod->coeff = calloc((size1+size2), sizeof(int));

	for (int i = 0; i<size1; i++)
	{
		for (int j = 0; j<size2; j++)
		{
			prod->coeff[i+j] += p1->coeff[i] * p2->coeff[j];
		}
	}
	prod->size = size1+size2;
	return prod;
}

void print_poly(poly_t *poly)
{
	for (int i = 0; i < poly->size; i++)
	{
		if (poly->coeff[i] != 0)
		{
			printf("x^%d", poly->coeff[i]);
		}
	}
}

static void poly_test(char* a, char* b)
{
	poly_t* p;
	poly_t* q;
	poly_t* r;
	printf("Begin polynomial test of (%s) * (%s)\n", a, b);
	p = new_poly_from_string(a);
	q = new_poly_from_string(b);
	print_poly(p);
	print_poly(q);
	r = mul(p, q);
	print_poly(r);
	free_poly(p);
	free_poly(q);
	free_poly(r);
	printf("End polynomial test of (%s) * (%s)\n\n\n", a, b);
}
int main(void)
{
	poly_test("x^2 - 7x + 1", "3x + 2");
	poly_test("x^10000000 + 2", "2x^2 + 3x + 4");
	return 0;
}
