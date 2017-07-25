#include <iostream>
#include <vector>

//auto��decltype�Ƶ�
double foo(){ return 0.0; }
int& bar(){ int a = 0; return a; }
float *bar1(){ float a = 0.0f; return &a; }

class White{};
class Black{};

template<typename T1, typename T2>
auto Sum(T1 t1, T2 t2) ->decltype(t1 + t2)
{
	auto s = t1 + t2;
	std::cout << typeid(s).name() << std::endl;
	return s;
}

void Overloaded(int){}
void Overloaded(char){}
int && RvalRe(){ return 1; }
const bool Func(int){ return true; }

int main()
{
	int x;
	int *y = &x;

	auto *a = &x;		//a: int*
	auto &b = x;		//b: int&
	auto c = y;			//c: int*
	auto *d = y;		//d: int*
	//auto *e = foo();	//����ʧ�ܣ�ָ�벻��ָ��һ����ʱ����
	//auto &f = foo();	//����ʧ�ܣ�nonconst����ֵ���ò��ܺ�һ����ʱ������
	auto g = bar();		//g: int
	auto &h = bar();	//h: int&

	//cv���Ʒ���const��volatile
	//auto��������ͨ�������ܴӳ�ʼ�����ʽ�д���cv���Ʒ�
	//��auto���������ú�ָ�����,����Ա�����ԭ�����������
	const auto a1 = foo();		//a1: const double
	const auto &b1 = foo();		//b1: const double&
	volatile auto *c1 = bar1();	//c1: volatile float*

	auto d1 = a1;				//d1: double
	auto &e1 = a1;				//e1: const double&	
	auto f1 = c1;				//f1: float*
	volatile auto &g1 = c1;		//g1: volatile float*&
	volatile auto h1 = c1;		//h1: volatile float*

	//�����autoʹ��
	/*1��������Ϊ������������:
		void fun(auto i){}
		*/

	/*2���������ηǾ�̬�ĳ�Ա����
	struct f
	{
		auto var = 10;
	};*/

	/*3��������ģ��ʵ����ʱʹ��auto
	std::vector<auto> v = { 1 };
	*/

	/*4�����������������������
	int arr[3];
	auto x[3] = arr;
	*/

	White wh;
	Black bl;
	White wh2;

	//is_sameģ�溯����Ա����value�ڱ���ʱ�õ���Ϣ����hash_code������ʱ�õ���Ϣ
	bool bFlags = std::is_same<White, Black>();	//false 0
	
	bFlags = (typeid(wh).hash_code() == typeid(bl).hash_code());
	std::cout << bFlags << std::endl;		//false 0

	bFlags = (typeid(wh).hash_code() == typeid(wh2).hash_code());
	std::cout << bFlags << std::endl;		//true	1

	/************************************************************************/
	//decltype
	std::vector<int> vec;
	typedef decltype(vec.begin()) vectype;
	for (vectype iv = vec.begin(); iv != vec.end(); ++iv)
	{	}
	for (decltype(vec)::iterator it = vec.begin(); it != vec.end(); ++it)
	{	}

	int i = 4;
	long l = 5;
	auto il = Sum<int, long>(i, l);
	std::cout << il << std::endl;
	std::cout << typeid(il).name() << std::endl;

	int aa;
	decltype(aa) bb;	//bb : int
	//decltype((aa)) cc;	//cc : int&�� ����ʧ��	error

	//1�����e��û�д����ŵı�Ƿ����ʽ���������Ա���ʱ��ʽ����ôdecltype(e)��Ϊe��������ʵ�����ͣ�
	//2�����򣬼���e��������T�����e��һ������ֵ(xvalue)����ôdecltype(e)ΪT&&��
	//3�����򣬼���e��������T�����e��һ����ֵ����decltype(e)ΪT&��
	//4�����򣬼���e��������T����decltype(e)������ΪT��
	//
	//���Ƶ�����
	//��1�����Ե�֪decltype(aa) bb����aaΪ��Ǳ��ʽ��ʹ���Ƶ�����1����֪bb������Ϊint��
	//��2����decltype((aa)) cc;��(aa)���Ǳ�Ǳ��ʽ��ȴ��һ����ֵ�����԰����Ƶ�����3��cc������Ϊint&.

	int ii = 4;
	int arr[5] = { 0 };
	int *ptr = arr;
	struct S{ double d; }s;

	//����1��
	decltype(arr) var1;			//int[5]����Ǳ��ʽ
	decltype(ptr) var2;			//int*����Ǳ��ʽ
	decltype(s.d) var3;			//double����Ǳ��ʽ
	//decltype(Overloaded) var4;	//�޷�ͨ�����룬�����Ǹ����غ���

	//����2��
	decltype(RvalRe()) var5 = 1;//int&&

	//����3:
	decltype(true ? ii : ii) var6 = ii;	//int&����Ԫ�����������һ��i����ֵ
	decltype((ii)) var7 = ii;			//int&����Բ���ŵ���ֵ
	decltype(++ii) var8 = ii;			//int&��++ii����ii����ֵ
	decltype(arr[3]) var9 = ii;			//int&��[]����������ֵ
	decltype(*ptr) var10 = ii;			//int&��*����������ֵ
	decltype("lval") var11 = "lval";	//const char(&)[5]���ַ������泣��Ϊ��ֵ

	//����4��
	decltype(1) var12;					//int�����ַ���������ֵΪ��ֵ
	decltype(ii++) var13;				//int��ii++������ֵ
	decltype((Func(1))) var14;			//const bool��Բ���ſɺ���

	//ʹ��ģ����is_lvalue_reference�ĳ�Աvalue���鿴decltype��Ч����1��ʾΪ��ֵ���ã�0��֮
	//ʹ��ģ����is_rvalue_reference�ĳ�Աvalue���鿴decltype��Ч����1��ʾΪ��ֵ���ã�0��֮
	std::cout << std::is_lvalue_reference<decltype(true ? ii : ii)>::value << std::endl;	//1
	std::cout << std::is_lvalue_reference<decltype((ii))>::value << std::endl;				//1
	std::cout << std::is_lvalue_reference<decltype(arr[3])>::value << std::endl;			//1
	std::cout << std::is_lvalue_reference<decltype(*ptr)>::value << std::endl;				//1
	std::cout << std::is_lvalue_reference<decltype("lval")>::value << std::endl;			//1
	std::cout << std::is_lvalue_reference<decltype(++ii)>::value << std::endl;				//1
	std::cout << std::is_lvalue_reference<decltype(ii++)>::value << std::endl;				//0

	std::cout << std::is_rvalue_reference<decltype(RvalRe())>::value << std::endl;			//1
	std::cout << std::is_rvalue_reference<decltype(ii++)>::value << std::endl;				//0
	std::cout << std::endl;

	//��auto�����Ƶ����ܴ���cv���Ʒ����ã�decltype�ܴ��߱��ʽ��cv���Ʒ���
	//���������������ʱʹ��const����volatile���Ʒ���ʹ��decltype�����Ƶ�ʱ�����Ա����̳�const��volatile���Ʒ�
	//ģ����is_const��is_volatile�ĳ�Աvalue���鿴�����Ƿ��ǳ���������ʧ��
	const int ic = 0;
	volatile int iv;
	struct SS{ int i; };

	const SS sa = { 0 };
	volatile SS sb;
	volatile SS* ps = &sb;

	std::cout << std::is_const <decltype(ic)>::value << std::endl;		//1
	std::cout << std::is_volatile<decltype(iv)>::value << std::endl;	//1
	std::cout << std::is_const<decltype(sa)>::value << std::endl;		//1
	std::cout << std::is_volatile<decltype(sb)>::value << std::endl;	//1

	//��Ա����̳�const����volatile���Ʒ�
	std::cout << std::is_const<decltype(sa.i)>::value << std::endl;		//0
	std::cout << std::is_volatile<decltype(ps->i)>::value << std::endl;	//0

	std::cout << std::endl;
	//cv���Ʒ��Լ����÷���&������Ƶ������������Ѿ�������Щ���ԣ�����ķ��žͻᱻ����
	//ע�⣺*���Ų��ᱻ����
	int iii = 1;
	int &jjj = iii;
	int *ppp = &iii;
	const int kkk = 1;

	decltype(iii) & var15 = ii;	//var15��int&
	decltype(jjj) & var16 = ii;	//var16��int&�������&������

	std::cout << std::is_lvalue_reference<decltype(var15)>::value << std::endl;//1

	std::cout << std::is_rvalue_reference<decltype(var16)>::value << std::endl;//0
	std::cout << std::is_lvalue_reference<decltype(var16)>::value << std::endl;//1

	decltype(ppp) * var17 = &iii;	//�޷�ͨ������
	decltype(ppp) * var18 = &ppp;	//var18������Ϊint**

	auto *v3 = ppp;					//v3������Ϊint*
	v3 = &iii;
	const decltype(kkk) var19 = 1;	//�����const��������
	return 0;
}