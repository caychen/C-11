#include <iostream>
#include <string>
#include <assert.h>

//2��_Pragma(�ַ���������)
//_Pragma("once") ===== #pragma  once
//

//3���䳤�����궨�弰__VA_ARGS__   
//��ʡ�Ժ���Ϊ�����б�����һ������
#define LOG(...) {\
	fprintf_s(stderr, "%s: Line %d:\t", __FILE__, __LINE__);\
	fprintf_s(stderr, __VA_ARGS__);\
	fprintf_s(stderr, "\n");\
}

template<typename T, typename U>
void bit_copy(T &a, U& b)
{
	//4��static_assert:��̬���ԣ��ڱ����ʱ��ͽ��ж���
	//static_assert(sizeof a == sizeof b, "Two type Must have same width");		compile error
	memcpy_s(&a, sizeof a, &b, sizeof b);
}

//4��ע��㣺����static_assert���ڱ����ڼ���ж��ԣ���static_assert�ĵ�һ�����������Ǹ��������ʽ��
//	���ʹ�ñ�������ᵼ�³���
void positive(const int n)
{
	//ʹ�ñ����Ķ��ԣ�����ʹ��assert
	//static_assert(n > 0, "value must > 0");		error
	assert(n > 0);
}

//5��noexcept ���������throw()
//ֱ���ں������������noexcept�ؼ��ֻ��߽���һ���������ʽ��Ϊ����������ת��Ϊbool����
//��ֵΪtrue�����ʾ�������׳��쳣����֮���׳��쳣
//�����������ʽ��noexcept�൱��noexcept(true),�����׳��쳣
//vs����֧��noexcept
void Throw(){ throw 1; }
void NoBlockThrow(){ Throw(); }
void BlockThrow() throw(){ Throw(); }

int main()
{
	//1��__fun__:���غ�������C++11��--->VS2015
	//std::cout << __func__ << std::endl;
	std::cout << __LINE__ << std::endl;//�к�
	std::cout << __FILE__ << std::endl;//�ļ���

	LOG("x = %d", __LINE__);

	int a = 3;
	double b = 4.0;
	bit_copy(a, b);

	try//Throw()
	{
		Throw();
	}
	catch (...)
	{
		std::cerr << "Throw() error" << std::endl;
	}

	try//NoBlockThrow()
	{
		NoBlockThrow();
	}
	catch (...)
	{
		std::cerr << "NoBlockThrow() error" << std::endl;
	}

	try//BlockThrow()
	{
		BlockThrow();
	}
	catch (...)
	{
		std::cerr << "BlockThrow() error" << std::endl;
	}

	return 0;
}