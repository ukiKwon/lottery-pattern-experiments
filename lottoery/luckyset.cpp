#include "myclass1.h"

void luckyset::generateNum(const Lnode &g, Lotto &p) {
   cout << "luckyset::generateNum\n";
   int i,j,k;
   short _ver = p.getVersion();
   short now_figure[5][2];
   bool onNoff;
   Lnode luckNum(_ver);  //임임의 숫자 당첨 세트를 생성
   fpl db_figure, zero;    //패턴 닮을 공간 생성

   ///part1.현재 수 패턴 파악
   cout << " >> 교정작업을 시작합니다.\n";
   setMaterial(g);//luckyset->marterial 세팅
   fpl::setFigure(now_figure, g.num);// 한 게임 세트 정보를 바탕으로 now_figure 세팅
   myfunction::mysort_number2(now_figure);   //패턴 정렬

   cout << " - now_figure \n";
   for(int i = 0; i < 5; ++i)
      cout << now_figure [i][0] << ' ' << now_figure[i][1] << endl;
   cout << endl;
   ///part1_a.DB에서 현재 들어온 패턴 검색
   db_figure = myfunction::isthereFigure(now_figure, p.getPattern());//db에 없으면 zero 반환
   onNoff = (db_figure == zero);

   ///part1_b.DB에 있으면_현재 패턴 출력
   if(!onNoff) {
         cout << " db_figure 확인 " << endl;
         for(int i = 0; i < 5; ++i)
            cout << db_figure.pattern[i] << ' ';
         cout <<endl << "compound 확인 :";
         cout << "db_figure.compound.size : " << db_figure.compound.size() << endl;
         for(int i = 0; i < 5; ++i)
            cout << db_figure.compound[0][i] << ' ';
         cout << endl;
         //해당 spreadpatterh 가진 compound 개수 나열
         //cout << "- 사이즈 1도 안 나오면 이상있음" << endl;
   }
   else { cout << " >> It's a new figure" << endl;}

   ///part2.현재 패턴과 DB 패턴 분석
   if(!onNoff) {
         int len = 0, ch1 = 0, n = 1, _aliveOrnot = 1;
         short differ[5];
         short *aliveNum, *addNum;//*aliveOrnot,
         short _aliveNum = 0, _addNum = 0;
         vofv aliveOrnot;
         short combi_r[5];
         cout << "differ 생성 \n\n";
         for(i = 0; i < 5; ++i) {
            ///part2_1_a.패턴 분석내용 differ[i]에 담기
            differ[i] = now_figure[i][1] - db_figure.compound[0][i];
            ///part2_1_b.죽일 번호(_aliveOrnot) 수 설정
            if(isAliveornot(differ[i])) {
               _aliveOrnot *= myfunction::combination(now_figure[i][1], db_figure.compound[0][i]);
               combi_r[len++] = db_figure.compound[0][i];
            }
            ///part2_1_d.새로 만들 번호(_addNum) 수 설정
            else if(isAddnum(differ[i])) {
               _addNum += (-differ[i]);
            }
            ///part2_1_c.유지할 번호(aliveNum) 수 설정
            if(isAliveNum(differ[i])) {
               _aliveNum += now_figure[i][1];
            }
         }
         n = myfunction::combination(45, _addNum);///_addNum = myfunction::combination(45,_addNum);n 이랑 addNum 나중에 합쳐버려도 상관은 없음
         len = 0;
         cout << endl << endl;
         cout << "_aliveNum :" << _aliveNum << endl;
         cout << "_aliveOrnot :" << _aliveOrnot << endl; ///이거는 이미 combination 값이니깐
         cout << "_addNum :" << _addNum << "combination : " << n << endl;
         cout << "\n - Giving array -\n";

         ///part2_2.수 저장할 변수 할당
         aliveNum = (_aliveNum == 0)? 0 : new short[_aliveNum];
         //aliveOrnot = _aliveOrnot == 1? 0 : new short[_aliveOrnot];
         addNum = (_addNum == 0)? 0 : new short[_addNum];

         ///part2_2_a.aliveNum 찾기
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

         ///part2_2_b.aliveOrnot 찾기
         cout <<" \n2. aliveOrnot is tried to set up...now\n";
         vs cellOfaon;
         vofv aon;
         int ch3 = 0;len = 0;
         for(i = 0; _aliveOrnot && i < 5; ++i) {
            for(j = 0; j<_ver; ++j) {
                  if(isAliveornot(differ[i])
                     &&rangTest(material.num[j], now_figure[i][0])
                     &&db_figure.compound[0][i] != 0)   //1C0 방지
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
         ///part3. 새로 생성할 번호가 존재한다면 <==> 죽일 번호가 생겼다.
         while(addNum&&count1++<n) {
               int ch4=0;
               luckNum.setMaxnum(_ver);   //새로 생성하는 수 저장; luckNum; 크기는 _ver(6 or 7)
               ///part3_1. 살아있는 수 있으면 먼저 대입
               if(aliveNum)   luckNum.push_num(aliveNum, _aliveNum);
               of1 << "1 | ";
               for(int z=0;z<_aliveNum;++z)  {of1 << luckNum.num[z] << ' ';}
               of1 << " |" << '\n';
               ///part3_2_1. 살아있는 수가 있으면
               while(_aliveOrnot && count2++ < _aliveOrnot) {
                  int ch5 = 0;
                  Lnode tLnode = luckNum;
                  short* token = new short[_token];

                  ch5 = setToken(token, aliveOrnot, _token);//aliveOrnot 짤라서 token에 넣기
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
                  //중복되는지 확인
                  ch4 = myfunction::isthereNnum(tLnode, getNewnumber());
                  //중복된 게 아니라면
                  if(!ch4) setNewnumber(tLnode, p);//새로운 Newnumber에 pushing
                  tLnode.g_clearing();
                  delete token;
               }
               ///part3_2_2. 빈자리 = 랜덤수로 채움
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
