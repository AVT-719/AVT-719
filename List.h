#pragma once

#include <exception>

template <class T> class List
{
protected:
	class Node
	{
	public:
		T item;//значение объекта в элементе
		Node *prev;// указатель на предыдущий
		Node *next;//указатель на следующий
	};

	int length; //длина списка
	Node *first;	//указатель на первый элемент
	Node *last;	//указатель на последний элемент
	int looked; //просмотренные элементы

public:
	List(void);//конструктор без параметров
	List(const List<T>& anotherList);//конструктор копирования
	~List(void);//деструктор
	int sizeOfList();//опрос размера списка
	void deleteList();//очистка списка
	bool EmptyList();//проверка списка на пустоту
	bool findObject(T obj);//опрос наличия заданного значения
	T readObject(int num);//чтение значения с заданным номером
	bool changeObject(int num, T obj);//изменение значения с заданным номером
	int getIndex(T obj);//получение позиции в списке с заданным значением
	void add(T obj);//включение нового значения
	bool addNewIndex(int num, T obj);//включение нового значения в позицию с заданным номером
	bool deleteObject(T obj);//удаление заданного значения
	bool deleteIndex(int num);//удаления значения из позиции с заданным номером
	void show_list();
	int GetLooked() {return looked;}
	void GetTest(long long n, long long m);
	long long myrand();

	
	class Iterator
	{
	private:
		List *ptr;//указатель на объект коллекции
		Node *cur;//указатель на текущий элемент коллекции
	public:
		Iterator(List &list){//конструктор
			ptr = &list;
			beg();
		}
		
		void beg(){//установка на первый
			cur = ptr -> first;
		}
		
		void end(){//установка на последний
			cur = ptr -> last;
		}
		
		void next(){//установка на следующий
			if (cur -> next != NULL)
				cur = cur -> next;
			else
				throw exception("Out of range");
		}
		
		void prev(){//установка на предыдущий
			if (cur != NULL)
				cur = cur -> prev;
			else
				throw exception("Out of range");
		}
		
		bool is_off() const{//проверка выхода итератора за пределы коллекции
			return (cur == NULL);
		}
		
		T& operator*(){//доспуп к данным текущего элемента
			if (cur != NULL)
				return cur -> item;
			else
				throw exception("Out of range");
		}
	};
	friend class Iterator;
};

//конструктор без параметров
	template<class T> List<T>::List()
	{
		first = last = NULL;
		length = 0;
		looked = 0;
	}

//конструктор копирования
	template<class T> List<T>::List(const List<T>& anotherList)
	{
		first = last = NULL;
		length = 0;
		looked = 0;
		Node *temp = anotherList.first; //начало списка, откуда копируем
		while(temp != NULL) //пока не конец списка
		{
			this -> add(temp -> item);
			temp = temp -> next;
		}
	}

//деструктор
	template<class T> List<T>::~List(void)
	{
		deleteList();
	}
	
//опрос размера списка	
	template<class T> int List<T>::sizeOfList()
	{
		return length;
	}

//очистка списка
	template<class T> void List<T>::deleteList()
	{
		while(first != NULL)//пока по адресу на начало списка что-то есть
		{
			last = first->next;//резервная копия след элемента списка
			delete first; //очистка памяти от первого элемента
			first = last; // смена адреса начала на адрес след
		}
		looked = length;
		length = 0;
	}

//проверка списка на пустоту
	template<class T> bool List<T>::EmptyList()
	{
		return (first == NULL && length == 0 && last == NULL);
	}

//опрос наличия заданного значения
	template<class T> bool List<T>::findObject(T obj)
	{
		Node *temp = first; //запоминаем адрес первого
		looked = 0;
		while (temp != NULL)
		{
			if (temp -> item == obj)
				return true;
			else
				temp = temp -> next;		
			looked++;
		}
		return false;
	}

//чтение значения с заданным номером
	template<class T> T List<T>::readObject(int num)
	{
		if (num < 1 || num > length)
		{
			return -1;
		}
		Node *temp;
		looked = 0;
		if (length/2 > num)//рассматриваем 2 случая, если середина больше, чем выбранный номер 
		{
			temp = first;
			for( int cur = 1; cur != num; cur++, looked++ )
				temp = temp -> next;
		}
		else 
		{
			temp = last;
			for( int cur = length; cur != num; cur--, looked++ )
				temp = temp -> prev;
		}
		return temp -> item;
	}

//изменение значения с заданным номером
	template<class T> bool List<T>::changeObject(int num, T obj)
	{
		looked = 0;
		if (num < 1 || num > length)
		{
			return false;
		}
		Node *temp;
		if (length/2 > num)//рассматриваем 2 случая, если середина больше, чем выбранный номер 
		{
			temp = first;
			for( int cur = 1; cur != num; cur++, looked++ )
				temp = temp -> next;
		}
		else 
		{
			temp = last;
			for( int cur = length; cur != num; cur--, looked++ )
				temp = temp -> prev;
		}
		temp -> item = obj;
		return true;
	}

//получение позиции в списке с заданным значением
	template<class T> int List<T>::getIndex(T obj)
	{
		looked = 0;
		Node *temp = first; //запоминаем адрес первого
		while (temp != NULL)
		{
			looked++;
			if (temp -> item == obj)
				return looked;
			else
				temp = temp -> next;
		}
		return 0;
	}

