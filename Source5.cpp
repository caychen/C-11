#include <iostream>
#include <vector>
#include <map>

//1����ʾת��������explicit
struct Rational1
{
	//û��explicit���εĹ��캯��������ʽ���ã����Խ�ĳ��������ʽת��Ϊ������
	Rational1(int n = 0, int d = 1):num(n), den(d)
	{
		std::cout << "Rational(" << n << "/" << d << ")" << std::endl;
	}
	int num;		//������
	int den;		//����
};

struct Rational2
{
	//��ʹ��explicit���εĹ��캯�����ֹ��ʽ���ã���ֹ��ĳ��������ʽת��Ϊ������
	explicit Rational2(int n = 0, int d = 1) :num(n), den(d)
	{
		std::cout << "Rationa2(" << n << "/" << d << ")" << std::endl;
	}
	int num;		//������
	int den;		//����
};

void Display1(Rational1 r)
{
	std::cout << "Numerator: " << r.num << ",Denominator: " << r.den << std::endl;
}
void Display2(Rational2 r)
{
	std::cout << "Numerator: " << r.num << ",Denominator: " << r.den << std::endl;
}

//C++11��׼�У���explicit��ʹ�÷�Χ��չ�����Զ��������ת���������ϣ���֧����ν�ġ���ʽ����ת����
class ConvertTo{};
class Convertable
{
public:
	//������һ����ʽת����ConvertTo���͵�����ת����
	explicit operator ConvertTo () const{ return ConvertTo(); }
};
void Func(ConvertTo ct){}

void ExplicitTest()
{
	Convertable c;
	ConvertTo ct(c);
	//ConvertTo ct2 = c;		//���������ʼ��������ʧ��
	ConvertTo ct3 = static_cast<ConvertTo>(c);//ǿ��ת����ok
	//Func(c);				//���������ʼ��������ʧ��
}

//2���б��ʼ��
//ͨ��initializer_list��ʵ���б��ʼ��
#include <initializer_list>
#include <vector>
#include <algorithm>	//for  for_each()

enum Gender{ male, female };
class Person
{
public:
	Person(std::initializer_list<std::pair<Gender, std::string>> ls)
	{
		auto lse = ls.begin();
		/*for (; lse != ls.end(); ++lse)
			pl.push_back(*lse);*/
		std::for_each(ls.begin(), ls.end(), [&](std::pair<Gender, std::string> pe){pl.push_back(pe); });
	}

	std::vector<std::pair<Gender, std::string>> pl;
};


void Fun(std::initializer_list<int> ls){}


class Mydata
{
public:
	Mydata& operator[](std::initializer_list<int> ls)
	{
		std::for_each(ls.begin(), ls.end(), [&](const int e){idx.push_back(e); });
		/*for (auto i = ls.begin(); i != ls.end(); ++i)
			idx.push_back(*i);*/
		return *this;
	}
	Mydata&	operator=(int v)
	{
		if (idx.empty() != true)
		{
			for (auto i = idx.begin(); i != idx.end(); ++i)
			{
				id.resize((*i > id.size() ? *i : id.size()));
				id[*i - 1] = v;
			}
			idx.clear();
		}
		return *this;
	}

	void Print()
	{
		std::for_each(id.begin(), id.end(), [](const int i) {std::cout << i << " "; });
		std::cout << std::endl;
	}
public:
	std::vector<int> idx;
	std::vector<int> id;
};

int main()
{
	Rational1 r1_1 = 11;		//Rational1(11/1)
	Rational1 r1_2(12);			//Rational1(12/1)

	//Rational2 r2_1 = 12;		//�޷�ͨ������
	Rational2 r2_2(5);			//Rational2(5/1)

	Display1(1);				//Rational1(1/1)
	//Display2(2);				//�޷�ͨ������
	Display2(Rational2(3));		//Rational2(3/1)


	//�б��ʼ��,�ڣ���֮���=�ţ����벻��Ч����ͬ
	int a[]{1, 2, 4};	//	int a[] = {1,2,4};
	std::vector<int> v{ 1, 2, 3 };
	std::map<int, float> m = { { 1, 1.0f }, { 2, 2.0f } };
	int c = { 3 + 4 };	//int c{3 + 4};		7

	//ͨ��initializer_listʵ���б��ʼ��
	//����1
	Person p = { { male, "Tom" }, { female, "Kitty" } };

	//����2
	Fun({ 1, 2 });		//�б�Ԫ�أ�1��2��
	Fun({});			//���б�

	//����3
	Mydata d;
	d[{2, 3, 5}] = 7;
	d[{1, 4, 6, 9}] = 4;
	d.Print();

	return 0;
}