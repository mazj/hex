int main(int argc, char const *argv[])
{
	char *s = 0;
	s = itoa_fmt(1000, s, 10, 0);
    printf("%d (base %d)-> %s\n", 1000, 10, s);
    free(s);
   	s = itoa_fmt(1000, s, 8, 0);
    printf("%d (base %d)-> %s\n", 1000, 8, s);
	return 0;
}