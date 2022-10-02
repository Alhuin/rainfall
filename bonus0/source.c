char *p(char *buffer, char *dash){
    char read_buffer[4108]; //4120- 12 (pour les 3 arguments)
    
    puts(dash);
    read(0, read_buffer, 4096);
    strchr(read_buffer , '\n') = '\0';
    return(strncpy(buffer, read_buffer, 20));
}

void pp(char *main_buffer) {
    char a_buffer[20]; 
    char b_buffer[20];

    p(a_buffer," - ");
    p(b_buffer," - ");
    strcpy(main_buffer, a_buffer);
    len = strlen(main_buffer)
    main_buffer[len] = ' ';
    return(strcat(main_buffer, b_buffer));
}

int    main(int argc, char** argv){
    char main_buffer[42];
    pp(main_buffer);
    puts(main_buffer);
    return(0);
}
