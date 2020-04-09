#include "stdafx.h"
#include "list.h"
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <numeric>


using namespace std;

typedef double MyType;

bool CheckLimits(const List<MyType>::Iterator& it)
{
	if (it.is_off())
		return true;
	else
		return false;
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	List<MyType> mylist;
	int kol;

	List<MyType>::Iterator it(mylist);
	bool isExit = false;	//‘лаг выхода
	int size, x;
	long long n,m;
	MyType z;

	
	cout << "Menu:" << endl;
	cout << "0) View list" << endl;   //¬ыводим список
	cout << "1) List size" << endl;  //–азмера списка
	cout << "2) Clean list" << endl; //„истка списка
	cout << "3) Check if list is empty" << endl; //ѕроверка списка на пустоту
	cout << "4) Check if this digit is in list" << endl; //ѕроверка наличи€ заданного значени€
	cout << "5) Digit at some position" << endl; //«начени€ с заданным номером в списке
	cout << "6) Change digit at some position" << endl; //»зменение значени€ с заданным номером в списке
	cout << "7) Position of some digit" << endl; //получение позиции в списке с заданным значением
	cout << "8) New digit" << endl; // Ќовое значение
	cout << "9) New digit at some position" << endl; //¬ключение нового значени€ в позицию с заданным номером
	cout << "10) Delete digit from list" << endl;
	cout << "11) Delete digit from list at some position" << endl; //удаление значени€ из позиции с заданным номером
	cout << "Iterator:" << endl;
	cout << "\t\t12) Put on the first" << endl; //установка на первый
	cout << "\t\t13) Put on the last" << endl; //установка на последний 
	cout << "\t\t14) Put on the next" << endl; //установка на следующий
	cout << "\t\t15) Put on the previous" << endl; //установка на предыдущий
	cout << "\t\t16) Check if iterator is out of list" << endl; //проверка выхода итератора за пределы коллекции
	cout << "\t\t17) Show chosen element" << endl; //проверка выхода итератора за пределы коллекции
	cout << "\t\t18) Change chosen element" << endl; // изменение текущего элемента
	cout << "19) Test" << endl;
	cout << "27) Exit" << endl;
	
	while(!isExit)
	{
		int ans;	// од нажатой клавиши
		cin >> ans;
		
			switch(ans)
			{
			case 0:	//
				mylist.show_list();
				break;
			case 1:	//
				size=mylist.sizeOfList();
				cout << size << endl;
				break;

			case 2:
				mylist.deleteList();
				cout<< "List is cleaned"<<endl;
				break;

			case 3:
				cout<< mylist.EmptyList()<<endl;
				break;
			case 4:
				cout << "Write the digit"<<endl;
				cin>> z;
				cout<<mylist.findObject(z)<<endl;
				break;

			case 5:
				cout << "Write the position" <<endl;
				cin>> x;
				z=mylist.readObject(x);
				if (z>-1)
				  cout << "Digit at this position = " << z << endl;
				else cout << "Not exist"  << endl;
				break;

			case 6:
				cout << "Write the position number" <<endl;
				cin>> x;
				cout << "Write the new digit" <<endl;
				cin>> z;
				cout<<mylist.changeObject(x,z)<<endl;
				break;
			
			case 7:
				cout << "Write the position" <<endl;
				cin>> z;
				cout << mylist.getIndex(z)<< endl;
				break;
			
			case 8:
				cout << "Write the new digit" <<endl;
				cin>> z;
				mylist.add(z);
				cout<< "Complete"<<endl;
				break;
			
			case 9:
				cout << "Write position:" <<endl;
				cin>> x;
				cout << "Write the new digit" <<endl;
				cin>> z;
				cout<<mylist.addNewIndex(x,z)<<endl;
				break;

            case 10:
				cout << "Write the digit to delete" <<endl;
				cin>> z;
				cout<<mylist.deleteObject(z)<<endl;
				break;
			case 11:
				cout << "Write the position:" <<endl;
				cin>> x;
				cout<<mylist.deleteIndex(x)<<endl;
				break;
			case 12:
				it.beg();
				break;
			case 13:
				it.end();
				break;
			case 14:
				it.next();
				cout << CheckLimits(it)<<endl;
				break;
			case 15:
				it.prev();
				cout << CheckLimits(it)<<endl;
				break;
			case 16:
				cout << CheckLimits(it)<<endl;
				break;
			case 17:
				try
				{
					cout << "Choosed element: "<< *it  << endl;
				}
				catch(exception e)
				{
					cout << e.what() << endl;
				}
				break;
			case 18:
				try
				{
					cout << "Write the new digit" <<endl;
					cin>> z;
					*it = z;
				}
				catch(exception e)
				{
					cout << e.what() << endl;
				}
				break;
			case 19:
				cout << "Write the size(more than 1000)" <<endl;
				cin>> n;
				cout << "Interval" <<endl;
				cin>> m;
				system("cls");
				for(int iter = 1000;iter <=n;iter+=1000){
					mylist.GetTest(iter,  m);
				}
				break;
			case 27:	//¬ыход
				isExit = true;
				break;
			default:	//Ќажата клавиша, не соответствующа€ ни одной команде
				cout << "This sommand can't be recognized" << endl;
			}
	}
	cout << "\nWrite the list size" << endl;
	cin>> kol;
	return 0;
}

