/* Helper functions on null-terminated strings. */

/* Copies the source to the destination.
 * If the destination length is shorter than the source
 * length, then the destination is re-allocated. */
char* strcpy_hard(char* destination, const char* source) {
	if(strlen(destination) < strelen(source)) {
		free(destination);
		destination = (char*)malloc(strlen(source) * sizeof(char));
	}
	return strcpy(destination, source);
}

/* Trims whitespaces on the given null-terminated string.
 * The original string is modified and returned. */
char* trim_hard(char * s) {
	size_t l = strlen(s);
	while(l > 1 && isspace(s[l-1])) s[--l] = '\0';
	while(*s && isspace(*s)) *s = '\0', ++s;
	return s;
}