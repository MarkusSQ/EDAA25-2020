#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //problem som kvarstår: Man måste lägga till enter för att få korrekt resultat
#include <string.h>

#define N		(10)

static int stack[N];
static int size;
static int input;
static int val;
static bool space = false;
static int ouse = 0;
static int nuse = 0;
static bool lastop;
static bool num;
static bool err; 
static bool special = false;
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

	printf("line %u: error at %s\n", line, buf);

	*err = true;
}

void push(int value)
{
	if (size >= 10 || special == true) {
		error(line, input, &err);
	} else {
		stack[size++] = value;
	}
}

int pop()
{
	if (size <= 0) {
		error(line, input, &err);
	}
	return stack[--size];
}

int main(void)
{
	val = 0;
	size = 0;
	line = 1;
	num = false;
	err = false;
	lastop = false;

	while ((input = getchar ()) != EOF) {
		if (err) {
			errnewline:
			line +=1;
			err = false;
			size = 0;
			num = false;
			continue;
		} else if (isdigit(input)) {
			val = val * 10 + input - '0';
			num = true;
			lastop = false;
		} 
		else {
			int tmp;
			if (num) {
				if (size >= N) {
					error(line, '0' + val%10, &err);
					val = 0;
					num = false;
					space = false;
					while ((input = getchar()) != '\n') {

					}
					goto errnewline;
				}else {
					push(val);
					nuse++;
					val = 0;
					space = false;
					num = false;
				}

			}
			if (input != ' ') {
				ouse++;
			}

			switch (input) {
				case '+':
				lastop = true;
				push(pop()+pop());
				break;
				case '-':
				lastop = true;
				tmp = pop();
				push(pop() - tmp);
				break;
				case '*':
				lastop = true;
				push(pop()*pop());
				break;
				case '/':

				lastop = true;
				if ((tmp = pop()) == 0) {
					error(line, input, &err);
					goto errdiv;
				}
				push(pop() / tmp);
				errdiv:
				break;
				case ' ':
				space = true;
				lastop = true;
				break;
				case '\n':
				if (nuse - ouse > 1  || nuse - ouse < 0) {
					nuse = ouse = 0;
					error(line, input, &err);
					val = 0;
					goto errnewline;
				}
				nuse = ouse = 0;
				int p = pop();
				if (err) {
					line++;

					goto errnewline;
				} else if (size >= 1) {
					error(line, input, &err);
					goto errnewline;
				} else {
					printf("line %u: %d\n", line, p);
					line++;
				}

				break;

				case '!':
				error(line-1, input, &err);
				break;

				default:
				error(line, input, &err);
				while ((input = getchar()) != '\n') {

				}
				nuse = ouse = 0;
				goto errnewline;

			}
		}
	}
	

	//int p = pop();
	//printf("line %u: %d \n", line, p);
	return 0;
}
