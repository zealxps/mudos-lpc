
#include <stdio.h>

struct Book
{
    char name[10];
    int price;
};

int main()
{
    struct Book a;      //Single structure variable
    struct Book* ptr;   //Pointer of Structure type
    struct Book b[10];  //Array of structure variables
    struct Book* p;     //Pointer of Structure type
    p = &b[0];
    printf("p:%0x", p);


    return 0;
}
