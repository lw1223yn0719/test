#include<iostream>  
#include<string.h>
#include<stdio.h>
using  namespace  std;
class  String
{
	char* pData;
public:
	String(){ pData = NULL;}
	void setString(const  char* pStr) {

		int len = strlen(pStr);
		pData = new char[len + 1];
		strcpy(pData, pStr);

	}
	//拷贝构造函数定义
	String(const String& str)
	{
		int len = strlen(str.pData);
		pData = new char[len + 1];
		strcpy(pData, str.pData);
	}
	~String()
	{

		if (pData != NULL)
			delete[] pData;
		pData = NULL;

	}

	//  ">"  运算符重载

	bool operator >(String& str) {
		int i = strcmp(pData, str.pData);
		return i > 0 ? true : false;
	}
	bool operator ==(String& str) {
		if (strcmp(pData, str.pData) == 0) {
			return true;
		}
		else return false;
	}

	//采用友元形式完成输出运算符重载
	friend  ostream& operator  <<  (ostream& out, const  String& obj);
	String& operator =(String& str) {
		if (pData != NULL) {
			delete[]pData;
			pData = NULL;
		}
		int len = strlen(str.pData);
		pData = new char[len + 1];
		strcpy(pData, str.pData);
		return *this;
	}
};
ostream& operator  <<  (ostream& out, const  String& obj)

{
	cout << obj.pData;
	return  cout;
}

class Point {
private:
	double x, y;
public:
	Point() {
		x = y = 0;
	}
	~Point() {}
	void setPoint(double x, double y) {
		this->x = x;
		this->y = y;
	}
		double getx(){
			return x;
		}
		double gety() {
			return y;
		}
		bool operator >(Point& p) {
			if (x > p.getx()) {
				return true;
			}
			else return false;
		}
		friend ostream& operator <<(ostream& out,Point &p);
		bool operator ==( Point& P) {
			if (x ==P.getx() && y == P.gety()) {
				return true;
			}
			else return false;
		}
		Point& operator =(Point& p) {
			x = p.getx();
			y = p.gety();
			return *this;
		}
};
ostream& operator <<(ostream& out, Point& p) {
	cout << "(" << p.getx() << "," << p.gety() << ") ";
	return cout;
}

template<class  T>
class  DynamicArray;
template<class  T>
class  node {          //定义结构模板
	T  val;                        //val取任意类型，即模板参数类型
	node<T>* next;        //此处node为结构模板
public:
	node() {
		next = NULL;
	}
	node(T  a) {
		val = a;
		next = NULL;
	}
	void setnode(T a) {
		val = a;
	}
	friend  class  DynamicArray<T>;
};

template<class  T>
class  DynamicArray
{
	node<T>* head=NULL;
	node<T>* tail=NULL;
	node<T>* p=NULL;
	int reallen;
	int start_len=10;
public:
	DynamicArray(int n) {
		reallen = n;
		for (int i = 0; i < 10; i++) {
			node<T>* r = new node<T>;
			if (head == NULL) {
				head = r;
			}
			else {
				tail->next = r;;
			}
			tail = r;
		}
		p = head;
	}
	~DynamicArray() {
		node<T>* t;
		for (node<T>*p = head; p; ) {
			t = p; p = p->next;
				delete t;
		}
	}
	void SelectSort() {
		node<T>* t=new node<T>;
		t->next = NULL;
		p = head;
		tail = head;
		int i = 0; int j = 0;
		for (i = 0; i < reallen; i++) {
			for (j = 0; j < reallen; j++) {
				if (tail->val >p->val ) {
					t->val = p->val;
					p->val = tail->val;
					tail->val = t->val;
				}
				tail = tail->next;
			}
			p = p->next;
			tail = head;
		}
	}
	void setlist(T t) {
		p->val = t;
		p = p->next;
	}
	int AddItem(T t) {
		node<T>* nodes = new node<T>(t);
		if (nodes == NULL)
		{
			return -1;
		}
		if (head == NULL) {
			head = nodes;
		}
		else { tail->next = nodes; }
		tail = nodes;
		tail->next = NULL;
		start_len++;
		return start_len;
	}
	void print() {
		p = head;
		for (int i=0;i<reallen;i++ ) {
			cout << p->val << " "; p = p->next;
		}
		cout <<"数组长度=" << reallen;
		cout << endl;
	}
	void InsertItem(int index, T aData) {
		node<T>* nodes = new node<T>(aData);
			if (index == 0) {
				reallen++;
				nodes->next=head;
				head = nodes;
			}
			else if (index > 0 && index < reallen) {
				reallen++;
                p = head;
		        tail = head->next;
				for(int i = 1; i < reallen; i++) {
					if (i == index) {
						p->next = nodes;
						nodes->next = tail;
						break;
					}
					p = tail;
					tail = p->next;
				}

			}
			else if(index>reallen-1) {				
				p = head;
				for (int i = 1;i < reallen; i++) { p = p->next; }
				reallen++;
				p->next = nodes;
			}
	}
	bool RemoveAt(int index) {
		node<T>* r = head;
		p = head->next;
		if (index==0) {
			reallen--;
			head = p;
			delete r;
			r = NULL;
			return true;
		}
		else if(index>0&&index<reallen){
			for (int i = 1; i < reallen; i++) {
				if (i==index) {
					reallen--;
					r->next = p->next;
					delete p;
					p = NULL;
					return true;
				}
				r = p;
				p = p->next;
			}
		}
		else {
			cout << "未查找到元素";
			return false;
		}
	}
};

