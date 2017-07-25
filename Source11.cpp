#include <iostream>
#include <iterator> //for ostream_iterator

//�������ʽ
//1������ʱ�����������ʱ�����Լ�const��constexpr
const int GetConst(){ return 1; }	//����ʱ����
constexpr int GetConstexpr(){ return 1; }	//����ʱ����

//constexpt���ʽ������Ҫ��
//1��������ֻ�õ�һ��return�������
//2�����������з���ֵ��������void����
//3����ʹ��ǰ�������ж���
//4��return���������ʽ�в���ʹ�÷ǳ������ʽ�ĺ�����ȫ�����ݣ��ұ�����һ���������ʽ

//Ҫ��3��
constexpr int f();	//constexpr���ʽ��������
int a = f();
const int b = f();
constexpr int c = f();	//error����ʹ��ǰ�����ж���
constexpr int f(){ return 1; }	//constexpr���ʽ��������
constexpr int e = f();	//ok��ʹ��ǰ�Ѷ���

//Ҫ��4��
constexpr int g(){ return GetConst(); } //error���޷���return���������ʹ�÷ǳ������ʽ�ĺ���
constexpr int h(){ return GetConstexpr(); } //ok��return�������һ���������ʽ

int p = 3;
constexpr int m(){ return p; }	//error���������ʽ�������޷�����ȫ������


//�������ʽֵ��ʹ��constexpr���εı�����Ϊ�������ʽֵ��
//�������ʽֵ���뱻һ���������ʽ��ֵ����ʹ��ǰ���뱻��ʼ��
constexpr int aa = 1;
constexpr int bb = aa;//ok

//�����Զ�����������ͣ�Ҫ���Ϊ�������ʽֵ��ʱ����Ҫ�Զ��峣�����캯����ֻ���ڹ��캯��ǰ����constexpr�ؼ���
//Ҫ��Լ����
//1�����������Ϊ��
//2���г�Ա����������Ҫ��ʼ��
//3����ʼ���б�ֻ���ɳ������ʽ����ֵ
class ConstexprClass
{
public:
	constexpr ConstexprClass(int x) :i(x){}
	int i;
};

class Date
{
public:
	constexpr Date(int y, int m, int d) :year(y), month(m), day(d){}
	constexpr int GetYear(){ return year; }
	constexpr int GetMonth(){ return month; }
	constexpr int GetDay(){ return day; }

private:
	int year;
	int month;
	int day;
};

//�������ʽ��������ģ�溯��
//������Ϊ�������ʽ��ģ�溯�������ĳ����ģ�溯����ʵ������������㳣�����ʽ����Ļ���constexpr���Զ�����
struct NotLiteral
{
	NotLiteral(){ i = 5; }
	int i;
};

struct Literal
{
	constexpr Literal(){}
};

template<typename T>
constexpr T ConstExprFun(T t)
{
	return t;
}

//constexpr�ݹ�����
constexpr int Fib(int n)
{
	return (n == 1 || n == 2 ? 1 : (Fib(n - 1) + Fib(n - 2)));
}
//ģ��Ԫ
template<long num = 10>
struct Fibo
{
	static const long result = Fibo<num - 1>::result + Fibo<num - 2>::result;
};
template<>
struct Fibo<0>{ static const long result = 0; };
template<>
struct Fibo<1>{ static const long result = 1; };
template<>
struct Fibo<2>{ static const long result = 1; };


int main()
{
	int arr[GetConst()] = { 0 };//�޷�ʹ������ʱ��������ʼ������
	enum{ e1 = GetConst(), e2 };//Ҳ�޷�ʹ������ʱ������Ϊö��ֵ

	int arr2[GetConstexpr()] = { 0 };//ok

	constexpr ConstexprClass mc(0); //����ʹ�ó������ʽ��ֵ
	//constexpr ConstexprClass mc = { 0 };�ȼ���һ��
	//constexpr ConstexprClass mc{ 0 }; �ȼ���һ��

	//gcc-5.1����"error: passing 'const Date' as 'this' argument discards qualifiers [-fpermissive]"
	constexpr Date d(1990, 11, 28);
	constexpr int year = d.GetYear();
	constexpr int month = d.GetMonth();
	constexpr int day = d.GetDay();
	std::cout << "year:" << year << std::endl
		<< "month" << month << std::endl
		<< "day" << day << std::endl;


	//�ṹ��NotLiteral���Ƕ����˳������ʽ���캯�������ͣ���˲��ܹ�����Ϊ�������ʽֵ
	//��ģ�溯��һ����NotLiteral��Ϊ��������ô��constexpr�ؼ��־ͻᱻ����
	NotLiteral nl;
	NotLiteral nl1 = ConstExprFun(nl);
	constexpr NotLiteral nl2 = ConstExprFun(nl);//����ʧ��
	constexpr int a = ConstExprFun(1);

	constexpr Literal l1;
	Literal l2 = ConstExprFun(l1);//ok
	constexpr Literal l3 = ConstExprFun(l1);//ok

	//constexpr�����ݹ�
	int fibs[] = { Fib(11), Fib(12), Fib(13), Fib(14), Fib(15) };
	std::copy(std::begin(fibs), std::end(fibs),
		std::ostream_iterator<int>(std::cout, " "));//89 144 233 377 610 
	
	std::cout << std::endl;
	//ʹ��ģ��Ԫʵ�ֵݹ���
	int fibs2[] = { Fibo<11>::result, Fibo<12>::result, Fibo<13>::result, Fibo<14>::result, Fibo<15>::result };
	std::copy(std::begin(fibs2), std::end(fibs2),
		std::ostream_iterator<int>(std::cout, " "));//89 144 233 377 610 

	return 0;
}