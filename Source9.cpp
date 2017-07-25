#include <iostream>

namespace T	//�����ռ�T
{
	enum Color{ Black, Gray, Green };
}

namespace S
{
	enum Size{ Small = 1, Middle, Large };
}

namespace //���������ռ䣨ȫ�֣�
{
	enum Color{Black,Blue,Gray};
}

//ö���ࣺǿ����ö��
int main()
{
	//��enum��ȱ�㣺
	//1��enum��Ա�ں�����ȫ�ֿɼ�����������ڶ��оͻᱨ����ʾ�ظ�����
	enum Type1{ Purple, Red, White };
	//enum Color{Purple,Gray,Green};//Purple redefinition

	//����namespace,class/struct��union����δͨ��"����::��Ա��"�ķ�ʽ���ʣ���Ϊǿ����������
	//��enum��Ϊ��ǿ����������
	//����δʹ�����֣���ֱ��ʹ��enum�ĳ�Ա���ģ�Ĭ�Ͻ���ȫ�������ռ�
	T::Color c = T::Green;
	if (c == Black)	//Black�����������ռ��Black����cΪ�����ռ�T�ڵ�Green���������ڲ�ͬ�����ռ�
		std::cout << "..." << std::endl;
	
	//2��enum������ʽת��Ϊ���ͣ����²�ͬ���͵�ֵ�����໥�Ƚ�
	c = T::Gray;
	S::Size s = S::Small;
	if (c == s)
		std::cout << "match" << std::endl;//match

	//ǿö������ enum class/struct
	//�ŵ㣺
	//1��ǿ������ǿö�����ͳ�Ա�����Ʋ��ᱻ������丸������ռ�
	//2��ת�����ƣ�ǿö�����ͳ�Ա��ֵ��������������ʽ���໥ת��������ʹ����ʽ��ǿ��ת��
	//3������ָ���ײ����ͣ�ǿö������Ĭ�ϵײ�����Ϊint����Ҳ������ʽ��ָ���ײ�����
	//		�磺enum class Type : char{};
	//		��ָ����Type�ǻ���char���͵�ö������

	enum class Type{ General, Light, Medium, Heavy };
	enum class Color{ Black = 1, Red, Blue, Green };
	//enum class Color�е�Red��enum Type1�е�Red����ͻ������ǿö��������ǿ��������ص㣬ǿö�����͵����ֲ��ᱻ���������������

	Type1 tt = Red;//ok����ö�����͵ĳ�Աǰ���Բ�ʹ��������ö�����͵�����
	Color cl = Red;//error��ǿö�����͵ĳ�Աǰ����ʹ��������ö�����͵�����

	Type t = Type::Light;
	Color clr = Color::Black;
	t = clr;			//���Ͳ�ƥ�䣬����ʧ��
	if (t == clr)		//���Ͳ�ƥ�䣬����ʧ��
		std::cout << "111" << std::endl;
	if (Type::Heavy > t)//����ͨ��
		std::cout << "222" << std::endl;	//222

	if (t > 0)			//��������ʽת��Ϊint���ͣ�����ʧ��
		std::cout << "333" << std::endl;
	if ((int)t > 0)		//����ͨ��
		std::cout << "444" << std::endl;	//444

	std::cout << std::is_pod<Type>::value << std::endl;		//1
	std::cout << std::is_pod<Color>::value << std::endl;	//1

	enum class C : char{ C1 = 1, C2 };
	enum class D : unsigned{ D1 = 1, D2, Dbig = 0xFFFFFFFF0U };

	std::cout << sizeof(C::C1) << std::endl;	//1
	std::cout << (unsigned)D::Dbig << std::endl;//4294967280
	std::cout << sizeof(D::D1) << std::endl;	//4
	std::cout << sizeof(D::Dbig) << std::endl;	//4

	//C++11��ԭ�е�enumö�����ͽ�����չ����ָ���ײ�����
	enum Type2 : char{ CC1 = 1, CC2 };
	return 0;
}