#include <iostream>

//����֧��
//C++11��׼����alignof���鿴���ݵĶ��뷽ʽ
//Microsoft����Ϊ__alignof���鿴���ݵĶ��뷽ʽ
struct EmptyStruct{};
class EmptyClass{};
class EmptyClass1;

struct HowManyBytes
{
	char a;
	int b;
};

struct ColorVector1
{
	double r;
	double g;
	double b;
	double a;
};

//C++11��׼�ṩ���η�alignas�趨struct/class/union�Ķ��뷽ʽ
//Microsoftʹ��_declspec(align(#))���趨struct/class/union���뷽ʽ
struct _declspec(align(32)) ColorVector2//ֱ�ӽ�ColorVector�趨��32�ֽڵĵ�ַ�߽��ϣ�����ʼ��ַ������32�ı���
	//�ȼ�_declspec(align(32)) struct ColorVector
{
	double r;
	double g;
	double b;
	double a;
};

int main()
{
	std::cout << "sizeof(EmptyStruct): " << sizeof(EmptyStruct) << std::endl;//1
	std::cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) << std::endl;//1
	std::cout << "__alignof(EmptyClass): " << __alignof(EmptyClass) << std::endl;//1

	//error,���Ͳ�����������ʧ��
	//std::cout << "__alignof(EmptyClass1): " << __alignof(EmptyClass1) << std::endl;//1

	std::cout << "sizeof(char): " << sizeof(char) << std::endl;//1
	std::cout << "sizeof(int): " << sizeof(int) << std::endl;//4
	std::cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << std::endl;//8

	std::cout << "offset of char a: " << offsetof(HowManyBytes, a) << std::endl;//0
	std::cout << "offset of int b: " << offsetof(HowManyBytes, b) << std::endl;//4

	std::cout << "__alignof(HowManyBytes): " << __alignof(HowManyBytes) << std::endl;//4
	std::cout << "__alignof(ColorVector1): " << __alignof(ColorVector1) << std::endl;//8
	std::cout << "__alignof(ColorVector2): " << __alignof(ColorVector2) << std::endl;//32
	std::cout << "sizeof(ColorVector2): " << sizeof(ColorVector2) << std::endl;//32

	std::cout << "in ColorVector1 offset of double r: " << offsetof(ColorVector1, r) << std::endl;//0
	std::cout << "in ColorVector1 offset of double g: " << offsetof(ColorVector1, g) << std::endl;//8
	std::cout << "in ColorVector1 offset of double b: " << offsetof(ColorVector1, b) << std::endl;//16
	std::cout << "in ColorVector1 offset of double a: " << offsetof(ColorVector1, a) << std::endl;//24

	std::cout << std::endl;
	std::cout << "in ColorVector2 offset of double r: " << offsetof(ColorVector2, r) << std::endl;//0
	std::cout << "in ColorVector2 offset of double g: " << offsetof(ColorVector2, g) << std::endl;//8
	std::cout << "in ColorVector2 offset of double b: " << offsetof(ColorVector2, b) << std::endl;//16
	std::cout << "in ColorVector2 offset of double a: " << offsetof(ColorVector2, a) << std::endl;//24

	int a;
	long long b;
	auto &c = b;
	char d[1024] = { 0 };
	//����������
	std::cout << __alignof(int) << std::endl;//4

	//�Ա��������û�������
	std::cout << __alignof(a) << std::endl//4
		<< __alignof(b) << std::endl//8
		<< __alignof(c) << std::endl//8		�����������õ����ݶ���ֵ��ͬ
		<< __alignof(d) << std::endl;//1	����Ķ���ֵ����Ԫ�ؾ���

	return 0;
}