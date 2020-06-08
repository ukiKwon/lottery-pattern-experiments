#include "myclass1.h"

void luckyset::generateNum(const Lnode &g, Lotto &p) {
   cout << "luckyset::generateNum\n";
   int i,j,k;
   short _ver = p.getVersion();
   short now_figure[5][2];
   bool onNoff;
   Lnode luckNum(_ver);  //������ ���� ��÷ ��Ʈ�� ����
   fpl db_figure, zero;    //���� ���� ���� ����

   ///part1.���� �� ���� �ľ�
   cout << " >> �����۾��� �����մϴ�.\n";
   setMaterial(g);//luckyset->marterial ����
   fpl::setFigure(now_figure, g.num);// �� ���� ��Ʈ ������ �������� now_figure ����
   myfunction::mysort_number2(now_figure);   //���� ����

   cout << " - now_figure \n";
   for(int i = 0; i < 5; ++i)
      cout << now_figure [i][0] << ' ' << now_figure[i][1] << endl;
   cout << endl;
   ///part1_a.DB���� ���� ���� ���� �˻�
   db_figure = myfunction::isthereFigure(now_figure, p.getPattern());//db�� ������ zero ��ȯ
   onNoff = (db_figure == zero);

   ///part1_b.DB�� ������_���� ���� ���
   if(!onNoff) {
         cout << " db_figure Ȯ�� " << endl;
         for(int i = 0; i < 5; ++i)
            cout << db_figure.pattern[i] << ' ';
         cout <<endl << "compound Ȯ�� :";
         cout << "db_figure.compound.size : " << db_figure.compound.size() << endl;
         for(int i = 0; i < 5; ++i)
            cout << db_figure.compound[0][i] << ' ';
         cout << endl;
         //�ش� spreadpatterh ���� compound ���� ����
         //cout << "- ������ 1�� �� ������ �̻�����" << endl;
   }
   else { cout << " >> It's a new figure" << endl;}

   ///part2.���� ���ϰ� DB ���� �м�
   if(!onNoff) {
         int len = 0, ch1 = 0, n = 1, _aliveOrnot = 1;
         short differ[5];
         short *aliveNum, *addNum;//*aliveOrnot,
         short _aliveNum = 0, _addNum = 0;
         vofv aliveOrnot;
         short combi_r[5];
         cout << "differ ���� \n\n";
         for(i = 0; i < 5; ++i) {
            ///part2_1_a.���� �м����� differ[i]�� ���
            differ[i] = now_figure[i][1] - db_figure.compound[0][i];
            ///part2_1_b.���� ��ȣ(_aliveOrnot) �� ����
            if(isAliveornot(differ[i])) {
               _aliveOrnot *= myfunction::combination(now_figure[i][1], db_figure.compound[0][i]);
               combi_r[len++] = db_figure.compound[0][i];
            }
            ///part2_1_d.���� ���� ��ȣ(_addNum) �� ����
            else if(isAddnum(differ[i])) {
               _addNum += (-differ[i]);
            }
            ///part2_1_c.������ ��ȣ(aliveNum) �� ����
            if(isAliveNum(differ[i])) {
               _aliveNum += now_figure[i][1];
            }
         }
         n = myfunction::combination(45, _addNum);///_addNum = myfunction::combination(45,_addNum);n �̶� addNum ���߿� ���Ĺ����� ����� ����
         len = 0;
         cout << endl << endl;
         cout << "_aliveNum :" << _aliveNum << endl;
         cout << "_aliveOrnot :" << _aliveOrnot << endl; ///�̰Ŵ� �̹� combination ���̴ϱ�
         cout << "_addNum :" << _addNum << "combination : " << n << endl;
         cout << "\n - Giving array -\n";

         ///part2_2.�� ������ ���� �Ҵ�
         aliveNum = (_aliveNum == 0)? 0 : new short[_aliveNum];
         //aliveOrnot = _aliveOrnot == 1? 0 : new short[_aliveOrnot];
         addNum = (_addNum == 0)? 0 : new short[_addNum];

         ///part2_2_a.aliveNum ã��
         cout << " 1. aliveNum is tried to set up...now\n";
         for(i = 0; aliveNum && i < 5; ++i) {
            for(j = 0; j < _ver; ++j)
               //cout << " num :" << material.num[j] << endl;
               //cout << " isAliveNum : " << isAliveNum(differ[i]) << endl;
               //cout << " rangTest : " << rangTest(material.num[j],now_figure[i][0]) <<endl;
               if(isAliveNum(differ[i])
                  &&rangTest(material.num[j], now_figure[i][0]))
                  aliveNum[len++]=material.num[j];
         }
         if(_aliveNum == len)  cout << " >> aliveNum is setting rightly\n";
         else cout << " >> (err)aliveNum's setting is not working rightly\n";
         //aliveNum_checking
         cout << "- aliveNum_checking \n";
         for(short p = 0; p < _aliveNum; ++p)
            cout << aliveNum[p] << ' ';
         if(!_aliveNum)  cout <<" \n>> there is no aliveNum finded\n";

         ///part2_2_b.aliveOrnot ã��
         cout <<" \n2. aliveOrnot is tried to set up...now\n";
         vs cellOfaon;
         vofv aon;
         int ch3 = 0;len = 0;
         for(i = 0; _aliveOrnot && i < 5; ++i) {
            for(j = 0; j<_ver; ++j) {
                  if(isAliveornot(differ[i])
                     &&rangTest(material.num[j], now_figure[i][0])
                     &&db_figure.compound[0][i] != 0)   //1C0 ����
                     cellOfaon.push_back(material.num[j]);
            }
            if(cellOfaon.size() != 0)
               aon.push_back(cellOfaon);
            cellOfaon.clear();cellOfaon.resize(0);
         }
         ch3 = myfunction::generateCompound(aliveOrnot, aon, combi_r);//generateCompound(saveToHere, combination_n, combination_r)
         if(!aliveOrnot.size() == 0)  cout << " >> No aliveOrnot!!!\n";

         cout << "2. aliveOrnot array checking " << endl;
         int count1 = 0, count2 = 0;
         int _token = aon[0].size();
         //cout << "\n- here's the making newNumber - " << endl;
         //cout << " ch3 :" << ch3 << endl;
         cout << " token :" << _token << endl;
         //cout << "addNum :" << addNum << endl;
         //cout << "aliveNum :" << aliveNum << endl;
         //cout << "aliveOrnot :" << aliveOrnot << endl;
         ofstream of1("newNumber_list.txt");
         of1 << " **** newNumber_list **** " << endl;
         ///part3. ���� ������ ��ȣ�� �����Ѵٸ� <==> ���� ��ȣ�� �����.
         while(addNum&&count1++<n) {
               int ch4=0;
               luckNum.setMaxnum(_ver);   //���� �����ϴ� �� ����; luckNum; ũ��� _ver(6 or 7)
               ///part3_1. ����ִ� �� ������ ���� ����
               if(aliveNum)   luckNum.push_num(aliveNum, _aliveNum);
               of1 << "1 | ";
               for(int z=0;z<_aliveNum;++z)  {of1 << luckNum.num[z] << ' ';}
               of1 << " |" << '\n';
               ///part3_2_1. ����ִ� ���� ������
               while(_aliveOrnot && count2++ < _aliveOrnot) {
                  int ch5 = 0;
                  Lnode tLnode = luckNum;
                  short* token = new short[_token];

                  ch5 = setToken(token, aliveOrnot, _token);//aliveOrnot ©�� token�� �ֱ�
                  //cout << " ch5 :" << ch5 << endl;
                  tLnode.push_num(token,_token);///3
                  of1 << "2 | ";
                  for(int z = 0;z < _token; ++z) {of1 << token[z] << ' ';}
                  of1 << " |" << endl;
                  //addNum's setting
                  for(i = 0; i < _addNum; ++i) {
                     addNum[i] = generate_randomIn(tLnode);
                     tLnode.push_num(addNum + i);
                  }
                  of1 << "3 | ";
                  for(int z = 0; z < _addNum; ++z) {of1 << addNum[z] << ' ';}
                  of1 << " |" << endl;
                  //�ߺ��Ǵ��� Ȯ��
                  ch4 = myfunction::isthereNnum(tLnode, getNewnumber());
                  //�ߺ��� �� �ƴ϶��
                  if(!ch4) setNewnumber(tLnode, p);//���ο� Newnumber�� pushing
                  tLnode.g_clearing();
                  delete token;
               }
               ///part3_2_2. ���ڸ� = �������� ä��
               if(!_aliveOrnot) {
                  for(i = 0; i < _addNum; ++i) {
                     //cout << "part2" << endl;
                     addNum[i] = generate_randomIn(luckNum);
                     luckNum.push_num(addNum + i);///1
                  }
                  of1 << "3 | ";
                  for(int z=0;z<_addNum;++z) {
                     of1 << addNum[z] << ' ';
                  }
                  of1 << " |" << endl;
                  ch4=myfunction::isthereNnum(luckNum,newNumber);
                  //cout << "ch4 :" << ch4 <<endl;
                  if(!ch4)
                     setNewnumber(luckNum, p);
               }
               //cout << "luckNum is cleared now " << endl;
               luckNum.g_clearing();
               count2 = 0;

         }
         count1=0;
   of1.close();
   }

}
