#include "myclass1.h"
int Linterface::procIntro(void) {
   //version setting
   short num=0,ch1=getSelect(),ch2='Y';
   cout << "**** For my victory *** " << endl;
   cout << "��Ȱ�� ���α׷� �ӵ��� ���ؼ� �ڸ����� �Է����ּ���." << endl;
   cout << " - �ڸ����� ���� ����� �����ϰ� �ٸ��ϴ�. " << endl;
   cout << " - 6�ڸ� or 7�ڸ�: ����ڸ� ����" << endl;
   cout << ">> ";cin >> num;cin.clear();
   cout << endl;
   while(!num ||num!=6 &&num!=7) {
      cout << " - ��ȿ���� �ʴ� �ڸ��� �Դϴ�. " << endl;
      cout << ">> �ٽ� �Է��ϼ���\n>> ";
      cin >> num;cin.clear();
   }
   if(ch1==num) {
      cout << " - ������ ���� �ڸ����Դϴ�." << endl;
      cout << ">> ���ο� �����͸� �������� �ʽ��ϴ�." << endl;
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
   //���� Ȯ���� �־����
   p.outSpreadpattern();
   cout << "\n***" <<_ver << "�ڸ��� ���̺� ���� ***" <<endl;
   cout << " >>�۾��� �����մϴ�." << endl;
   while(ch1!=5&&ch1!=6) {
      cout << "\n1.nȸ�� �������� " << endl;
      cout << "2.Ư�� ��ū �˻� " << endl;
      cout << "3.��ȣ ���� " << endl;
      cout << "4.���¹�ȣ ���� " << endl;
      cout << "5.�������� " << endl;
      cout << "6.���α׷� ���� " << endl;
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
   cout << "Ȯ���� ȸ���� �Է����ּ���.\n :";

}
int Linterface::procNpattern(void) {
   //find strong pattern until N
   int untilN=0,myrank=0;
   int pat_sz,total_sz;
   char ch1='y';

   //N������ ������ �м��Ѵ�.
   while(ch1!='n'&&ch1!='N') {
      Lotto* temp=new Lotto;
      cout << "\n�ֱ� n ȸ�������� ������ �м��մϴ�. " << endl;
      cout << '(' << STD_TOTAL << "ȸ���� ����Ǿ����ϴ�.)" << endl;
      cout << ">> ";cin>>untilN;
      p.setSpreadpattern(temp->getPattern(),untilN);
      cout << "�����͸� �������Դϴ�." << endl;
      cout << " . . . " << endl;
      pat_sz = temp->getPattern().size();//pattern ����
      total_sz = temp->getTotalPattern();//compound ����
      //��� ���� �˻�
      myrank=Linterface::chPat_size(pat_sz,total_sz);
      /**1**/
      //��ȿ�� pattern ������ �������
      if(myrank)
         temp->printPattern(myrank); //pattern ���
      delete temp;
      cout << "�۾��� ��� �����Ͻðڽ��ϱ�?" << endl;
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
   ///1.�������� �߰� �ؾ���
   //6���� �޴��� �Ǽ� �Ҽ� �����ϱ�,
   //�Ѱ��� Ʋ���� �Ѱ��� ��ĥ�� �ֵ���
   double sim=0,sameCount;
   int count=0,_max=p.getVersion();
   Lnode cell(_max);
   short* token=new short[_max];
   char ch1='Y',ch2='Y';
   //what Token pattern's simmularity
   //Ư�� ��ū�� ã�Ƴ���
   //�װ��� sim�� �����ߴ� indexes ����ϸ� ��
   while(ch1=='Y'||ch1=='y') {
      //v_Lnode* src=new v_Lnode;
      cout << " \n������ ��ū�� �Է����ּ���.\n";
      cout << " - �ִ� :" << _max << endl;
      cout << " - �Է� �ߴ��� ctrl+z\n>> ";
      while(count<_max&&cin >> token[count++]);//�Է�
      cin.clear();
      //cell����
      for(int i=0;i<count;++i)
         cell.num.push_back(token[i]);
      //��ū üũ
      cout << "\n... ó���� ...\n"<< endl;
      cell=p.isthereToken(cell);
      sameCount=cell.indexes.size();
      sim=sameCount/STD_TOTAL;
      cout << " - ���Ҵ� ��ū ����(sameCount) : " << sameCount << endl;
      cout << " - ���� ��ū ���缺(sim) : " << sim << endl;
      cout << " (sim = sameCount/STD_TOTAL )" << endl;
      //indexes ��� üũ
      cout << " >>����ȸ���� ����Ͻðڽ��ϱ�?\n :";
      cin >> ch2;
      if(ch2=='y'||ch2=='Y')
         cell.printIndex();
      cout << " >>�۾��� ��� �Ͻðڽ��ϱ�?\n :";
      cin >> ch1;
      //�ʱ�ȭ
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
         //1.��ȣ�Է�
         //���� �Է��� ��ȣ�� ���� sim ���
         Lnode *cell = new Lnode(_ver);
         cout << "��ȣ�� �Է��ϼ���.\n>> ";
         for(i = 0; i < _ver; ++i) {
            cin >> firstNum[i];
            cell->push_num(firstNum + i);
         }
         data.push_back(*cell);
         cout << "data_size :" << data.size() << endl;
         p.setDatasheet(data,p.getLucky());
         init_sim=data[0].simmularity;
         cout << "max_count :" << data[0].maxOfthesame << endl;
         //���� sim ���
         cout << "�ʱ� simmularity : " << init_sim << endl;
         //2.�������� Ȯ��
         if(init_sim != 0) {
            cout << "���� �۾��� �����Ͻðڽ��ϱ�?\n>> ";
            cin >> ch2;cin.clear();
            //3.�����۾�����
            if(ch2 == 'Y' || ch2 == 'y') {
               //���� ���ڸ� �������� luckyset�� ����
               s.generateNum(*cell, p);
               //printing
               s.printNewnumber();
            }
         }
         cout << "�����ߴ� ȸ���� ����Ͻðڽ��ϱ�?\n :";
         cin >> ch3;
         if(ch3 == 'Y' || ch3 == 'y')
            data[0].printIndex();

         cell->g_clearing();data.clear();
         s.l_clearing();
         cout <<" �۾��� �ٽ� �Ͻðڽ��ϱ�\n>> ";
         cin >> ch1;cin.clear();
         delete cell;
   }///---while
   return -2;
}
int Linterface::procAutonum(){}//auto generating basing on spreadpattern
