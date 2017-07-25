#include <iostream>
#include <cstdarg>
#include <string>

//�ع˿ɱ�������䳤������
template<typename T>
T SumOfValues(int nCount, ...)
{
	T Sum = 0;
	va_list vl;
	va_start(vl, nCount);
	for (int i = 0; i < nCount; ++i)
		Sum += va_arg(vl, T);
	va_end(vl);
	return Sum;
}

//�䳤ģ����
//����Elements������ģ��������������������Խ����ģ���������ɵ�����ģ�������Elements
template<typename... Elements> 
class Tuple{};

//���������չ
//�����Ϊ��ʹ��ģ���������������Ҫ�Ƶ������ģ�����ͣ�������̾ͽ������
//����չ����ɽ���Ĺ�����Ҫһ������չ���ʽ
typedef int X;	//X����
typedef double Y;//Y����
template<typename T1, typename T2>class Base{};
template<typename... A>class Template : private Base<A...>{};
Template<X, Y> xy;
//���̣�
//Ϊ��ģ������һ��������A...����ʹ�ò�����A...������Template��˽�л���Base<A...>��
//���һ�����ʽ��������һ������ΪBase<X,Y>��ģ����Template<X,Y>�Ķ���xy
//����X,Y����ģ��������Ǵ���ɲ�����A���������ڰ���չ���ʽA...�б���ԭ


//�䳤ģ���ඨ�壺�ݹ�
//ͨ������ݹ��ģ��ƫ�ػ����壬����ʹ��ģ���������ʵ�����ܹ����չ��
//		ֱ���������еĲ����𽥺ľ����ߵ���ĳ�������ı߽�Ϊֹ��
template<typename... Elements> class tuple;//�䳤ģ������
template<typename Head, typename... Tail>//�ݹ��ƫ�ػ�����
class tuple<Head, Tail...> : private Tuple<Tail...>
{
	Head head;
};
//�߽�����
template<> class tuple<>{};

//�����Ͳ����ı䳤ģ����
template<long... nums> struct Multiply;	//�䳤ģ������
template<long first, long... nums>	//�ݹ��ƫ�ػ�����
struct Multiply<first, nums...>
{
	static const long val = first * Multiply<nums...>::val;
};
//�߽�����
template<>struct Multiply<>{ static const long val = 1; };


//�䳤ģ�庯��������Printf
void Printf(const char* s)
{
	while (*s)
	{
		if (*s == '%' && *++s != '%')
			throw "invalid format string: missing arguments";
		std::cout << *s++;
	}
}
template<typename T , typename... Args>
void Printf(const char* s, T value, Args... args)
{
	while (*s)
	{
		if (*s == '%' && *++s != '%')
		{
			std::cout << value;
			return Printf(++s, args...);
		}
		std::cout << *s++;
	}
}

int main()
{
	//�ɱ����
	int iSum = SumOfValues<int>(4, 1, 2, 3, 4);
	std::cout << iSum << std::endl;

	double fSum = SumOfValues<double>(3, 3.2, 6.3, 8.1);
	std::cout << fSum << std::endl;

	//�����Ͳ�����ģ������
	std::cout << Multiply<2, 3, 4>::val << std::endl;	//24
	std::cout << Multiply<22, 44, 66, 88>::val << std::endl;	//5622144


	//�䳤����ģ������
	//Hello world
	Printf("Hello %s\n", std::string("world"));
	//The sum of (12 + 21) is 33
	Printf("The sum of (%d + %d) is %d\n", 12, 21, 12 + 21);
	return 0;
}