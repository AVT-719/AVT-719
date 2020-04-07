#pragma once

#include <exception>

template <class T> class List
{
protected:
	class Node
	{
	public:
		T item;//�������� ������� � ��������
		Node *prev;// ��������� �� ����������
		Node *next;//��������� �� ���������
	};

	int length; //����� ������
	Node *first;	//��������� �� ������ �������
	Node *last;	//��������� �� ��������� �������
	int looked; //������������� ��������

public:
	List(void);//����������� ��� ����������
	List(const List<T>& anotherList);//����������� �����������
	~List(void);//����������
	int sizeOfList();//����� ������� ������
	void deleteList();//������� ������
	bool EmptyList();//�������� ������ �� �������
	bool findObject(T obj);//����� ������� ��������� ��������
	T readObject(int num);//������ �������� � �������� �������
	bool changeObject(int num, T obj);//��������� �������� � �������� �������
	int getIndex(T obj);//��������� ������� � ������ � �������� ���������
	void add(T obj);//��������� ������ ��������
	bool addNewIndex(int num, T obj);//��������� ������ �������� � ������� � �������� �������
	bool deleteObject(T obj);//�������� ��������� ��������
	bool deleteIndex(int num);//�������� �������� �� ������� � �������� �������
	void show_list();
	int GetLooked() {return looked;}
	void GetTest(long long n, long long m);
	long long myrand();

	
	class Iterator
	{
	private:
		List *ptr;//��������� �� ������ ���������
		Node *cur;//��������� �� ������� ������� ���������
	public:
		Iterator(List &list){//�����������
			ptr = &list;
			beg();
		}
		
		void beg(){//��������� �� ������
			cur = ptr -> first;
		}
		
		void end(){//��������� �� ���������
			cur = ptr -> last;
		}
		
		void next(){//��������� �� ���������
			if (cur -> next != NULL)
				cur = cur -> next;
			else
				throw exception("Out of range");
		}
		
		void prev(){//��������� �� ����������
			if (cur != NULL)
				cur = cur -> prev;
			else
				throw exception("Out of range");
		}
		
		bool is_off() const{//�������� ������ ��������� �� ������� ���������
			return (cur == NULL);
		}
		
		T& operator*(){//������ � ������ �������� ��������
			if (cur != NULL)
				return cur -> item;
			else
				throw exception("Out of range");
		}
	};
	friend class Iterator;
};

//����������� ��� ����������
	template<class T> List<T>::List()
	{
		first = last = NULL;
		length = 0;
		looked = 0;
	}

//����������� �����������
	template<class T> List<T>::List(const List<T>& anotherList)
	{
		first = last = NULL;
		length = 0;
		looked = 0;
		Node *temp = anotherList.first; //������ ������, ������ ��������
		while(temp != NULL) //���� �� ����� ������
		{
			this -> add(temp -> item);
			temp = temp -> next;
		}
	}

//����������
	template<class T> List<T>::~List(void)
	{
		deleteList();
	}
	
//����� ������� ������	
	template<class T> int List<T>::sizeOfList()
	{
		return length;
	}

//������� ������
	template<class T> void List<T>::deleteList()
	{
		while(first != NULL)//���� �� ������ �� ������ ������ ���-�� ����
		{
			last = first->next;//��������� ����� ���� �������� ������
			delete first; //������� ������ �� ������� ��������
			first = last; // ����� ������ ������ �� ����� ����
		}
		looked = length;
		length = 0;
	}

//�������� ������ �� �������
	template<class T> bool List<T>::EmptyList()
	{
		return (first == NULL && length == 0 && last == NULL);
	}

