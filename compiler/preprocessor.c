/* HEX Preprocessor */
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "esb.h"
#include "utils.h"

#define HEX_PREPROCESSOR_FILE_LINE_SIZE 200

int in_stmt_group = 0;
Node* esb_buf_head;
Node* esb_buf_tail;

static void
process_line(char *line)
{
	if(!line) {
		return;
	}

	static esb_s esb_buf;

	size_t len = strlen(line);

	if(len <= 1) {  // empty line
		if(in_stmt_group) {
			in_stmt_group = 0;
			if(!esb_buf_head) {
				esb_buf_head = MALLOC(Node);
				char *str = (char*)esb_get_string(&esb_buf);
				esb_buf_head->value = (char*)strndup(str, strlen(str));			
				esb_buf_tail = esb_buf_head;
			} else {
				Node *node = MALLOC(Node);
				char *str = (char*)esb_get_string(&esb_buf);
				node->value = (char*)strndup(str, strlen(str));	
				node->next = 0;
				if(!esb_buf_tail) {
					esb_buf_tail = MALLOC(Node);
				}
				esb_buf_tail->next = node;
				esb_buf_tail = node;
			}

			// empty string buffer
			esb_destructor(&esb_buf);
		}
	} else {  // not an empty line
		if(in_stmt_group) { // if already in stmt_group state, simply append to buffer
			esb_append(&esb_buf, line);
		} else {
			in_stmt_group = 1;
			esb_constructor(&esb_buf);
			esb_append(&esb_buf, line);
		}
	}
}

int main(int argc, char const *argv[])
{
	const char* filename = argv[1];

	esb_s esb_buf;
	esb_constructor(&esb_buf);

	FILE* fin;
	char line[HEX_PREPROCESSOR_FILE_LINE_SIZE];
	unsigned int linenum = 0;
	fin = fopen(filename, "rt");

	if(fin) {
		while(fgets(line, sizeof(line), fin)) {
			process_line(line);
		}
	} else {
		fprintf(stderr, s"ERROR READING FILE: %s.\n", filename);	
	}

	fclose(fin);
	return 0;
}