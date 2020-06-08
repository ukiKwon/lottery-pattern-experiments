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
      data.push_num(input,version);   //version����ŭ push_back()
      myfunction::mysort_number1(data);

      luckyNumber.push_back(data);
      data.g_clearing();   //������ num�� Ŭ���� �ϸ� �Ǳ�� ������,
   }
   return -2;
}
int Lotto::setDatasheet(v_Lnode& dst,v_Lnode& src) {
   int count=0;
   /**
   //Lnode
   //�� ȸ���� ������ �ϼ���Ű�� ��
   - short max_num; //versino ����
   - vs num;  //����� version�� ��ȣ
   - int index;  //�� ȸ��
   - short maxOfthesame;  //��ġ�� �ִ��� ����
   - int simmularity;  //��ü �����Ϳ����� ���缺 ����
   - list <int> indexes; //�� ȸ���� ������ ȸ�� ����
   **/
   //--luckynumber�� iterator�� �Ѱ��ָ�
   //--���� ���ڸ� �Ѱ��ش�. �ʹ� ������ �׳� 0�� �����ְ�
   //cout << "src_size :" << src.size() << endl;
   for(v_Lnode::iterator it_dst=dst.begin();
         it_dst!=dst.end();++it_dst) {
         for(v_Lnode::iterator it_src=src.begin();
            it_src!=src.end();++it_src) {
            //���� �ʴٸ� �񱳸� �����Ѵ�.
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
         //���� �м�
         procSetpattern << "spreadpattern_size :" <<spreadpatt.size() << endl;
         //cout << "saving1 :" << saving1 << endl;
         for(v_fpl::iterator target=spreadpatt.begin();saving1!=5
               &&target!=spreadpatt.end();++target) {
               //���� ���� üũ
               saving1=0;
               for(i=0;target->pattern[i]==figure[i][0]&&i<5;++i)
                  ++saving1;
               procSetpattern << "saving1 :" << saving1 << endl;
               //���� ����&& ���� �ڸ��� ���� üũ
               if(saving1==5) {
                     //pattern[5] ��Ʈ �÷���
                     procSetpattern << " >> ���� ���� ã��" << endl;
                     ++target->pattern[5];
                     for(vofv::iterator compo=target->compound.begin();saving2!=5
                           &&compo!=target->compound.end();++compo) {
                           saving2=0;
                           //'���� ���� '&& ���� '�ڸ��� ������'
                           for(i=0;(*compo)[i]==figure[i][1]&&i<5;++i)
                              ++saving2;
                           procSetpattern << "saving2 :" << saving2 << endl;
                           //�ش� �ڸ����������� ã�´ٸ� ī��Ʈ��Ʈ�� �ø���.
                           if(saving2==5) {
                              procSetpattern << " >> ���� �ڸ��� ������ ã�� " << endl;
                              ++(*compo)[5];
                           }
                     }
                     if(saving2!=5) //�ٸ� �ڸ������������ ���ο� �ڸ����������� �߰��Ѵ�.
                        target->compound.push_back(cell);
                     saving2=0;
               }
         }
      ///3
      if(saving1!=5) {//�ٸ� �����̶�� spreadpattern�� �����Ѵ�.
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
   int len=g.num.size()-1;//^z�� len���� ó���Ǵ� �ǰ�
   Lnode tLnode;
   //ver1.���� ��ū�� ���Ҵ� ��ó��ȣ ȸ�� �� ��� ==c2
   //ver2.� ��ū�� ���Ҵ��� �˷��ִ°� �� ���� ������?
   //ver2.3.� ��ū�� ���Ҵ����� �� �Լ����� �ٷ� �˷��ְ�
   //��ȯ�ϴ� ���� ���Ҵ� �ִ� ī��Ʈ�� �ٱ�?->�̰Ŵ� Lnode.maxOfthecount�� �̹� �����Ǿ�����
   //�ƴϴ�.���ϴ� ���̰� �ٸ��� ����ó�� �ϰ� ��������.�׳� ���⼭ ���� �����ؾ���
   //�׸��� ��ū ��ü�� �˻��ϴ°Ŷ� maxOfthecount�� �ǹ̰� ����.
   //ver1.1���.��ū�� �߰ߵ� ȸ���� ī��Ʈ�ؼ� �����ָ�� ==indexes.size();
   //cout << "len : " << len << endl;
   for(v_Lnode::iterator src=luckyNumber.begin();
      src!=luckyNumber.end();++src) {
      //���� ���� ī��Ʈ
      for(int s=0;s<len;++s)
         for(int d=0;d<_ver;++d) {
            if(g.num[s]==src->num[d])
               ++c1;
         }
      //��ū ���̿� �������ڰ� ���� �������
      if(len==c1)
         tLnode.indexes.push_back(src->index);
      c1=0;
   }
   return tLnode;
}
void Lotto::printPattern(void) const {
   //pattern size��ŭ ����ϸ��
   int com_sz=0,myrank=0;
   cout << " *** printing spreadPattern ***" << endl;
   //���� pattern �����ְ�
   //compound �����ְ�
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
   //pattern size��ŭ ����ϸ��
   int com_sz=0,myrank=0,count=0;
   cout << " *** printing spreadPattern ***" << endl;
   //���� pattern �����ְ�
   //compound �����ְ�
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
