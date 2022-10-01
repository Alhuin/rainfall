Class N {
public:
    int value;
    char annotation[100];
        
    N(int n){
        this->value = n;
    }

    void operator+(N &n){
        return(this->value + n.value);
    }
    
    void operator-(N &n){
        return(this->value - n.value);
    }
        
    void setAnnotation(char *str){
        memcpy(this->annotation, str, strlen(str));
    }
}

int main(int argc, char **argv)  
{  
    if (argc <= 1)  
        exit(1);  
  
   N *a;
   N *b;

   a = new N(5);  
   b = new N(6);  
  
   a->setAnnotation(argv[1]);  
   return (b + a);  
}
