
char*
itoa_format(int value, char *str, int base, int capital)
{
	char *s = itoa(value);

	if(!s) {
		// report error
	}

	#define BASE_2_LOWER 0
	#define BASE_2_UPPER 1
	#define BASE_8_LOWER 2
	#define BASE_8_UPPER 3
	#define BASE_16_LOWER 4
	#define BASE_16_UPPER 5

	const char* formats[] = {
		[BASE_2_LOWER] = "0b",
		[BASE_2_UPPER] = "0B",
		[BASE_8_LOWER] = "0o",
		[BASE_8_UPPER] = "0O",
		[BASE_16_LOWER] = "0x",
		[BASE_16_UPPER] = "0X"
	}

	if(base == 2|| base == 8 || base == 16) {
		size_t len = strlen(s) + 2;
		char *ss = (char*)malloc(len);
		char format[2];
		if(base == 2 && !capital) format = formats[BASE_2_LOWER];
		if(base == 2 && capital) format = formats[BASE_2_UPPER];
		if(base == 8 && !capital) format = formats[BASE_8_LOWER];
		if(base == 8 && capital) format = formats[BASE_8_UPPER];
		if(base == 16 && !capital) format = formats[BASE_16_LOWER];
		if(base == 16 && capital) format = formats[BASE_16_UPPER];

		snprintf(ss, len, "%s%s", format, s);
		free(s);
		str = ss;
		return ss;
	}

	return s;
}