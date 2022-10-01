Class N {
public:
    int value;
    char annotation[100];
        
    N(int n){
        this->value = n;
    }
    
    void setAnnotation(char *str){
        memcpy(this->annotation, str, strlen(str));
    }
    void operator+(N &n){
        return(this->value + n.value);
    }
    void operator-(N &n){
        return(this->value - n.value);
    }
}

int main(int argc, char **argv)  
{  
    if (argc <= 1)  
        exit(1);  
  
   N *a;  
   N *b;  
   N *a_ptr;  
   N *b_ptr;  

   a = new N(5);  
   b = new N(6);  
   a_ptr = a;  
   b_ptr = b;
  
   a->setAnnotation(argv[1]);  
   return (b + a);  
}
