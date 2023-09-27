#include <stdio.h>
#include<stdbool.h>
int n = 0 ; 
int curr = 0 ; 
int d = 1 ; 

int main(int argc,char* argv[]){
printf("introduce numero ");
scanf("%d ",&n);
printf(" %d == ",n);
{
int tmp0;
tmp0 = 2+0;
curr=tmp0;
}
{
etiqueta3: 
 { 
 bool tmp1;
tmp1 = curr<=n;
if(!tmp1) goto etiqueta2 ; 
{
{
int tmp2;
tmp2 = n/curr;
d=tmp2;
}
{
bool tmp4;
int tmp3;
tmp3 = d*curr;
tmp4 = tmp3==n;
if(!tmp4) goto etiqueta0 ; 
{
printf("* %d ",curr);
{
int tmp5;
tmp5 = n/curr;
n=tmp5;
}
}
 goto etiqueta1;
 etiqueta0: 
 {
{
int tmp6;
tmp6 = curr+1;
curr=tmp6;
}
}
 
 } 
etiqueta1: 
{}
}

 goto etiqueta3; 
 } 
 } 
  etiqueta2: 
printf("\n");
}

