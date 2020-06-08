#include "myclass1.h"

int Lotto::setLuckynumber(short version) {
   short input[7];
   int count=0;
   Lnode data; //Lnode 'max_num' is set

   ifstream in("lotto.txt");
   while(!in.eof()) {
      for(int i=0;i<7;++i)
         in >> input[i];
      data.setMaxnum(version);
      data.index=STD_TOTAL-(count++);//index
      data.push_num(input,version);   //version개만큼 push_back()
      myfunction::mysort_number1(data);

      luckyNumber.push_back(data);
      data.g_clearing();   //실제로 num만 클리어 하면 되기는 하지만,
   }
   return -2;
}
int Lotto::setDatasheet(v_Lnode& dst,v_Lnode& src) {
   int count=0;
   /**
   //Lnode
   //한 회차의 정보를 완성시키면 됨
   - short max_num; //versino 정보
   - vs num;  //저장된 version개 번호
   - int index;  //현 회차
   - short maxOfthesame;  //일치한 최대의 개수
   - int simmularity;  //전체 데이터에대한 유사성 저장
   - list <int> indexes; //현 회차와 유사한 회차 저장
   **/
   //--luckynumber의 iterator를 넘겨주면
   //--같은 숫자를 넘겨준다. 너무 적으면 그냥 0을 돌려주고
   //cout << "src_size :" << src.size() << endl;
   for(v_Lnode::iterator it_dst=dst.begin();
         it_dst!=dst.end();++it_dst) {
         for(v_Lnode::iterator it_src=src.begin();
            it_src!=src.end();++it_src) {
            //같지 않다면 비교를 시작한다.
            //if(it_dst!=it_src)
            count=myfunction::findSamenum(it_dst,it_src);
            if(count) {
               //simmularity
               it_dst->simmularity+=count;
               if(it_dst->maxOfthesame<count)
               //maxOfthesame
                  it_dst->maxOfthesame=count;
               //index
               it_dst->indexes.push_back(it_src->index);
               count=0;
            }
         }
         it_dst->simmularity=it_dst->simmularity/STD_TOTAL;
   }
   return -2;
}
int Lotto::setSpreadpattern(v_fpl& spreadpatt,int untilN) {
   //spreadPattern setting
   int i=0,count=0;
   short figure[5][2];
   short saving1=0,saving2=0;
   vs cell;
   fpl data;
   ofstream procSetpattern("setSpreadpattern.txt");
   //cout << "< Lotto::setSpreadpattern >" << endl;
   /**
   //fpl
   short pattern[6];
   vofv compound;
   **/
   //cout << "spreadpatt_size : " << spreadpatt.size() << endl;
   //cout << "untilN :" << untilN << endl;
   for(v_Lnode::iterator src=luckyNumber.begin();count++<untilN
      &&src!=luckyNumber.end();++src) {
         ///1
         procSetpattern << "\nIndex :" << count << endl;
         fpl::setFigure(figure,src->num);  //setting figure
         myfunction::mysort_number2(figure); //setting figure by increasing
         //setting data
         for(int i=0;i<5;++i) {
            data.pattern[i]=figure[i][0];
            cell.push_back(figure[i][1]);
         }
         cell.push_back(1);
         data.pattern[5]=1;
         data.compound.push_back(cell);
         ///2
         //패턴 분석
         procSetpattern << "spreadpattern_size :" <<spreadpatt.size() << endl;
         //cout << "saving1 :" << saving1 << endl;
         for(v_fpl::iterator target=spreadpatt.begin();saving1!=5
               &&target!=spreadpatt.end();++target) {
               //같은 패턴 체크
               saving1=0;
               for(i=0;target->pattern[i]==figure[i][0]&&i<5;++i)
                  ++saving1;
               procSetpattern << "saving1 :" << saving1 << endl;
               //같은 패턴&& 같은 자리수 패턴 체크
               if(saving1==5) {
                     //pattern[5] 비트 플러스
                     procSetpattern << " >> 같은 패턴 찾음" << endl;
                     ++target->pattern[5];
                     for(vofv::iterator compo=target->compound.begin();saving2!=5
                           &&compo!=target->compound.end();++compo) {
                           saving2=0;
                           //'같은 패턴 '&& 같은 '자리수 분포도'
                           for(i=0;(*compo)[i]==figure[i][1]&&i<5;++i)
                              ++saving2;
                           procSetpattern << "saving2 :" << saving2 << endl;
                           //해당 자리수분포도를 찾는다면 카운트비트를 올린다.
                           if(saving2==5) {
                              procSetpattern << " >> 같은 자리수 분포도 찾음 " << endl;
                              ++(*compo)[5];
                           }
                     }
                     if(saving2!=5) //다른 자리수분포도라면 새로운 자리수분포도를 추가한다.
                        target->compound.push_back(cell);
                     saving2=0;
               }
         }
      ///3
      if(saving1!=5) {//다른 패턴이라면 spreadpattern에 저장한다.
         procSetpattern << " >>new data is loading " << endl;
         spreadpatt.push_back(data);
      }
      saving1=0;
      ///4
      //data_checking
      //data.printPattern();
      data.f_clearing();cell.clear();

   }
   procSetpattern.close();
   myfunction::mysort_number3(spreadpatt);
   return -2;
}
Lnode Lotto::isthereToken(Lnode& g) {
   int c1=0,c2=0,_ver=getVersion();
   int len=g.num.size()-1;//^z도 len으로 처리되는 건가
   Lnode tLnode;
   //ver1.들어온 토큰과 같았던 당처번호 회차 수 출력 ==c2
   //ver2.어떤 토큰이 같았는지 알려주는게 더 낫지 않을까?
   //ver2.3.어떤 토큰이 같았는지는 이 함수에서 바로 알려주고
   //반환하는 값은 같았던 최대 카운트를 줄까?->이거는 Lnode.maxOfthecount에 이미 설정되어있음
   //아니다.비교하는 길이가 다르면 예외처리 하게 만들어놨음.그냥 여기서 따로 구현해야함
   //그리고 토큰 자체를 검사하는거라서 maxOfthecount가 의미가 없다.
   //ver1.1결론.토큰이 발견된 회수만 카운트해서 보내주면됨 ==indexes.size();
   //cout << "len : " << len << endl;
   for(v_Lnode::iterator src=luckyNumber.begin();
      src!=luckyNumber.end();++src) {
      //같은 숫자 카운트
      for(int s=0;s<len;++s)
         for(int d=0;d<_ver;++d) {
            if(g.num[s]==src->num[d])
               ++c1;
         }
      //토큰 길이와 같은숫자가 같은 개수라면
      if(len==c1)
         tLnode.indexes.push_back(src->index);
      c1=0;
   }
   return tLnode;
}
void Lotto::printPattern(void) const {
   //pattern size만큼 출력하면됨
   int com_sz=0,myrank=0;
   cout << " *** printing spreadPattern ***" << endl;
   //현재 pattern 보여주고
   //compound 보여주고
   for(v_fpl::const_iterator src=spreadPattern.begin();
      src!=spreadPattern.end();++src) {
      cout << ++myrank << ':';
      for(int i=0;i<5;++i)
         cout << src->pattern[i] << ' ';
      cout << '(' << src->pattern[5] << ')' << endl;
      cout << " -compound check -" << endl;
      com_sz=src->compound.size();
      for(int i=0;i<com_sz;++i) {
         for(int j=0;j<5;++j)
            cout << src->compound[i][j] << ' ';
         cout << '(' << src->compound[i][5] << ')' << endl;
      }
   }
}
void Lotto::printPattern(int _sz) const {
   //pattern size만큼 출력하면됨
   int com_sz=0,myrank=0,count=0;
   cout << " *** printing spreadPattern ***" << endl;
   //현재 pattern 보여주고
   //compound 보여주고
   for(v_fpl::const_iterator src=spreadPattern.begin();count++<_sz
      &&src!=spreadPattern.end();++src) {
      cout << '\n' << ++myrank << ':';
      for(int i=0;i<5;++i)
         cout << src->pattern[i] << ' ';
      cout << '(' << src->pattern[5] << ')' << endl;
      cout << " -compound check -" << endl;
      com_sz=src->compound.size();
      for(int i=0;i<com_sz;++i) {
         for(int j=0;j<5;++j)
            cout << src->compound[i][j] << ' ';
         cout << '(' << src->compound[i][5] << ')' << endl;
      }
   }
}
void Lotto::outSpreadpattern(void) const {
   int pat_size=spreadPattern.size(),compo_size=0;;
   int i,j,k;
   FILE* fop;
   fop=fopen("outSpreadpattern.txt","w");
   fprintf(fop," ************** outSpreadpattern **************\n");
   for(i=0;i<pat_size;++i) {
      compo_size=spreadPattern[i].compound.size();
      //pattern_out
      fprintf(fop,"< %d > pattern : ",i);
      for(k=0;k<5;++k)
         fprintf(fop,"%d ",spreadPattern[i].pattern[k]);
      fprintf(fop,"(%d)\n",spreadPattern[i].pattern[5]);
      //its compound_out
      fprintf(fop," compound_list\n");
      for(j=0;j<compo_size;++j) {
         for(k=0;k<5;++k)
            fprintf(fop,"%d ",spreadPattern[i].compound[j][k]);
         fprintf(fop,"(%d)\n",spreadPattern[i].compound[j][5]);
      }
   }
}
