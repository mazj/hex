/* HEX Preprocessor */
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 200

char* trim(char * s) {
	//size_t l = strlen(s);
	// while(l && isspace(s[l-1])) s[--l] = '\0';
	// while(*s && isspace(*s)) *s = '\0', ++s;
	size_t l = strlen(s);
	while(l > 1 && isspace(s[l-1])) s[--l] = '\0';
	while(*s && isspace(*s)) *s = '\0',++s;
	return s;
}

static process_line(char* line) {
	
}

int main(int argc, char const *argv[])
{
	char s[] = " abd ";
	printf("%s: %u\n", s, strlen(s));
	char* c = trim(s);
	printf("%s: %u\n", c, strlen(c));
	FILE* fin;
	char buf[BUF_SIZE];
	unsigned int lineNum = 1;
	fin = fopen("tests/lexer_test_class_01.hex", "rt");
	if(fin) {
		while(fgets(buf, sizeof(buf), fin)) {
			printf("%d: %s", lineNum, buf);
			printf("%d: %s\n", lineNum, trim(buf));
			lineNum++;
		}
	} else {
		printf("ERROR READING FILE.\n");	
	}
	fclose(fin);
	return 0;
}