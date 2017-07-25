#include <iostream>

//ָ���ֵnullptr
/*
	����
		1�����ж���Ϊnullptr_t���͵����ݶ��ǵȼ۵ģ���ΪҲ��ȫһ��
		2��nullptr_t�������ݿ�����ʽת��������һ��ָ������
		3��nullptr_t�������ݲ���ת��Ϊ��ָ�����ͣ���ʹʹ��reinterpret_cast<nullptr_t>()�ķ���Ҳ����
		4��nullptr_t�������ݲ�����������������ʽ
		5��nullptr_t�������ݿ������ڹ�ϵ������ʽ����������nullptr_t�������ݻ���ָ���������ݽ��бȽϣ����ҽ�����ϵ�����Ϊ==��<=��>=��ʱ����true��
*/
void fun(int)
{
	std::cout << "fun(int)" << std::endl;
}

void fun(char*)
{
	std::cout << "fun(char*)" << std::endl;
}

template<typename T> void g(T* t){}
template<typename T> void h(T t){}

int main()
{
	fun(0);				//fun(int)
	fun(nullptr);		//fun(char*)

	std::cout << "===========================" << std::endl;
	//��������

	//nullptr������ʽת��Ϊchar*
	char *cp = nullptr;

	//nullptr������ʽת��Ϊint���κ�����Ҳ����ת��Ϊnullptr_t
	int n1 = nullptr;	//error
	int n2 = reinterpret_cast<nullptr_t>(nullptr);	//error

	//nullptr��nullptr_t���ͱ����������Ƚϣ���ʹ��==��<=��>=�������Ƚ�ʱ�ŷ���true
	nullptr_t nptr;
	if (nptr == nullptr)	//nullptr_t nptr == nullptr
		std::cout << "nullptr_t nptr == nullptr" << std::endl;
	else
		std::cout << "nullptr_t nptr != nullptr" << std::endl;

	if (nptr < nullptr)		//nullptr_t nptr >= nullptr
		std::cout << "nullptr_t nptr < nullptr" << std::endl;
	else
		std::cout << "nullptr_t nptr >= nullptr" << std::endl;

	//����ת��Ϊ���ͻ���bool����
	if (0 == nullptr);	//error
	if (nullptr);	//error

	//���ܽ�����������
	nullptr += 1;	//error
	nullptr * 5;	//error

	sizeof(nullptr);
	typeid(nullptr);
	throw(nullptr);

	//nullptr����������nullptr_t��������ָ��
	//ģ��ֻ�ܰ�nullptr����һ����ͨ�����ͽ����Ƶ��������Ὣ����ΪT*ָ�룬�����Ҫ�Ƶ���ָ�����ͣ�������ʽת������
	g(nullptr);		//error
	g((float*)nullptr);

	h(0);
	h(nullptr);
	h((float*)nullptr);

	//nullptr��(void*)0������
	/*
		1��nullptr��һ������ʱ�ڵĳ��������������Ǳ���ʱ�ڵ�һ���ؼ��֣��ܹ�Ϊ��������ʶ��
			��(void*)0ֻ��һ��ǿ��ת�����ʽ���䷵�ص�Ҳ��һ��void*ָ�����͡�
		2����C++�����У�nullptr���κ�ָ���ת��������ʽ�ģ���(void*)����뾭������ת�������ʹ�á�
	*/
	int *px = (void*)0;	//error��������ʽ�ؽ�������ָ��ת��Ϊint*���͵�ָ��
	int *py = nullptr;	//ok
	return 0;
}