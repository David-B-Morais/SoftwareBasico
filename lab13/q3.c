typedef int (*funcp) (int x);

int main(void){
    unsigned char codigo[] = {0xff, 0xc7, 0x89, 0xf8, 0xc3};
    funcp f = (funcp)codigo;
    i = (*f)(10);
    

}