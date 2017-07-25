#include <iostream>

/**********************************************************/
//���������Ƿ���ƽ����
struct Trivial1{};
struct Trivial2
{ 
	int a, b; 
};

struct Trivial3
{ 
	Trivial1 t1; 
	Trivial2 t2; 
	Trivial2 ta[2]; 
};

struct Trivial4
{ 
	int x; 
	static int y; 
};

struct Trivial5
{
	Trivial5() = default;
};

struct NoTrivial1
{ 
	NoTrivial1() :z(4){} 
	int z;
};

struct NoTrivial2
{
	NoTrivial2();
	int w;
};
NoTrivial2::NoTrivial2() = default;

struct NoTrivial3
{
	virtual void f();
};

/**********************************************************/
//���������Ƿ��Ǳ�׼���ֵ�
struct SLayout1{};
struct SLayout2
{
private:
	int x;
	int y;
};

struct SLayout3 : SLayout1
{
	int x;
	int y;
	void f();
};

struct SLayout4 : SLayout1
{
	int x;
	SLayout1 y;
};

struct SLayout5 { static int y; };

struct SLayout6 : SLayout5{ int x; };

struct NoSLayout1 : SLayout1	//������(3)���е�һ���Ǿ�̬��Ա������������಻ͬ
{
	SLayout1 x;
	int i;
};

struct NoSLayout2 : SLayout2{ int z; };	//������(2)

struct NoSLayout3 : NoSLayout2{};

struct NoSLayout4	//������(1)
{
public:
	int x;
private: 
	int y;
};

/**********************************************************/
//���������Ƿ���POD��
union U{};
union U1{ U1(){} };
enum E{};
typedef double*	DA;
typedef void(*PF)(int, double);

/**********************************************************/
int main()
{
	//POD ���ͣ�Plain Old Data
	//ƽ����(trivial)�ͱ�׼���ֵ�(standard layout)

	//(1)ƽ����
	//1��ӵ��ƽ����Ĭ�Ϲ��캯����������������C++11�п���ʹ��=default�ؼ�����ʽ����ȱʡ�Ĺ��캯�����Ӷ��ָ���ƽ������
	//	ע�⣺Trivial5��NoTrivial2��default����
	//2��ӵ��ƽ���Ŀ������캯�����ƶ����캯��
	//3��ӵ��ƽ���Ŀ�����ֵ�������ƶ���ֵ����
	//4�����ܰ����麯���Լ������

	//template<typename T> struct std::is_trivial;
	//ͨ����ģ��is_trivial��valueֵ���ж�T�����Ƿ��Ǹ�ƽ��������
	std::cout << std::is_trivial<Trivial1>::value << std::endl;		//1
	std::cout << std::is_trivial<Trivial2>::value << std::endl;		//1
	std::cout << std::is_trivial<Trivial3>::value << std::endl;		//1
	std::cout << std::is_trivial<Trivial4>::value << std::endl;		//1
	std::cout << std::is_trivial<Trivial5>::value << std::endl;		//1
	std::cout << std::is_trivial<NoTrivial1>::value << std::endl;	//0
	std::cout << std::is_trivial<NoTrivial2>::value << std::endl;	//0
	std::cout << std::is_trivial<NoTrivial3>::value << std::endl;	//0

	std::cout << std::endl;
	//(2)��׼���ֵ�
	//1�����зǾ�̬��Ա����ͬ�ķ���Ȩ��
	//2�������ṹ��̳�ʱ��������������������֮һ��
	//		1)���������зǾ�̬��Ա����ֻ��һ����������̬��Ա�Ļ���
	//		2)�����зǾ�̬��Ա����������û�зǾ�̬��Ա
	//3�����е�һ���Ǿ�̬��Ա������������಻ͬ
	//4��û���麯���������
	//5�����зǾ�̬��Ա�����ϱ�׼�������ͣ������Ҳ���ϱ�׼���֡�

	//template<typename T> struct std::is_standard_layout;
	//ͨ����ģ��is_trivial��valueֵ���ж�T�����Ƿ��Ǹ���׼���ֵ�����
	std::cout << std::is_standard_layout<SLayout1>::value << std::endl;		//1
	std::cout << std::is_standard_layout<SLayout2>::value << std::endl;		//1
	std::cout << std::is_standard_layout<SLayout3>::value << std::endl;		//1
	std::cout << std::is_standard_layout<SLayout4>::value << std::endl;		//1
	std::cout << std::is_standard_layout<SLayout5>::value << std::endl;		//1
	std::cout << std::is_standard_layout<SLayout6>::value << std::endl;		//1
	std::cout << std::is_standard_layout<NoSLayout1>::value << std::endl;	//0
	std::cout << std::is_standard_layout<NoSLayout2>::value << std::endl;	//0
	std::cout << std::is_standard_layout<NoSLayout3>::value << std::endl;	//0
	std::cout << std::is_standard_layout<NoSLayout4>::value << std::endl;	//0

	std::cout << std::endl;
	//POD����:�ܶ����õ����Ͷ���POD��
	//template<typename T> struct std::is_pod;
	std::cout << std::is_pod<U>::value << std::endl;	//1
	std::cout << std::is_pod<U1>::value << std::endl;	//0
	std::cout << std::is_pod<E>::value << std::endl;	//1
	std::cout << std::is_pod<int>::value << std::endl;	//1
	std::cout << std::is_pod<DA>::value << std::endl;	//1
	std::cout << std::is_pod<PF>::value << std::endl;	//1

	return 0;
}