int g_language = 0;


int greetuser(char *a)
{
	char *b;

	if (g_language == 1)
		strcpy(b,"Hyvää päivää ");
	else if (g_language == 2)
		strcpy(b,"Goedemiddag! ");
	else if (g_language == 0)
		strcpy(b, "Hello ");
	strcat(b, a);
	return(puts(b));
}

int main(int argc, char **argv)
{
	char a[72];
	char *lang;
	
	if (argc != 3)
		return(1);

	memset(a, '\0', 72);
	strncpy(a, argv[1], 40);
	strncpy(&a[40], argv[2], 32);
	lang_env = getenv("LANG");

	if (lang_env != 0)
	{
		if (memcmp(lang_env, "fi", 2) == 0)
			lang = 1;
		else if (memcmp(lang_env, "nl", 2) == 0)
			lang = 2;
	}
	return (greetuser(a));
}
