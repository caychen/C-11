#include <iostream>

struct init
{
	int a = 1;
	//1�����ٳ�ʼ����Ա����
	//�ڳ�Ա���ٳ�ʼ���׶�ʱ������ʹ�ã�������ʼ����
	//���ڷǾ�̬��Ա����ֻ��ʹ��=���ߣ��������п��ٳ�ʼ��
	std::string s{ "sss" };	//std::string s("aaa");---->error
	double d{ 3.0 };		//double d(3.0);---->error
};

class Mem
{
public :
	Mem(int i) :m(i){}
private:
	int m{0};
};

class Group
{
public :
	Group() = default;
	Group(int a) : data(a){}
	Group(Mem m) : mem(m){}
	Group(int a, Mem m, std::string s) :data(a), mem(m), name(s){}

private:
	int data = 1;
	Mem mem{ 0 };
	std::string name{ "123" };
};

class Person
{
public:
	int hand = 0;
	static Person* all;
	static int b;
};
Person* Person::all = nullptr;
int Person::b; //Ĭ��Ϊ0

//2��final������������ߺ������������ε����򲻾��м̳��ԣ��������εĺ������޷�����
class Base
{
	virtual void fun() = 0;
	virtual void fun3() = 0;
};

class Derived1 : public Base
{
	void fun() final{}
	virtual void fun2() = 0;

	//3��override��������
	//3-1�����������麯������ʱʹ��override,��ú����������ػ����е�ͬ�������������������ͣ������б�����˳�����Ҫһ��
	//����������
	//3-2���Է��麯����������Ҳ�����
	//void fun4() override {}	---->error
};

class Derived2 final: public Derived1
{
	//2-1
	//void fun(){}	//error ��Derived2�Ļ���Derived1��fun��������final���Σ�������������˵���޷�����
	void fun2() override{}
};

//2-2
//����Derived2����final���Σ���Derived2�಻�ɼ̳�,����������
//class Derived3 : public Derived2
//{

//};

//4��ģ�溯����Ĭ��ģ�����,
//4-1�����򣺣�1��������ģ�棺���ж��Ĭ��ģ���������Ϊָ��Ĭ��ֵʱ�����ա��������󡱵Ĺ���ָ��
//			 ��2�����ں���ģ����˵����Ҫ�����Ը��ݺ������������Ƶ�ģ������
template<typename T = int>
class DefClass{};

template<typename T = int>
void DefFunc(){}

//error ,��ģ��Ĭ�ϲ���δ���մ�������Ĺ���
template<typename T1 = int ,typename T2> class DefClass2{};
//ok
template<typename T1, typename T2 = int> class DefClass3{};

//ok
template<typename T1 = int, typename T2> void DefFunc2();
//ok
template<typename T1, typename T2 = int> void DefFunc3();


int main()
{
	Person p;
	std::cout << sizeof(p.hand) << std::endl;
	std::cout << sizeof(Person::all) << std::endl;
	std::cout << sizeof(((Person*)0)->hand) << std::endl;
	std::cout << sizeof(p.all) << std::endl;
	std::cout << p.b << std::endl;
	return 0;
}