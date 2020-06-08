#include "myclass1.h"

void myfunction::mysort_number1(game& g) {
   //vs num 정렬
   short t1,_sz=g.num.size();
   for(int i=0;_sz&&i<_sz-1;++i)
      for(int j=i+1;j<_sz;++j)
         if(g.num[i]>g.num[j]) {
            t1=g.num[i];
            g.num[i]=g.num[j];
            g.num[j]=t1;
         }
}
void myfunction::mysort_number2(short (&f)[5][2]) {
   short t1=0,t2=0;
   //cout << "mysort...is OK" << endl;
   for(int src=0;src<4;++src)
      for(int next=src+1;next<5;++next)
         if(f[src][1]<f[next][1]) {
            t1=f[src][0];t2=f[src][1];
            f[src][0]=f[next][0];f[src][1]=f[next][1];
            f[next][0]=t1;f[next][1]=t2;
         }
}
void myfunction::mysort_number3(v_fpl& src) {
   //패턴 세팅
   fpl t1;
   for(v_fpl::iterator s=src.begin();s!=src.end();++s)
      for(v_fpl::iterator d=src.begin();d!=src.end();++d)
         if(s!=d&&s->pattern[5]>d->pattern[5]) {
            t1=*s;
            *s=*d;
            *d=t1;
         }
}
int myfunction::findSamenum(v_game::iterator& src,v_game::iterator& dst){
   //src와 dst를 비교하여 src를 기준으로 반환한다.
   int count=0;
   short _sz1=src->num.size(),_sz2=dst->num.size();
   //condition
   if(_sz1!=_sz2
      ||_sz1>src->max_num
      ||_sz2>dst->max_num)
      return 0;
   for(int i=0;i<_sz1;++i)
      for(int j=0;j<_sz2;++j)
         if(src->num[i]==dst->num[j])
            ++count;
   if (count>=STD_SIM)
      return count;
   return 0;
}
