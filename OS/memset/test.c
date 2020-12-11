#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

void* Memset(void *s, int c, size_t n) 
{
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n) 
  {
    *schar++ = (unsigned char) c;
    cnt++;
  }
  return s;
}

void* My_Memset(void *s, unsigned long cs, size_t n) 
{
  size_t K = sizeof(unsigned long);
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n)
  {
    if ((size_t)schar % K == 0) 
	  break;
    *schar++ = (unsigned char)cs;
    cnt++;
  }
  
  unsigned long *slong = (unsigned long *)schar;
  size_t rest = n - cnt;
  size_t loop = rest / K;
  size_t tail = rest % K;
  for (size_t i = 0; i < loop; i++) 
   *slong++ = cs;
  
  schar = (unsigned char *)slong;
  for (size_t i = 0; i < tail; i++) 
    *schar++ = (unsigned char)cs;
  return s;
}

#define N (1024*1024LL)
#define INLINE inline __attribute__((always_inline))

char src[2*N] __attribute__((aligned(32))); 

int main()
{
	clock_t start,finish;
   	start=clock();
    //Memset(src,0,sizeof(src));
    My_Memset(src,'0',sizeof(src));
	finish = clock();
	printf("time=%lf\n", (double)(finish - start)/CLOCKS_PER_SEC);
	return 0;
}
