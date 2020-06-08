#include "myclass1.h"
int Linterface::procIntro(void) {
   //version setting
   short num=0,ch1=getSelect(),ch2='Y';
   cout << "**** For my victory *** " << endl;
   cout << "원활한 프로그램 속도를 위해서 자리수를 입력해주세요." << endl;
   cout << " - 자리수에 따라 결과가 상이하게 다릅니다. " << endl;
   cout << " - 6자리 or 7자리: 행운자리 포함" << endl;
   cout << ">> ";cin >> num;cin.clear();
   cout << endl;
   while(!num ||num!=6 &&num!=7) {
      cout << " - 유효하지 않는 자리수 입니다. " << endl;
      cout << ">> 다시 입력하세요\n>> ";
      cin >> num;cin.clear();
   }
   if(ch1==num) {
      cout << " - 이전과 같은 자리수입니다." << endl;
      cout << ">> 새로운 데이터를 생성하지 않습니다." << endl;
   }
   if(num&&ch1!=num) {
      setSelect(num);
      if(num==6||num==7)
         p.setLotto(num);
   }
   return -2;
}
int Linterface::procTable(void) {
   //menual
   int ch1=0,ch2=0;
   short _ver=p.getVersion();
   //패턴 확인차 넣어뒀음
   p.outSpreadpattern();
   cout << "\n***" <<_ver << "자리수 테이블 생성 ***" <<endl;
   cout << " >>작업을 시작합니다." << endl;
   while(ch1!=5&&ch1!=6) {
      cout << "\n1.n회차 유력패턴 " << endl;
      cout << "2.특정 토큰 검색 " << endl;
      cout << "3.번호 교정 " << endl;
      cout << "4.유력번호 생성 " << endl;
      cout << "5.메인으로 " << endl;
      cout << "6.프로그램 종료 " << endl;
      cout << ">> ";cin>>ch1;
      //table
      if(ch1==1) ch2=procNpattern();
      else if(ch1==2) ch2=procTokenpattern();
      else if(ch1==3) ch2=procRevising();
      else if(ch1==4) ch2=procAutonum();
      else if(ch1==5) return -2;
      else ch2=-4;
   }
   return ch2;
}
int procNprint(void) {
   vs list_num;
   cout << "확인할 회차를 입력해주세요.\n :";

}
int Linterface::procNpattern(void) {
   //find strong pattern until N
   int untilN=0,myrank=0;
   int pat_sz,total_sz;
   char ch1='y';

   //N까지의 패턴을 분석한다.
   while(ch1!='n'&&ch1!='N') {
      Lotto* temp=new Lotto;
      cout << "\n최근 n 회차까지의 패턴을 분석합니다. " << endl;
      cout << '(' << STD_TOTAL << "회까지 진행되었습니다.)" << endl;
      cout << ">> ";cin>>untilN;
      p.setSpreadpattern(temp->getPattern(),untilN);
      cout << "데이터를 생성중입니다." << endl;
      cout << " . . . " << endl;
      pat_sz = temp->getPattern().size();//pattern 개수
      total_sz = temp->getTotalPattern();//compound 개수
      //출력 조건 검사
      myrank=Linterface::chPat_size(pat_sz,total_sz);
      /**1**/
      //유효한 pattern 사이즈 범위라면
      if(myrank)
         temp->printPattern(myrank); //pattern 출력
      delete temp;
      cout << "작업을 계속 시작하시겠습니까?" << endl;
      cout << ">> ";cin >>ch1;cin.clear();
   }
   /**1**/
   /*
   cout << "pat_sz :" << pat_sz << endl;
   cout << "total_sz :" << total_sz << endl;
   cout << "myrank :" << myrank << endl;
   */
}
int Linterface::procTokenpattern(void) {
   ///1.범위교정 추가 해야함
   //6개를 받더라도 실수 할수 있으니깐,
   //한개가 틀리면 한개만 고칠수 있도록
   double sim=0,sameCount;
   int count=0,_max=p.getVersion();
   Lnode cell(_max);
   short* token=new short[_max];
   char ch1='Y',ch2='Y';
   //what Token pattern's simmularity
   //특정 토큰을 찾아내서
   //그것의 sim과 유사했던 indexes 출력하면 됨
   while(ch1=='Y'||ch1=='y') {
      //v_Lnode* src=new v_Lnode;
      cout << " \n조사할 토큰을 입력해주세요.\n";
      cout << " - 최대 :" << _max << endl;
      cout << " - 입력 중단은 ctrl+z\n>> ";
      while(count<_max&&cin >> token[count++]);//입력
      cin.clear();
      //cell형성
      for(int i=0;i<count;++i)
         cell.num.push_back(token[i]);
      //토큰 체크
      cout << "\n... 처리중 ...\n"<< endl;
      cell=p.isthereToken(cell);
      sameCount=cell.indexes.size();
      sim=sameCount/STD_TOTAL;
      cout << " - 같았던 토큰 개수(sameCount) : " << sameCount << endl;
      cout << " - 현재 토큰 유사성(sim) : " << sim << endl;
      cout << " (sim = sameCount/STD_TOTAL )" << endl;
      //indexes 출력 체크
      cout << " >>유사회차를 출력하시겠습니까?\n :";
      cin >> ch2;
      if(ch2=='y'||ch2=='Y')
         cell.printIndex();
      cout << " >>작업을 계속 하시겠습니까?\n :";
      cin >> ch1;
      //초기화
      cell.g_clearing();
      cell.setMaxnum(_max);
      count=0;
   }
}
int Linterface::procRevising(void){
   cout << "Revising" << endl;
   double init_sim = 0;
   int i,j,k;
   short _ver = p.getVersion();
   short *firstNum = new short[_ver];
   char ch1 = 'Y', ch2 = 'Y', ch3 = 'Y';
   luckyset s;
   v_Lnode data;
   while(ch1 == 'Y' || ch1 == 'y') {
         //1.번호입력
         //현재 입력한 번호에 대한 sim 출력
         Lnode *cell = new Lnode(_ver);
         cout << "번호를 입력하세요.\n>> ";
         for(i = 0; i < _ver; ++i) {
            cin >> firstNum[i];
            cell->push_num(firstNum + i);
         }
         data.push_back(*cell);
         cout << "data_size :" << data.size() << endl;
         p.setDatasheet(data,p.getLucky());
         init_sim=data[0].simmularity;
         cout << "max_count :" << data[0].maxOfthesame << endl;
         //현재 sim 출력
         cout << "초기 simmularity : " << init_sim << endl;
         //2.교정여부 확인
         if(init_sim != 0) {
            cout << "교정 작업을 시작하시겠습니까?\n>> ";
            cin >> ch2;cin.clear();
            //3.교정작업시작
            if(ch2 == 'Y' || ch2 == 'y') {
               //들어온 숫자를 바탕으로 luckyset에 형성
               s.generateNum(*cell, p);
               //printing
               s.printNewnumber();
            }
         }
         cout << "유사했던 회차를 출력하시겠습니까?\n :";
         cin >> ch3;
         if(ch3 == 'Y' || ch3 == 'y')
            data[0].printIndex();

         cell->g_clearing();data.clear();
         s.l_clearing();
         cout <<" 작업을 다시 하시겠습니까\n>> ";
         cin >> ch1;cin.clear();
         delete cell;
   }///---while
   return -2;
}
int Linterface::procAutonum(){}//auto generating basing on spreadpattern
