#include <iostream>

//Ĭ�Ϻ�������
/*
	���캯��
	�������캯��
	������ֵ����
	�ƶ����캯��
	�ƶ���������
	��������
	=============
	operator ,
	operator &
	operator &&
	operator *
	operator ->
	operator ->*
	operator new
	operator delete
*/

class TwoCstor
{
public:
	TwoCstor() = default;

	//1����ֹʹ�ÿ������캯����һ��ȱʡ�汾��ɾ�������ظú���Ҳ�ǷǷ���
	TwoCstor(const TwoCstor& t) = delete;

	//�˴�δʹ��"=default"
	TwoCstor& operator=(const TwoCstor& t);
};
//������ʹ��"=default"��ָ��ʹ��ȱʡ�汾
TwoCstor& TwoCstor::operator=(const TwoCstor& t) = default;

class ConvertTo
{
public:
	ConvertTo(int){}
	//2��ɾ������Ϊchar�İ汾
	ConvertTo(char) = delete;
};

class ConvType
{
public:
	ConvType(int){}
	explicit ConvType(char) = delete;
};

//3����ʽɾ����ʽ��������ת��
void func1(ConvertTo c){}
void func2(ConvType c){}

//4����ʽɾ����ͨ�ĺ���
void func3(int){}
void func3(char) = delete;

//5����ʽɾ���ڶ��Ϸ���class����
class NoHeapAlloc
{
public:
	void* operator new(std::size_t) = delete;
};

int main()
{
	//���TwoCstor() = default;�ĳ�TwoCstor(){},��is_trivial��is_pod��Ϊ0
	std::cout << std::is_trivial<TwoCstor>::value << std::endl;	//1
	std::cout << std::is_standard_layout<TwoCstor>::value << std::endl;	//1
	std::cout << std::is_pod<TwoCstor>::value << std::endl;	//1

	//1��
	TwoCstor t1;		//ok
	TwoCstor t2(t1);	//error����ֹʹ�ÿ������캯��

	//2��
	ConvertTo c1(1);	//ok
	ConvertTo c2('a');	//error������Ϊchar���͵Ĺ��캯����ɾ��
	func1(1);	//ok
	func1('a');	//error���޷���ʽ����ת��

	//3��������explicit�ؼ�������ʽɾ�����ã���������ͬʱʹ��
	ConvType cc1(1);
	ConvType cc2('a');	//error������Ϊchar���͵İ汾��ɾ�����޷�����
	func2(1);
	func2('a');	//������ʽת��Ϊfunc(ConvType(97));

	//4��
	func3(1);	//ok
	func3('a');	//error��һ�㺯������Ϊchar���͵ı�ɾ��

	//5��
	NoHeapAlloc nha;	//ok
	NoHeapAlloc *pNha = new NoHeapAlloc();	//error����ֹʹ�ò�����new

	return 0;
}