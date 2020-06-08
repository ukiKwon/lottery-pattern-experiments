#ifndef MYCLASS1_H_INCLUDED
#define MYCLASS1_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#define STD_TOTAL 688
#define STD_SIM 2
#define SZ_LUCK 5

using namespace std;
typedef vector< vector < short > > vofv;
typedef vector< short > vs;
typedef list < int > li;

enum ton { TRUE = 1, FALSE = 0};
struct Lnode { //한 회차에 대한
   double simmularity;  //전체 데이터에대한 유사성 저장
   int index;  //현 회차
   short max_num; //현재 들어온 num개수(최대 입력개수)
   short maxOfthesame;  //일치한 최대의 개수
   vs num;  //저장된 version개 번호
   list <int> indexes; //현 회차와 유사한 회차 저장
public:
   Lnode(void)
      : max_num(0),index(0),maxOfthesame(0),simmularity(0) {}
   Lnode(short _max)
      : max_num(_max),index(0),maxOfthesame(0),simmularity(0) {}
   Lnode(const Lnode &g)
      : max_num(g.max_num),index(g.index),maxOfthesame(g.maxOfthesame),simmularity(g.simmularity) {
         num.clear();num.resize(0);
         indexes.clear();indexes.resize(0);
         for(vs::const_iterator it = g.num.begin();
               it != g.num.end(); ++it)
               num.push_back(*it);
         for(li::const_iterator it = g.indexes.begin();
               it != g.indexes.end(); ++it)
            indexes.push_back(*it);
   }
public:
   void setMaxnum(short _max) {
      this->max_num=_max;
   }
   void push_num(short *n) {
      //cout << "push_num : one var " << endl;
      int _sz = num.size();
      if(max_num == _sz) {
         cout << "공간이 부족합니다.";
         cout << " -현재 사이즈 : " << _sz << endl;
         return;
      }
      num.push_back(*n);
   }
   void push_num(short *arr, short len) {
      //cout << "push_num : array " << endl;
      int _sz = num.size();
      //cout << "현재 공긴 :" << _sz << "vs 넣을 자료 길이 :" << len << endl;
      if(len > max_num - _sz) {
         cout << "공간이 부족합니다.";
         cout << " ( " << len << '>' << max_num << '-' << _sz << " )" << endl;
         return;
      }
      for(int i = 0; i < len; ++i)
         num.push_back(*(arr++));
   }
   void g_clearing(void) {
      max_num = 0;index = 0;maxOfthesame = 0;simmularity = 0;
      num.clear();num.resize(0);
      indexes.clear();indexes.resize(0);
   }
public:
   void printIndex(void) const {
      cout << " *** Indexes *** \n";
      int count = 0;
      for(li::const_iterator it=indexes.begin(); it != indexes.end(); ++it) {
         if((count++) % 10 == 0) cout << "\n:";
         cout << *it << ' ';
      }
      cout << endl;
   }
};
typedef struct figurepattern fpl;
typedef vector < Lnode > v_Lnode;
typedef vector< fpl > v_fpl;
struct figurepattern {
   short pattern[6]; //형성된 패턴에 대한 sorting 된 자리 분포
   vofv compound; //pattern을 가진 분포 나열
public:
   figurepattern(void) {
      for(int i=0; i<6; ++i)
         pattern[i]=0;
   }
   figurepattern(const fpl &f) {
      int _sz = f.compound.size();
      for(int i = 0; i < 6; ++i)
         pattern[i] = f.pattern[i];
      compound.clear();compound.resize(0);
      for(int i = 0; i < _sz; ++i) {
         compound.push_back(f.compound[i]);/// 될랑가
      }
   }
public:
   static void setFigure(short (&figure)[5][2], const vs &num) {
      short _sz = num.size();
      //set the figure to 'null'
      for(int i = 0; i < 5; ++i) {
         figure[i][0] = 10*i;
         figure[i][1] = 0;
      }
      //setting figure by src
      for(int i = 0; i < _sz; ++i) {
         if(num[i] < 10) ++figure[0][1];
         else if(num[i]<20)  ++figure[1][1];
         else if(num[i]<30)  ++figure[2][1];
         else if(num[i]<40)  ++figure[3][1];
         else if(num[i]<50)  ++figure[4][1];
      }
   }
public:
   void printPattern(void) const {
      int i,j;
      int _sz = compound.size();
      cout << "pattern : ";
      for(i = 0; i < 6; ++i)
         cout << pattern[i] << ' ';
      cout << '\n' << "compound : ";
      for(i = 0; i < _sz; ++i)
         for(j = 0; j < 6; ++j)
            cout << compound[i][j] << ' ';
      cout << endl;
   }
public:
   int operator==(const fpl &f) {
      //cout << "operator ==\n";
      fpl zero;
      int myflag1 = 0,myflag2 = 0;
      int sz_src = compound.size(),sz_dst = f.compound.size();
      for(int i = 0;
         i < 5&&pattern[i] == f.pattern[i]; ++i)
         ++myflag1;
      //cout << "sz_src :" << sz_src << ",sz_dst :" << sz_dst << endl;
      //cout << "myflag1 :" << myflag1 << endl;
      //if(myflag1==5)
         //cout << " >>같은 패턴입니다." << endl;
      if(myflag1 ==5 && sz_src == sz_dst) {
         for(int i = 0; i < sz_src; ++i)
            for(int j = 0;
            j < 5&&compound[i][j] == f.compound[i][j]; ++j)
               ++myflag2;
      }
      else return 0;
      //cout << "myflag2 :" << myflag2 << endl;
      //if(myflag2==5*sz_src)
         //cout << ">>같은 compound입니다. " << endl;
      if(myflag1 == 5 && myflag2 == (5*sz_dst))
         return -2;
      return 0;
   }
   void f_clearing(void) {
      int _sz = compound.size();
      vs zero;
      for(int i = 0; i < 6; ++i)
         pattern[i]=0;
      for(int i=0; i<_sz; ++i) {
         compound[i].clear();
         compound[i].resize(0);
      }
      compound.resize(0);
   }
};
class myfunction {
public:
   static void mysort_number1(Lnode &g);
   static void mysort_number2(short (&f)[5][2]);
   static void mysort_number3(v_fpl &src);
   static void mysort_number4(v_Lnode &g);

