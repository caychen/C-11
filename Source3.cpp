#include <iostream>
#include <algorithm>
#include <functional>

#define  _NONOTE

//1���̳й��캯��
class A
{
public:
	A(int i) {}
	A(double d) {}
	A(int i, double d){}
	void fun2(int i){ std::cout << "A:i = " << i << std::endl; }
};

class B :public A
{
public:
	//�����B��ӵ����Aȫ���Ĺ��캯���Ļ�����Ҫ����B�Ĺ��캯����һһʵ�֣���Ϊÿһ����A�Ĺ��캯��
	//Ϊ�˱�������B�Ĺ��캯����һһʵ����A�Ĺ��캯������ɵ��鷳����ʹ��using���������
	//�����Bֻ����Ҫ�Լ��Ĺ��캯�������Բ���using���Զ��幹�캯������
	using A::A;//������ͨ��ʹ��using�������̳л���Ĺ��캯�������ٴ���ռ�
	void fun(){}//�������Զ����Ա����

	//���ʣ���
	//���������B����ʵ�ֹ��캯�������������ĺ��������壬�������B b(2);�������޷�����ɹ�����B���Ǽ̳�����A�Ĺ��캯��������⣿
	B(double d) :A(d){}

	//��ֹ�ڹ��캯����ʱ��ſ���using�����ں���ͬ��ʵ��
	//�̳л����ͬ������
	//�����using A::fun2;ע�͵��Ļ�����Bֻ����һ������Ϊdouble���͵�fun2�������൱����д�˻���A��fun2����
	//����ע�͵Ļ�����B�ͺ�������fun2�����غ����������ֱ�Ϊint��double�����ݲ��������ͣ���ȷ�ĵ��ö�Ӧ��fun2����
#ifdef _NONOTE	
	using A::fun2;
#endif

	void fun2(double d){ std::cout << "B:d = " << d << std::endl; }
};


//2��ί�ɹ��캯��
class Info
{
public:
	//Ĭ��ԭ���캯��
	//Info() :type(1), c('a'){ InitRest(); }
	//Info(int i) :type(i), c('a'){ InitRest(); }
	//Info(char e) :type(1), c(e){ InitRest(); }

	//ʹ��ί�ɹ��캯��
	Info(){ InitRest(); }				//Ŀ�깹�캯��
	Info(int i) :Info(){ type = i; }	//ί�ɹ��캯��
	Info(char e) :Info(){ c = e; }		//ί�ɹ��캯��

	//ע��㣺
	//ί�ɹ��캯�������г�ʼ���б����Թ��캯���в���ͬʱ��ί�ɡ���ʹ�ó�ʼ���б�
	//���ί�ɹ��캯��Ҫ����������ֵ����ʼ�����������ں�������
	Info(int i, bool bl) : Info(), b(bl){}	//error
	Info(bool bl, int i) :Info(i){ b = bl; }//ok

private:
	void InitRest(){}
	int type{ 0 };
	char c{ 'A' };
	bool b;
};

//���飺
//��ʹ��ί�ɹ��캯����ʱ�򣬽���������Ϊ��ͨ�á�����Ϊ��ΪĿ�깹�캯��
//����Ruler������ֱ����ͨ�õ�Ruler(int i, char c);��ΪĿ�깹�캯�������������Ϊί�ɹ��캯��
class Ruler
{
public:
	Ruler() :Ruler(0, 'a'){}
	Ruler(int i) :Ruler(i, 'a'){}
	Ruler(char c) :Ruler(0, c){}

private:
	Ruler(int i, char c) :type(i), chr(c){}
	int type;
	char chr;
};

//��ί�ɹ��캯����ʹ��try��������Ŀ�깹�캯���в����쳣����ί�ɹ��캯�������б����񵽡�
class DCExcept
{
public:
	DCExcept(double d)
		try  DCExcept(1, d)
	{
			std::cerr << "Run Success" << std::endl;
	}
	catch (...)
	{
		std::cerr << "caught exception" << std::endl;
	}
private:
	DCExcept(int i, double d)
	{
		std::cout << "going to DCExcept(int ,double)" << std::endl;
		std::cout << "goint to throw" << std::endl;
		throw 0;
	}
private:
	int i;
	double d;
};

int main()
{
	A a(3);
	B b(2.0);

	//һ��ʹ���˼̳й��캯�����������Ͳ���Ϊ����������Ĭ�ϵĹ��캯��
	B b1;	//error

	//ͨ���궨��_NONOTE����Ϊusing A::fun2;�Ŀ���
	//�ڲ�ע��using A::fun2;������£��ֱ���A:i = 3��B:d = 3.5
	//��ע��using A::fun2;������£��ֱ���B:d = 3��B:d = 3.5
	b.fun2(3);						  	  
	b.fun2(3.5);	

	return 0;
}