int  main()
{
	int  Choice = 0;
	int  length = 0;
	for (;;) {
		cout << "请选择需要配置的数组类型：0(退出），1（String），2（Float），3（Int）,4（Point）" << endl; cin >> Choice;
		if (Choice == 0)break;
		cout << "请输入数组长度" << endl; cin >> length;
		cout << "请输入数组元素" << endl;
		//String数组

		 if (Choice == 1) {
			DynamicArray<String>  Stringlist(length);
			String   nTemp;
			char str[10];
			if (length < 11) {
				for (int i = 0; i < length; i++) {
					cin >> str;
					nTemp.setString(str);
					Stringlist.setlist(nTemp);
				}
			}
			else {
				int i = 0;
				for (; i < 10; i++) {
					cin >> str;
					nTemp.setString(str);
					Stringlist.setlist(nTemp);
				}
				for (; i < length; i++) {
					cin >> str;
					nTemp.setString(str);
					Stringlist.AddItem(nTemp);
				}
			}
			cout << "数组元素如下：" << endl;
			Stringlist.print();
			for (;;)
			{
				int fun = 0;
				cout << "请输入要求执行的功能编号：1插入，2删除，3排序,0退出" << endl;
				cin >> fun;
				if (fun == 1) {
					int index;
					String temp;
					char str[20];
					cout << "请输入需要插入的位置以及元素" << endl;
					cin >> index >> str;
					temp.setString(str);
					Stringlist.InsertItem(index, temp);
					Stringlist.print();
				}
				else if (fun == 2) {
					int temp;
					cout << "请输入需要删除的元素的下标" << endl;
					cin >> temp;
					if (Stringlist.RemoveAt(temp)) {
						cout << "删除成功";
					}
					else {
						cout << "删除失败";
					}
					Stringlist.print();
				}
				else if (fun == 3) {
					Stringlist.SelectSort();
					cout << "排序后的数组为：" << endl;
					Stringlist.print();
				}
				else if (fun == 0) { break; }
				else {
					cout << "暂未开发" << endl;
				}
			}
		}

		//Float数组
		else  if (Choice == 2) {
			DynamicArray<float>  floatlist(length);
			float   nTemp;
			if (length < 11) {
				for (int i = 0; i < length; i++) {
					cin >> nTemp;

					floatlist.setlist(nTemp);
				}
			}
			else {
				int i = 0;
				for (; i < 10; i++) {
					cin >> nTemp;
					floatlist.setlist(nTemp);
				}
				for (; i < length; i++) {
					cin >> nTemp;
					floatlist.AddItem(nTemp);
				}
			}
			cout << "数组元素如下：" << endl;
			floatlist.print();
			for (;;)
			{
				int fun = 0;
				cout << "请输入要求执行的功能编号：1插入，2删除，3排序,0退出" << endl;
				cin >> fun;
				if (fun == 1) {
					int index;
					float temp;
					cout << "请输入需要插入的位置以及元素" << endl;
					cin >> index >> temp;
					floatlist.InsertItem(index, temp);
					floatlist.print();
				}
				else if (fun == 2) {
					float temp;
					cout << "请输入需要删除的元素的下标" << endl;
					cin >> temp;
					if (floatlist.RemoveAt(temp)) {
						cout << "删除成功";
					}
					else {
						cout << "删除失败";
					}
					floatlist.print();
				}
				else if (fun == 3) {
					floatlist.SelectSort();
					cout << "排序后的数组为：" << endl;
					floatlist.print();
				}
				else if (fun == 0) { break; }
				else {
					cout << "暂未开发" << endl;
				}
			}
		}

		//Int数组
		else if (Choice == 3) {
			DynamicArray<int>  intlist(length);
			int   nTemp;
			if (length < 11) {
				for (int i = 0; i < length; i++) {
					cin >> nTemp;
					intlist.setlist(nTemp);
				}
			}
			else {
				int i = 0;
				for (; i < 10; i++) {
					cin >> nTemp;
					intlist.setlist(nTemp);
				}
				for (; i < length; i++) {
					cin >> nTemp;
					intlist.AddItem(nTemp);
				}
			}
			cout << "数组元素如下：" << endl;
			intlist.print();
			for (;;)
			{
				int fun = 0;
				cout << "请输入要求执行的功能编号：1插入，2删除，3排序,0退出" << endl;
				cin >> fun;
				if (fun == 1) {
					int index;
					int temp;
					cout << "请输入需要插入的位置以及元素" << endl;
					cin >> index >> temp;
					intlist.InsertItem(index, temp);
					intlist.print();
				}
				else if (fun == 2) {
					int temp;
					cout << "请输入需要删除的元素的下标" << endl;
					cin >> temp;
					if (intlist.RemoveAt(temp)) {
						cout << "删除成功";
					}
					else {
						cout << "删除失败";
					}
					intlist.print();
				}
				else if (fun == 3) {
					intlist.SelectSort();
					cout << "排序后的数组为：" << endl;
					intlist.print();
				}
				else if (fun == 0) { break; }
				else {
					cout << "暂未开发" << endl;
				}
			}
		}

		//Point数组
		else if (Choice == 4) {
			DynamicArray<Point>  Pointlist(length);
			Point   nTemp;
			double x, y;
			if (length < 11) {
				for (int i = 0; i < length; i++) {
					cin >> x >> y;
					nTemp.setPoint(x, y);
					Pointlist.setlist(nTemp);
				}
			}
			else {
				int i = 0;
				for (; i < 10; i++) {
					cin >> x >> y;
					nTemp.setPoint(x, y);
					Pointlist.setlist(nTemp);
				}
				for (; i < length; i++) {
					cin >> x >> y;
					nTemp.setPoint(x, y);
					Pointlist.AddItem(nTemp);
				}
			}
			cout << "数组元素如下：" << endl;
			Pointlist.print();
			for (;;)
			{
				int fun = 0;
				cout << "请输入要求执行的功能编号：1插入，2删除，3排序,0退出" << endl;
				cin >> fun;
				if (fun == 1) {
					int index;
					Point  temp;
					double a, b;
					cout << "请输入需要插入的位置以及元素" << endl;
					cin >> index >> a >> b;
					temp.setPoint(a, b);
					Pointlist.InsertItem(index, temp);
					Pointlist.print();
				}
				else if (fun == 2) {
					int temp;
					cout << "请输入需要删除的元素的下标" << endl;
					cin >> temp;
					if (Pointlist.RemoveAt(temp)) {
						cout << "删除成功";
					}
					else {
						cout << "删除失败";
					}
					Pointlist.print();
				}
				else if (fun == 3) {
					Pointlist.SelectSort();
					cout << "排序后的数组为：" << endl;
					Pointlist.print();
				}
				else if (fun == 0) { break; }
				else {
					cout << "暂未开发" << endl;
				}
			}
		}
	}
	return  0;
}



