#include "myclass1.h"

int main(void)
{
   try {
      int ch1 = 0;
      Linterface c;
      while(ch1 != -4) {
         c.procIntro();
         ch1 = c.procTable();
      }
      c.proEnd();
   }catch(int) {
      cout << "something is missing" << endl;
   }
}