//включение нового значения
	template<class T> void List<T>::add(T obj){
		looked = 0;
		Node *temp = new Node; //выделение памяти под новое значение
		temp -> next = NULL; //указываем, что изначально по след адресу пусто
		temp -> item = obj; //записываем значение в список
		if  (first != NULL) //если список не пуст
		{
			looked++;
			temp -> prev = last; //указываем адрес на пред элемент в сооот.поле
			last -> next = temp; //указываем адрес след за  концом элемента
		}
		else //если список пуст
		{
			temp -> prev = NULL;  //пред элемент указывает в пустоту
			first = temp; //перв.эл=посл.эл=добавленный эл.
		}
		last = temp; //меняем адрес конца
		length++;
	}

//включение нового значения в позицию с заданным номером
	template<class T> bool List<T>::addNewIndex(int num, T obj)
	{
		if (num < 1 || num > length + 1)
		{
			return false;
		}
		if (num == length+1) //если вставляем в конец списка (или в начало пустого)
		{
			add(obj);
			return true;
		}
		else if (num == 1) //в начало
		{
			Node *temp = new Node; //новый элемент
			temp -> prev = NULL; //предыдущего нет
			temp -> item = obj; //заполняем данные
			temp -> next = first; //предыдущий - бывший конец списка
			first -> prev = temp; //если элементы есть
			first = temp;
			looked = 1;
			length++;
			return true;
		}
		int i=1;
		Node *Ins = first;
		while(i<num) //отчитываем от начала num-1 элементов
		{
			Ins=Ins->next;//доходим до эл-та, перед которым вставляется
			i++;
		}
		Node *PrevIns = Ins -> prev; //доходим до эл-та, который предшествует
		Node *temp = new Node;
		temp -> item = obj; //заполняем данные
		if (PrevIns != 0 && length != 1)
			PrevIns -> next = temp;
		temp -> next = Ins;
        temp -> prev = PrevIns;
        Ins -> prev = temp;
		looked = num/2;
		length++;
		return true;
	}

//удаление заданного значения	
	template<class T> bool List<T>::deleteObject(T obj)
	{
		looked = 0;
		Node *temp = first; //запоминаем адрес первого
		while (temp != NULL) 
		{
			looked++;
			if (temp -> item == obj)
			{
				Node *exnext = temp -> next;
				Node *exprev = temp -> prev;
				if(exprev == NULL)//Если удаляемый был первым
					first = exnext;
				if(exnext == NULL)//Если удаляемый был последним
					last = exprev;
				if(exprev != NULL)//Если есть предыдущий
					exprev -> next = exnext;//Исключаем связь с удаляемым
				if(exnext != NULL)//Если есть следующий
				{
					exnext -> prev = exprev;//Исключаем связь с удаляемым
				}
				delete temp;
	            length--;
				return true;
			}
			else
				temp = temp -> next;
			
		}
		return false;
	}
	
//удаление значения из позиции с заданным номером
	template<class T> bool  List<T>::deleteIndex(int num)
	{
		looked = 0;
		if (num < 1 || num > length)
		{
			return false;
		}
		Node *temp;
		if (length/2 > num)//рассматриваем 2 случая, если середина больше, чем выбранный номер 
		{
			temp = first;
			for( int cur = 1; cur != num; cur++, looked++)// 
				temp = temp -> next;
		}
		else 
		{
			temp = last;
			for( int cur = length; cur != num; cur--, looked++ )//
				temp = temp -> prev;
		}
		Node *exnext = temp -> next;
		Node *exprev = temp -> prev;
		if(exprev == NULL)//Если удаляемый был первым
			first = exnext;
		if(exnext == NULL)//Если удаляемый был последним
			last = exprev;
		if(exprev != NULL)//Если есть предыдущий
			exprev -> next = exnext;//Исключаем связь с удаляемым
		if(exnext != NULL)//Если есть следующий
			exnext -> prev = exprev;//Исключаем связь с удаляемым
		delete temp;
		length--;
		return true;
	}

	template <class T> void  List<T>::show_list()
	{
	// Если в списке присутствуют элементы, то пробегаем по нему
   // и печатаем элементы, начиная с головного
		if(!EmptyList())
		{
			Node* temp = first;
			cout << "( ";
			while(temp->next != NULL)
			{
				cout << temp->item << ", ";
				temp = temp->next;
			}

			cout << temp->item << " )" << endl;
		}
		else
			cout << "Список пуст"<< endl;
		looked = length;
	}

	template <class T>	long long List<T>::myrand()
	{
		return rand()<<16 | rand ();
	}

	template <class T>	void  List<T>::GetTest(long long n, long long m)
	{
		List<long long>  testA;
		for(int i=0; i<n; i++)
			testA.add(myrand()%m);
		double A=0,D=0,R=0;
		for (int i=0; i<n; i++)
		{
			testA.deleteIndex(myrand()%n);
			D+=testA.GetLooked();
			testA.addNewIndex(myrand()%n, myrand()%m);
			A+=testA.GetLooked();
			testA.findObject(myrand()%m);
			R+=testA.GetLooked();
		}
		cout <<"Ydalenie: " << D/(n)<< "   ";
		cout <<"Vstavka: " << A/(n)<< "   ";
		cout <<"Poisk: " <<  R/(n)<< endl;
		
	}
