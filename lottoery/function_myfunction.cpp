#include "myclass1.h"

void myfunction::mysort_number1(Lnode& g) {
   //vs num 정렬
   //당첨 숫자 정렬
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
   //figure[i][1] 크기별로 정렬
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
   //패턴의 중복성에 따른 정렬
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
void myfunction::mysort_number4(v_Lnode& g) {
   //sim에 따라서 v_Lnode 정렬
   //simmularity에 따라 소팅
   int _sz=g.size();
   Lnode tLnode;
   for(int i=0;i<_sz;++i)
      for(int j=i+1;j<_sz-1;++j)
         if(g[i].simmularity<g[j].simmularity) {
            tLnode=g[i];
            g[i]=g[j];
            g[j]=tLnode;
         }
}
int myfunction::findSamenum(v_Lnode::iterator& src, v_Lnode::iterator& dst){
   //src와 dst를 비교하여 src를 기준으로 반환한다.
   int count=0;
   short _sz1=src->num.size(),_sz2=dst->num.size();
   //condition
   if(_sz1!=_sz2
      ||_sz1>src->max_num
      ||_sz2>dst->max_num)
      return 0;
   for(int i=0; i<_sz1; ++i)
      for(int j=0; j<_sz2; ++j)
         if(src->num[i]==dst->num[j])
            ++count;
   if (count>=STD_SIM)
      return count;  //satified, return its same count
   return 0;   //Not satified, return 0
}
fpl myfunction::isthereFigure(const short (&figure)[5][2], const v_fpl& src) {
   //cout << "myfunction::isthereFigure\n";
   fpl zero;
   int myflag1;
   for(v_fpl::const_iterator it=src.begin();
      it!=src.end(); ++it) {
      myflag1=0;
      //condition : figure is sorted
      for(int i=0; i<5
         &&figure[i][0]==it->pattern[i]; ++i)
         ++myflag1;
      if(myflag1==5) return *it; //if there, return v_fpl
   }
   return zero;
}
int myfunction::isthereNnum(const Lnode& tLnode, const v_Lnode& src) {
   int _sz1=tLnode.num.size(),_sz2=src.size();
   int ch1=0;
   //luckySet에 생성된 newNumber 안에 새로 생성된 녀석이 있는지 확인한다.
   //newNumber==src/*/tLnode==tLnode
   //cout << "<myfunction::isthereNum>\n";
   //cout << "_sz1 :" << _sz1 << ", _sz2 :" << _sz2 << endl;
   for(v_Lnode::const_iterator it=src.begin();
         it!=src.end(); ++it) {
         ch1=0;
         for(int i=0;i<_sz1
            &&tLnode.num[i]==it->num[i];++i)
            ++ch1;
         if(ch1==_sz1)
            return ch1;  //찾으면 _sz2 반환
   }
   return 0;
}
int myfunction::generateCompound(vofv& aliveOrnot, const vofv& combi_n, short* combi_r) {
   //alvieOrnot에는 저장용도
   //cellOfaon는 만들 조합
   int c,i,j,k,l,len=0;
   short n=combi_n.size();
   vs cell;
   ofstream of("compoundCheck.txt");
   if(n)  cout << " >> compound is generated rightly...\n";
   else if(n==1||n==0){cout << " >> " << '(' << n << ')' << ":compound wouldn't be generated,but it's right\n";return -1;}
   short combi_count=1;
   //combi_count
   for(i=0; i<combi_r[i]; ++i)
      combi_count*=combination(combi_n[i].size(), combi_r[i]);
   while(c<n) {
      //case1.3c1
      if(combi_n[c].size()==3&&combi_r[c]==1) {
         for(i=0; i<combi_count; ++i) {///1
            for(j=0; j<combi_n[c].size(); ++j)///2
               for(k=0; k<combi_r[c]; ++k)///3
                  aliveOrnot[i++].push_back(combi_n[j]);
         }
      }
      //case2.3c2
      //case3.2c1
   }
   else {cout << "myfunction::generateCompound is in a error\n";return -1;}
   for(int z=0; z<len; ++z) {
      if(z%n==0) of << endl;
      of << aliveOrnot[z] << ' ';
   }
   of.close();
   return n;
}
int myfunction::combination(int n, int r) {
   if(n == r || r == 0) return 1;
   else return combination(n - 1, r - 1) + combination(n - 1, r);
}