   static int findSamenum(v_Lnode::iterator& src, v_Lnode::iterator& dst);
   static fpl isthereFigure(const short(&figure)[5][2],const v_fpl& src);
   static int isthereNnum(const Lnode& tLnode,const v_Lnode& src);
   static int generateCompound(vofv& aliveOrnot, const vofv& combi_n, short* combi_r);
   static int combination(short n, short r);
};
class Lotto {
   short version;
   li indexes;
   v_Lnode luckyNumber;
   v_fpl spreadPattern;
public:
   Lotto(void)
      :version(0) {}
   Lotto(short _ver)
      :version(_ver) {}
   Lotto(const Lotto &p) {
      version = p.getVersion();
      this->indexes.clear();this->indexes.resize(0);
      this->luckyNumber.clear();this->luckyNumber.resize(0);
      this->spreadPattern.clear();this->spreadPattern.resize(0);
      for(li::const_iterator it=p.getIndex().begin();
            it != p.getIndex().end(); ++it)
         indexes.push_back(*it);
      for(v_Lnode::const_iterator it=p.getLucky().begin();
            it != p.getLucky().end(); ++it)
            luckyNumber.push_back(*it);
      for(v_fpl::const_iterator it=p.getPattern().begin();
            it != p.getPattern().end(); ++it)
            spreadPattern.push_back(*it);
   }
   void setLotto(short _version) {
      //cout << "setLotto" << endl;
      this->version = _version;
      cout << "초기데이터를 받아들이고 있습니다." << endl;setLuckynumber(_version);
      cout << ">> 데이터를 생성 중입니다..." << endl;setDatasheet(luckyNumber,luckyNumber);
      cout << ">> 패턴 정보 생성중..." << endl;setSpreadpattern(spreadPattern,STD_TOTAL);
   }
public:
   Lnode isthereToken(Lnode &tLnode);
public:
   int setLuckynumber(short version);
   int setDatasheet(v_Lnode &dst, v_Lnode &src);
   int setSpreadpattern(v_fpl &src, int untilN);
public:
   short getVersion(void) const {
      return version;
   }
   int getTotalPattern(void) const {
      int count = 0;//,pattern_size=spreadPattern.size();
      for(v_fpl::const_iterator it=spreadPattern.begin();
         it != spreadPattern.end(); ++it)
         count += static_cast < int >((*it).compound.size());
      return count;
   }
   li getIndex(void) const {
      return indexes;
   }
   v_Lnode getLucky(void) const {
      return luckyNumber;
   }
   v_Lnode& getLucky(void) {
      return luckyNumber;
   }
   v_fpl getPattern(void) const{
      //cout << "const_getpattern" << endl;
      return spreadPattern;
   }
   v_fpl& getPattern(void) {
      //cout << "ref_getPattern" << endl;
      return spreadPattern;
   }
   void printIndexes(void) {
      int count = 0;
      cout << " *** Indexes *** ";
      for(li::iterator it = indexes.begin();
         it != indexes.end(); ++it) {
         if((count++)%10 == 0) cout << "\n:";
         cout << *it << ' ';
      }
      cout << endl;
      indexes.clear();indexes.resize(0);
   }
   void printPattern(void) const;
   void printPattern(int _sz) const;
   void printLuckynum(void) const {
   }
   void outSpreadpattern(void) const;
public:
   void p_clearing(void) {
      this->version=0;
      indexes.clear();indexes.resize(0);
      for(v_Lnode::iterator it=luckyNumber.begin();
         it != luckyNumber.end(); ++it)
         it->g_clearing();
      for(v_fpl::iterator it=spreadPattern.begin();
         it != spreadPattern.end(); ++it)
         it->f_clearing();
   }
   friend class luckyset;
};
class Linterface {
   short select;
   Lotto p;
public:
   Linterface(void)
      :select(0),p(0) {}
   void setSelect(short _sel) {
      this->select=_sel;
   }
public:
   int procIntro();//version setting
   int procTable();//menual
   int procNprint();//print N'th number
   int procNpattern();//find strong pattern until N
   int procTokenpattern();//what Token pattern's simmularity
   int procRevising();//revising my number
   int procAutonum();//auto generating basing on spreadpattern
   void proEnd() {
      //ending message
      cout << " *** 프로그램을 종료합니다. ***" << endl;
   }
public:
   short getSelect(void) const {
      return select;
   }
public:
   static int chPat_size(int pat_sz,int total_sz) {
      int myrank = 0;
      if(pat_sz) {
         cout << "패턴 : " << pat_sz << "아래, ";
         cout << total_sz << " 패턴이 생성되어있습니다. " << endl;
         cout << ">> 나열할 상위 랭크 수를 입력하세요 " << endl;
         cout << " (범위 : 1~ "<< total_sz << " )" << endl;
         cout << " :";
         cin >> myrank;cin.clear();
         while(myrank>total_sz) {
            cout << ">> 다시입력해주십시오 " << endl;
            cout << " (범위 : 1~ "<< total_sz << " )" << endl;
            cin >> myrank;cin.clear();
         }
      }
      return myrank;
   }
};
class luckyset {
   int sz;
   Lnode material;
   v_Lnode newNumber;
public:
   luckyset(void)
      :sz(SZ_LUCK),material(0) {}
   void setMaterial(const Lnode &g) {material = g;}
   luckyset(int _sz)
      :sz(_sz),material(0) {}
   int setToken(short *token, vofv aliveOrnot, short _sz) {
      static int count = 0;
      int len = 0;
      for(int i = count * _sz; i < _sz; ++i)
         token[len++] = aliveOrnot[0][i];
      ++count;
      if(len == _sz)   return -1;//right operation
      else  return 0;
   }
   void setNewnumber(const Lnode &g, Lotto &p) {
      v_Lnode tfpl;
      int i = 0,_sz = newNumber.size();
      //sim 계산을 하고 새로운 숫자조합으로 넣어준다.
      tfpl.push_back(g);
      p.setDatasheet(tfpl,p.getLucky());

      newNumber.push_back(tfpl[0]);
      myfunction::mysort_number4(newNumber);
      if(_sz + 1 > SZ_LUCK)
         newNumber.resize(SZ_LUCK);
   }
   v_Lnode getNewnumber(void) const {return newNumber;}
public:
   bool isAliveNum(short differ) const {
      if(differ <= 0)  return TRUE;
      return FALSE;
   }
   bool isAliveornot(short differ) const {
      if(differ>0)  return TRUE;
      return FALSE;
   }
   bool isAddnum(short differ) const {
      if(differ<0)  return TRUE;
      return FALSE;
   }
   bool rangTest(short a, short b) const {
      //cout << endl << " rangTest :";
      //cout << "a :" << a << ",b :" << b << endl;
      if(a - b < 10 && a - b >= 0) {
         //cout << "->범위에 속함 " << endl;
         return TRUE;
      }
      //cout << "->범위 탈락 " << endl;
      return FALSE;
   }
public:
   void generateNum(const Lnode &g,Lotto &p);
   static int generateCompound(vofv &aliveOrnot,const vs &cellOfaon, short _token);
   short generate_randomIn(const Lnode &src) {
      //Lnode.num 의 내용을 보고
      //중복되지 않는 랜덤수를 반환
      int len = src.num.size();
      short cell;bool ch = TRUE;
      while(ch != FALSE) {
         ch = TRUE;
         //random 생성
         cell = (rand()%45) + 1;
         //cout << "cell :" << cell << endl;
         //num안에 비교
         for(int i = 0;i < len;++i)
            if(cell == src.num[i])
               ch = FALSE;
      }
      return cell;
   }
public:
   void printMaterial(void) const {
      int _sz = material.num.size();
      //cout << "luckySet::printMaterial " << endl;
      cout << "material :" << endl;
      for(int i = 0; i < _sz; ++i)
         cout << material.num[i] << ' ';
      cout << endl;
   }
   void printNewnumber(void) const {
      cout << "\nluckySet::printNewnumber\n";
      int _ver = material.max_num;
      int _sz = newNumber.size();
      if(_sz) {
         cout << " >> Newnumber is loading...\n";
         cout << " - Material is : ";
         for(int i = 0; i < _ver; ++i)
            cout << material.num[i] << ' ';
         cout << endl;
         cout << " - new number list -\n";
         for(int i = 0; i < _sz; ++i) {
            cout << i << ": ";
            for(int j = 0; j < _ver; ++j)
               cout << newNumber[i].num[j] <<' ';
            cout << " :" << newNumber[i].simmularity << endl;
         }
      }
      else
         cout <<"\n >> 생성된 수가 없습니다.\n";
   }
public:
   void l_clearing(void) {
      int sz_vLnode = newNumber.size();
      Lnode zero;
      sz=0;
      material = zero;
      for(int i=0; i < sz_vLnode; ++i)
         newNumber[i]=zero;
      newNumber.resize(0);
   }
};
#endif // MYCLASS1_H_INCLUDED
