#include<stdio.h>
void octal(int n){
    int result=0;
    int x=n;
    while(n!=0){
        result=result*10+(n%8);
        n=(int)(n/8);
    }
    int r=0;
    while(x!=0){
        r=r*10+result%10;
        result=(int)(result/10);
        x=(int)(x/8);
    }
    printf("%d ",r);
}
int power(int a, int  b){
    int r=1;
    for(int i=0;i<b;i++){
        r=r*a;
    }
    return r;
}
void complement(int n){
    int binary=0;
    int x=n;
    int len=0;
    while(x!=0){
        if(x%2==0)
            binary=binary*10+1;
        else 
            binary=binary*10;
        x=(int)(x/2);
        len++;
    }
    int result=0;
    printf("The reverse order complement is %d\n",binary);
    printf("the len is %d\n",len);
    for(int i=1;i<=len;i++){
        result=result+power(2,len-i)*(binary%10);
        binary=(int)(binary/10);
    }
    printf("The complemnet is %d\n",result);
}
int main(){
    octal(8);
    complement(8);
}