//����� ������� ��������� ��������
	template<class T> bool List<T>::findObject(T obj)
	{
		Node *temp = first; //���������� ����� �������
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

//������ �������� � �������� �������
	template<class T> T List<T>::readObject(int num)
	{
		if (num < 1 || num > length)
		{
			return -1;
		}
		Node *temp;
		looked = 0;
		if (length/2 > num)//������������� 2 ������, ���� �������� ������, ��� ��������� ����� 
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

//��������� �������� � �������� �������
	template<class T> bool List<T>::changeObject(int num, T obj)
	{
		looked = 0;
		if (num < 1 || num > length)
		{
			return false;
		}
		Node *temp;
		if (length/2 > num)//������������� 2 ������, ���� �������� ������, ��� ��������� ����� 
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

//��������� ������� � ������ � �������� ���������
	template<class T> int List<T>::getIndex(T obj)
	{
		looked = 0;
		Node *temp = first; //���������� ����� �������
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

//��������� ������ ��������
	template<class T> void List<T>::add(T obj){
		looked = 0;
		Node *temp = new Node; //��������� ������ ��� ����� ��������
		temp -> next = NULL; //���������, ��� ���������� �� ���� ������ �����
		temp -> item = obj; //���������� �������� � ������
		if  (first != NULL) //���� ������ �� ����
		{
			looked++;
			temp -> prev = last; //��������� ����� �� ���� ������� � �����.����
			last -> next = temp; //��������� ����� ���� ��  ������ ��������
		}
		else //���� ������ ����
		{
			temp -> prev = NULL;  //���� ������� ��������� � �������
			first = temp; //����.��=����.��=����������� ��.
		}
		last = temp; //������ ����� �����
		length++;
	}

//��������� ������ �������� � ������� � �������� �������
	template<class T> bool List<T>::addNewIndex(int num, T obj)
	{
		if (num < 1 || num > length + 1)
		{
			return false;
		}
		if (num == length+1) //���� ��������� � ����� ������ (��� � ������ �������)
		{
			add(obj);
			return true;
		}
		else if (num == 1) //� ������
		{
			Node *temp = new Node; //����� �������
			temp -> prev = NULL; //����������� ���
			temp -> item = obj; //��������� ������
			temp -> next = first; //���������� - ������ ����� ������
			first -> prev = temp; //���� �������� ����
			first = temp;
			looked = 1;
			length++;
			return true;
		}
		int i=1;
		Node *Ins = first;
		while(i<num) //���������� �� ������ num-1 ���������
		{
			Ins=Ins->next;//������� �� ��-��, ����� ������� �����������
			i++;
		}
		Node *PrevIns = Ins -> prev; //������� �� ��-��, ������� ������������
		Node *temp = new Node;
		temp -> item = obj; //��������� ������
		if (PrevIns != 0 && length != 1)
			PrevIns -> next = temp;
		temp -> next = Ins;
        temp -> prev = PrevIns;
        Ins -> prev = temp;
		looked = num/2;
		length++;
		return true;
	}

//�������� ��������� ��������	
	template<class T> bool List<T>::deleteObject(T obj)
	{
		looked = 0;
		Node *temp = first; //���������� ����� �������
		while (temp != NULL) 
		{
			looked++;
			if (temp -> item == obj)
			{
				Node *exnext = temp -> next;
				Node *exprev = temp -> prev;
				if(exprev == NULL)//���� ��������� ��� ������
					first = exnext;
				if(exnext == NULL)//���� ��������� ��� ���������
					last = exprev;
				if(exprev != NULL)//���� ���� ����������
					exprev -> next = exnext;//��������� ����� � ���������
				if(exnext != NULL)//���� ���� ���������
				{
					exnext -> prev = exprev;//��������� ����� � ���������
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
	
//�������� �������� �� ������� � �������� �������
	template<class T> bool  List<T>::deleteIndex(int num)
	{
		looked = 0;
		if (num < 1 || num > length)
		{
			return false;
		}
		Node *temp;
		if (length/2 > num)//������������� 2 ������, ���� �������� ������, ��� ��������� ����� 
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
		if(exprev == NULL)//���� ��������� ��� ������
			first = exnext;
		if(exnext == NULL)//���� ��������� ��� ���������
			last = exprev;
		if(exprev != NULL)//���� ���� ����������
			exprev -> next = exnext;//��������� ����� � ���������
		if(exnext != NULL)//���� ���� ���������
			exnext -> prev = exprev;//��������� ����� � ���������
		delete temp;
		length--;
		return true;
	}

	template <class T> void  List<T>::show_list()
	{
	// ���� � ������ ������������ ��������, �� ��������� �� ����
   // � �������� ��������, ������� � ���������
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
			cout << "������ ����"<< endl;
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
