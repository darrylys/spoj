#include <stdio.h>

int count(int x){

 return 2|x>>1&1|x>>2&1|x>>3&1|x>>4&1|x>>5&1|x>>6&1|x>>7&1|x>>8&1|x>>9&1|x>>10&1|x>>11&1|x>>12&1|x>>13&1;

}

int main(){for(int i=1;i^10001;i++)printf("%d %d\n",i,count(i));return 0;}