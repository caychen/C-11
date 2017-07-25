#include <iostream>
#include <vector>
#include <algorithm>	//for_each...
#include <functional>	//plus<int>()...
#include <numeric>	//accumulate...

//lambda����
/*
	lambda�����﷨���壺
		[capture](parameters) mutable -> return-type{statement}
	1��[capture]����׽�б�
	2��(parameters)�������б�����ͨ���������б�һ�£��������Ҫ�����б��ݣ�����ͬ()һ��ʡ��
	3��mutable��mutable���η���Ĭ������£�lambda��������һ��const���ʽ��mutable����ȡ���䳣���ԣ�
		��ʹ�ø����η�ʱ�������б���ʡ�ԣ���ʹ����Ϊ��
	4��->return_type���������ͣ���׷�ٷ���������ʽ���������ķ������͡�������Ҫ����ֵ��ʱ�򣬿�����ͬ����->һ��ʡ��
		���⣬�ڷ���������ȷ������£�Ҳ����ʡ�Ըò��֣��ñ������Է������ͽ����Ƶ�
	5��{statement}�������壬����ͨ������һ��������ʹ�ò���֮�⣬������ʹ�����в���ı���


	��׽�б�ļ���ʽ��
	[var]����ʾֵ���ݷ�ʽ��׽����var
	[=]����ʾֵ���ݷ�ʽ��׽���и�������ı���������this
	[&var]����ʾ���ô��ݲ�׽����var
	[&]����ʾ���ô��ݲ�׽���и�������ı���������this
	[this]����ʾֵ���ݷ�ʽ��׽��ǰ��thisָ��

	���ӵ������ʽ��ע�ⲻ�����ظ���׽����
	[=,&var1,&var2]����ʾ�����ô��ݵķ�ʽ��׽����var1��var2��ֵ���ݵķ�ʽ��׽�������б���
	[&,var1,this]����ʾ��ֵ���ݵķ�ʽ����׽����var1��this�����ô��ݷ�ʽ��׽�������б���

	//error
	[=,var1]:�����=�Ѿ���ֵ���ݷ�ʽ��׽�����еı������ٲ�׽var1�����ظ�
	[&,&var1]:�����&�Ѿ������ô��ݲ�׽�����еı������ٲ�׽var1�����ظ�
*/

//�º���
class _functor
{
public:
	_functor() = default;
	int operator()(int a, int b)
	{
		return (a + b);
	}
};

int CommonFun(int times)
{
	//�ڳ�������ʱ��Ҫ�޸�x��ֵ�����Բ�������Ϊconst
	int x = 0;
	try
	{
		for (int i = 0; i < times; ++i)
			x += i;
	}
	catch (...)
	{
		x = 0;
	}
	return x;
}

int LambdaFun(int times)
{
	//��lambda�����У�ֻ��ʹ���亯������ֵ�����Կ�������Ϊconst����֤������
	const int y = [=]
	{
		int val = 0;
		try
		{
			for (int i = 0; i < times; ++i)
				val += i;
		}
		catch (...)
		{
			val = 0;
		}
		return val;
	}();
	return y;
}

void OneCond(int val)
{
	//��ͳforѭ�������Ƿ���valֵ
	for (auto i = nums.begin(); i != nums.end(); ++i)
	{
		if (*i == val)
			break;
	}

	//���÷º���equal_to
	std::find_if(nums.begin(), nums.end(), std::bind2nd(std::equal_to<int>(), val));

	//ʹ��lambda����
	std::find_if(nums.begin(), nums.end(), [=](const int& i)
	{
		return i == val;
	});
}

void Add(const int val)
{
	auto print = [&]
	{
		for (auto n : nums)
			std::cout << n << "\t";
		std::cout << std::endl;
	};

	//��ͳforѭ��
	for (auto i = nums.begin(); i != nums.end(); ++i)
	{
		*i += val;
	}
	print();

	//for_each�Լ����÷º������˴���plus<int>()ֻ�ǽ��ӷ�������أ��������ٴ�Ӧ�õ�vector��nums��
	std::for_each(nums.begin(), nums.end(), std::bind2nd(std::plus<int>(), val));
	print();

	//�������ĸĽ������ӷ�����ٴδ��͵�vector��nums��
	std::transform(nums.begin(), nums.end(), nums.begin(), std::bind2nd(std::plus<int>(), val));
	print();

	//lambda������for_each
	std::for_each(nums.begin(), nums.end(), [=](int &i)
	{
		i += val;
	});
	print();
}

std::vector<int> nums = { 1, 2, 9, 10, 21, 45, 37, 81 };
std::vector<int> LargeNums;
const int ubound = 10;
inline void LargeNumsFun(int i)
{
	if (i > ubound)
		LargeNums.push_back(i);
}

