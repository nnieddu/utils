#include <unistd.h>

int main ()
{
   int x = 10;
   int y = 5;
   int x1 = 0;
   int y1 = 0;
   
   while (y1 < y)
   {
       while (x1 < x)
       {
          if (x1 == 0 || x1 == x - 1 || y1 == 0 || y1 == y - 1) 
               write(1, "~", 1);
           else
               write(1, " ", 1);
           x1++;
       }
   	 write(1, "\n", 1);
       x1 = 0;
       y1++;
   }
}
