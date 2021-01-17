#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N		(10)

static int stack[N];
static int size;
static int input;
static int val;
//static int nuse;
static bool lastop;
static bool num;
static bool err; 
static unsigned line; 


static void error(unsigned int line, int c, bool* err)
{
	char buf[3];

	if (input== '\n') {
		strcpy(buf, "\\n");
	}
	else {
		buf[0] = c;
		buf[1] = 0;
	}

	printf("line %u: error with cause: %s\nInput:", line, buf) ;

	*err = true;
	//fflush(stdin);
}

void push(int value)
{
	if (size >= 10) {
		error(__LINE__, input, &err);
	}
	printf("pu,");
	stack[++size] = value;
	printf("%d,", stack[size]);
}

int pop()
{
	printf("stack[i]: %d,", stack[size]);
	if (size <= 0) {
		error(__LINE__, input, &err);
	}
	return stack[size--];
}

int main(void)
{
	
	printf("Input:");
	val = 0;
	size = 0;
	line = 1;
	num = false;
	err = false;
	lastop = false;

	while ((input = getchar ()) != EOF) {
		printf("a,");
		if (err) {
			//errnewline:
			//if (input == '\n') {
				line +=1;
				err = false;
				size = 0;
				num = false;
				//fflush(stdin);
			//}

			continue;
		} else if (isdigit(input)) {
			printf("digit,");
			val = val * 10 + input - '0';
			printf("val:%d,", val);
			num = true;
			lastop = false;
			continue;
		} else if (num && input == ' ') {
			printf("num,");
			if (size == N) {
				error(__LINE__, '0' + val%10, &err);
				val = 0;
				num = false;
				lastop = false;
				continue;
			}else {
				push(val);
				val = 0;
				num = false;
				lastop = false;
				printf("pushnum");
			}
		} else {
			num = false;
			int tmp;
			printf("operator,");
			switch (input) {
				case '+':
						lastop = true;
						printf("plus,");
						push(pop()+pop());
						printf("test");
						break;
				case '-':
						printf("minus,");
						lastop = true;
						tmp = pop();
						push(pop() - tmp);
						break;
				case '*':
						printf("mult,");
						lastop = true;
						push(pop()*pop());
						break;
				case '/':
						lastop = true;
						printf("div,");
						if ((tmp = pop()) == 0) {
							error(__LINE__, input, &err);
							goto errdiv;
						}
						push(pop() / tmp);
						errdiv:
						break;
				case ' ':
						lastop = true;
						printf("blank,");
						break;
				case '\n':
						printf("Result: %d \nInput:", pop());
						//errnline:
						line++;
						break;
				default:
						printf("default,");
						error(__LINE__, input, &err);
						break;

			}
		}
	}
	

	int p = pop();
	printf("Result: %d", p);
	return p;
}
