char *p(char *a, char *dash){
    char b[4108]; //4120- 12 (pour les 3 arguments)
    
    puts(dash);
    read(0, b, 4096);
    strchr(b , '\n') = '\0';
    return(strncpy(a, b, 20));
}

void pp(char *a) {
    char b[20]; 
    char c[20];

    p(b," - ");
    p(c," - ");
    strcpy(a, b);
    len = strlen(a)
    a[len] = ' ';
    a[len + 1] = 0;
    return(strcat(a, c));
}



int    main(int argc, char** argv){
    char a[42];
    pp(a);
    puts(a);
    return(0);
}
