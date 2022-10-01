int main(int argc, char **argv)
{
    char b[40];

    int a = atoi(argv[1]);
    if (a > 9)
        return (1);
    memcpy(b, argv[2], a*4);
    if (a == 1464814662)
        execl("/bin/sh", "sh", NULL);
    return(0);
}