class LargeNumsClass
{
public:
	LargeNumsClass(int b) :bound(b){}
	void operator()(int val) const
	{
		if (val > bound)
			LargeNums.push_back(val);
	}
private:
	int bound;
};

void Stat(std::vector<int> &iv)
{
	int errors, scores;
	auto print = [&]
	{
		std::cout << "Errors: " << errors << std::endl
			<< "Score: " << scores << std::endl;
	};

	errors = std::accumulate(iv.begin(), iv.end(), 0);//add
	scores = std::accumulate(iv.begin(), iv.end(), 100, std::minus<int>());//minus
	print();

	errors = 0;
	scores = 100;
	std::for_each(iv.begin(), iv.end(), [=](const int& i)mutable
	{
		errors += i;
		scores -= i;
	});
	print();

}

int main()
{
	int a = 3, b = 4;
	//�º���
	_functor f;
	std::cout << f(a, b) << std::endl;	//7

	//lambda����
	auto fun = [=]{return a + b; };
	std::cout << fun() << std::endl;	//7

	std::cout << "CommonFun(10) = " << CommonFun(10) << std::endl;	//45
	std::cout << "LambdaFun(10) = " << LambdaFun(10) << std::endl;	//45

	std::cout << "=============================" << std::endl;
	/*
		ע��㣺
		1�����ڰ�ֵ��ʽ���ݵĲ�׽�б��䴫�ݵ�ֵ��lambda���������ʱ����Ѿ�������
		2�������ô��ݵĲ�׽�б�������䴫�ݵ�ֵ��Ϊ����lambda����ʱ��ֵ��

		�ܽ᣺
		1�������Ҫ��׽��ֵ��Ϊlambda�����ĳ�����ͨ��ʹ�ð�ֵ���ݵķ�ʽ��׽
		2�������׽��ֵ��Ϊlambda��������ʱ�ı��������Ʋ���������Ӧ�ò��ð����ô��ݵķ�ʽ��׽
		*/

	int j = 12;
	auto by_val_lambda = [j]{return j + 1; };
	auto by_ref_lambda = [&j]{return j + 1; };

	std::cout << by_val_lambda() << std::endl;	//13
	std::cout << by_ref_lambda() << std::endl;	//13

	j++;
	std::cout << by_val_lambda() << std::endl;	//13
	std::cout << by_ref_lambda() << std::endl;	//14


	std::cout << "=============================" << std::endl;

	//C++11��׼������lambda���ʽ����ָ���ת������ǰ����lambda����û�в�׽�κα������Һ���ָ����ʾ�ĺ���ԭ�ͣ������lambda����������ͬ�ĵ��÷�ʽ
	auto totalChild = [](int x, int y)->int{return x + y; };
	typedef int(*TwoFun)(int, int);
	typedef int(*OneFun)(int);

	TwoFun tf;
	tf = totalChild;	//ok��lambda����ת��Ϊ����ָ��

	OneFun of;
	of = totalChild;	//error��������һ��

	decltype(totalChild) allChild = totalChild;
	decltype(totalChild) total = tf;	//error������ָ���޷�ת��Ϊlambda

	std::cout << "=============================" << std::endl;
	//lambda��������mutable�ؼ���
	int val = 2;

	auto const_val_lambda = [val]{val = 3; };	//error
	std::cout << "val = " << val << std::endl;	//2

	val = 2;
	auto mutalb_val_lambda = [val]()mutable{val = 3; };
	mutalb_val_lambda();
	std::cout << "val = " << val << std::endl;	//2

	val = 2;
	auto const_ref_lambda = [&val]{val = 3; };
	const_ref_lambda();
	std::cout << "val = " << val << std::endl;	//3

	val = 2;
	auto const_param_lambda = [&val](int v){v = 3; };
	const_param_lambda(val);
	std::cout << "val = " << val << std::endl;	//2


	std::cout << "=================================" << std::endl;
	//��ͳforѭ��
	LargeNums.clear();
	for (auto iter = nums.begin(); iter != nums.end(); ++iter)
	{
		if (*iter > ubound)
			LargeNums.push_back(*iter);
	}

	//ʹ�ú���ָ��
	LargeNums.clear();
	std::for_each(nums.begin(), nums.end(), LargeNumsFun);

	//ʹ�÷º���
	LargeNums.clear();
	std::for_each(nums.begin(), nums.end(), LargeNumsClass(ubound));

	//ʹ��lambda����
	LargeNums.clear();
	std::for_each(nums.begin(), nums.end(), [=](const int& val)
	{
		if (val > ubound)
			LargeNums.push_back(val);
	});


	std::cout << "===========================" << std::endl;
	std::vector<int> iv(10);
	std::generate(iv.begin(), iv.end(), []{return rand() % 10; });
	Stat(iv);

	return 0;
}