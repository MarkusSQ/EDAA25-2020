#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N		(10)

int stack[N];
int size;
int input;
int val;
int nuse;
bool lastop;
bool num;
bool err; 
unsigned line; 

/*Fixa:
- operatorer utan mellanrum
- newline utan annat
*/


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
	fflush(stdin);
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
	//nuse = 0;
	num = false;
	err = false;
	lastop = false;

	while ((input = getchar ()) != EOF) {
		printf("a,");
		if (err) {
			errnewline:
			if (input == '\n') {
				line +=1;
				err = 0;

				/*while(size != 0) {
					pop();
				}*/

				size = 0;
				//nuse = 0;
				num = 0;
				fflush(stdin);
				//printf("errn, %d", pop());
			}

			continue;
		} else if (isdigit(input)) {
			printf("digit,");
			val = val * 10 + input - '0'; //c är tecknet för siffran vi läste in, val blir med numeriskt värde. Eval 124: val= 0; val=10*0+1 =1; val =10*1+2=12; val=10*12+4 = 124; Om vi inte får nytt digit har vi '0' vilket vi tar bort
			printf("val:%d,", val);
			num = true;
			lastop = false;
			continue;
		} else if (num) {
			printf("num,");
			if (size == N) { //if (size == N || nuse >= 2) {
				//fflush(stdout);
				//fflush(stdin);
				error(__LINE__, '0' + val%10, &err);
				val = 0;
				num = false;
				lastop = false;
				//goto errnewline;
				continue;
			}else {
				push(val);
				//nuse++;
				val = 0;
				num = false;
				lastop = false;
			}
		} else {
			printf("operator,");
			num = false;
			int tmp;
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
						/*if((nuse == 0 && !lastop) || (nuse >= 2 && lastop)){
							error(__LINE__, input, &err);
							goto errnewline;
						}*/
						/*if (size != 1) {
							error(__LINE__, input, &err);
						}*/
						printf("Result: %d \nInput:", pop());
						errnline:
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
