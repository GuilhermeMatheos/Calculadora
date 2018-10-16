#include <stdlib.h>
#include <stdio.h>

int soma(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mult(int a, int b) {
    // multiplicacao recursiva
    if (a == 0 || b == 0) {
    	return 0;
	}

    return a + (a * (b-1));
}

int divisao(int a, int b) {
    // divisao inteira
    return a / b;
}

int string_to_int(char *s) {
    return atoi(s);
}

char* int_to_string(int x) {
    int tamanho = snprintf(NULL, 0, "%d", x);
    char *s = (char *)malloc(tamanho+1);
    itoa(x, s, 10);
    return s;
}
