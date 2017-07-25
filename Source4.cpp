#include <iostream>

//��ֵ����
//ǰհ��ǳ���������
class ShollowCopyClass
{
public:
	ShollowCopyClass() :i(new int(0)){}
	ShollowCopyClass(const ShollowCopyClass& s)
		:i(s.i){}		//ֻ�ǽ�������ָ��iָ�����s��i����ָ����ͬһ���ڴ�ռ�
						//������һ�������ͷź�delete������һ�������ָ��ͱ��������ָ�룬���ͷŵ�ʱ��ͻ��ж�
	~ShollowCopyClass(){ delete i; i = nullptr; }

private:
	int *i;
};

class DeepCopyClass
{
public:
	DeepCopyClass() :i(new int(0)){ std::cout << "Construct" << std::endl; }
	DeepCopyClass(const DeepCopyClass& d)
		:i(new int(*d.i)){
		std::cout << "Copy Construct" << std::endl;
	}	//���·����µ��ڴ�ռ䣬���������ָ��ָ��ͬ���ڴ棬���ͷŵ�ʱ��ͻ�������

	//����=�����
	DeepCopyClass& operator=(DeepCopyClass& d1)
	{
		std::cout << "= Construct" << std::endl;
		return DeepCopyClass(d1);
	}
	~DeepCopyClass(){ delete i; i = nullptr; }

private: 
	int *i;
};


class HasPtrMem
{
public:
	HasPtrMem() :d(new int(3)){}
	
	//�������캯��
	HasPtrMem(const HasPtrMem& h)
		:d(new int(*h.d)){}

	//�ƶ����캯��
	HasPtrMem(HasPtrMem&& h)
		:d(h.d){
		h.d = nullptr;	//����
		//���ƶ�������ɺ���ʱ�����������������
		//��Ҫ�ı���ʱ�����ָ���Ա����������ʱ����������ʱ��Ὣ��͵�����Ķ��ڴ汻������
	}
	void AcceptRvalueRef(HasPtrMem&& h)
	{
		//std::move:ǿ�ƽ�һ����ֵת��Ϊ��ֵ���ã�
		//���£�����ֵhǿ��ת��Ϊ����hp����ֵ����
		HasPtrMem hp = std::move(h);	//=====> static_cast<T&&>(lvalue)
	}

	//C++11 ���飺
	//��һЩ�򵥵ġ��������κ���Դ���͵�����˵���Ƿ�ʵ���ƶ�������޹ؽ�Ҫ����Ϊ������������������˵���ƶ����ǿ��������������ƶ�
	//���ڰ�����Դ���͵����У�����������ƶ����캯����Ӧ��ͬʱ�ṩ���Ƽ���������ͬʱ���ṩ

	~HasPtrMem(){ delete d; d = nullptr; }
	int *d;
};

//ʵ�ָ����ܵ�swap�û�����
//���T�ǿ��ƶ��ģ���������ͻᰴ���ƶ������������û�
//�����T�ǲ����ƶ��ģ����տ�����������û�
template<typename T>
void SwapEx(T& a, T& b)
{
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}

//�ƶ����캯���е��쳣����
//���ƶ���������У��׳��쳣�ǱȽ�Σ�յġ�
//������ƶ���������У��׳��쳣���ͻᵼ��ĳЩָ��������ָ�룬�����ھ�������д�����쳣���ƶ����캯����
//ͨ�����ƶ����캯�������һ��noexcept�ؼ��֣����Ա�֤���ƶ��������׳����쳣ֱ�ӵ���terminate������ֹ���У��������������ָ���״̬

//�ڱ�׼���п���ʹ��std::move_if_noexcept��ģ�溯������std::move����
//���������ƶ����캯����û��noexcept�ؼ��֣�����һ����ֵ���ôӶ�ʹ��������ʹ�ÿ�������
//���������ƶ����캯������noexcept�ؼ��֣��򷵻�һ����ֵ���ôӶ�ʹ��������ʹ���ƶ�����
//if no noexcept---->copy
//if has noexcept---->move
class MayThrow
{
public:
	MayThrow(){}
	MayThrow(const MayThrow&)
	{
		std::cout << "MayThrow copy construct" << std::endl;
	}
	MayThrow(MayThrow&&)
	{
		std::cout << "MayThrow move construct" << std::endl;
	}
};

class NoThrow
{
public:
	NoThrow(){}
	NoThrow(const NoThrow&)
	{
		std::cout << "NoThrow copy construct" << std::endl;
	}
	NoThrow(NoThrow&&) noexcept /*ע�����ƶ����캯���м���noexcept�ؼ���*/
	{
		std::cout << "NoThrow move construct" << std::endl;
	}
};

//����ת��forward�����������C++11���½�3.3.6 ����ת����
//�����۵�
//�ڶ�����һ��������ֵ���ã������۵����Ƚ����۵�Ϊ��ֵ����
void RunCode(int &m) { std::cout << "lvalue ref" << std::endl; }
void RunCode(int &&m) { std::cout << "rvalue ref" << std::endl; }
template<typename T>
void PerfectForward(T && t){ RunCode(std::forward<T>(t)); }


int main()
{
	ShollowCopyClass s1;
	ShollowCopyClass s2(s1);	//terminate
	
	DeepCopyClass d1;
	DeepCopyClass d2(d1);		//ok

	//��һ���Ѵ��ڵĶ���ȥ����һ�������ڵĶ���(����֮ǰ������), ���ǿ�����������.
	//��һ���Ѵ��ڵĶ���ȥ������һ���Ѵ��ڵĶ���, ���Ǹ�ֵ��������.
	DeepCopyClass d3;
	DeepCopyClass d4 = d3;	//Copy construct
	d4 = d3;				//operator=()
	
	//��ֵ(lvalue)������ȡ��ַ�������ֵ�
	//��ֵ(rvalue)��������ȡ��ַ�ģ�û�����ֵ�
	//����ֵ(xvalue):��Ҫ���ƶ��Ķ��󣬱���Ϊ����
	int c = 0;
	int &d = c;			//ok����ֵ����
	int &&e = c;		//error����ֵ���ò��ܰ󶨵��κε���ֵ��c�е�ַ�����֣�ʵ���Ǹ���ֵ��
	int &&f = c + 1;	//ok��c+1��û�����֣�Ҳ����ȡ��ַ������c+1�Ǹ���ֵ
	

	MayThrow m;
	MayThrow mt = std::move_if_noexcept(m);		//MayThrow copy construct

	NoThrow n;
	NoThrow nt = std::move_if_noexcept(n);		//NoThrow move construct


	//����ת������
	int a, b;
	PerfectForward(a);				//lvalue ref
	PerfectForward(std::move(b));	//rvalue ref

	return 0;
}