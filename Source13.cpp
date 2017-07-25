#include <iostream>
#include <cstdlib>
#include <thread>
#include <atomic> //C++11��ͷ�ļ�	for  atomic_***ԭ����������
#include <windows.h>	// for Sleep

//ԭ�Ӳ�����ԭ����������
/*
	typedef enum memory_order {
	memory_order_relaxed,
	memory_order_consume,
	memory_order_acquire,
	memory_order_release,
	memory_order_acq_rel,
	memory_order_seq_cst
	} memory_order;

	memory_order_relaxed������ִ��˳�����κεı�֤����ԭ�Ӳ���˳��һ��
	memory_order_consume�����߳��У����к����Ķ����������ڱ���ԭ�Ӳ�����ɺ�ִ��
	memory_order_acquire�����߳��У�����֮ǰ��д������ɺ����ִ�б���ԭ�Ӳ���
	memory_order_release��ͬʱ����memory_order_consume��memory_order_acquire���
	memory_order_acq_rel�����߳��У����к������йر�ԭ�����͵Ĳ����������ڱ���ԭ�Ӳ�����ɺ�ִ��
	memory_order_seq_cst: ȫ���洢������˳��ִ�У�Ĭ��ֵ��

	1��ԭ�Ӵ洢����(store)������ʹ��memory_order_relaxed��memory_order_release��memory_order_seq_cst
	2��ԭ�Ӷ�ȡ����(load)������ʹ��memory_order_relaxed��memory_order_consume��memory_order_acquire��memory_order_seq_cst
	3��RWM����(read-write-modify)��ͬʱ��д����������ʹ��ȫ��memory_orderö��ֵ
*/

std::atomic<int> a{ 0 };
std::atomic<int> b{ 0 };
void Thread1()
{
	int t = 1;
	a.store(t, std::memory_order::memory_order_relaxed);
	b.store(2, std::memory_order::memory_order_relaxed);
}

void Thread2()
{
	while (b.load(std::memory_order::memory_order_relaxed) != 2)
		;
	std::cout << a.load(std::memory_order::memory_order_relaxed) << std::endl;
}

std::atomic<int> c{ 0 };
std::atomic<int> d{ 0 };
//memory_order_release��memory_order_acquire���ʹ�ã���Ϊ���ڴ�˳��Ϊrelease-acquire�ڴ�˳��
void Thread3()
{
	int t = 1;
	c.store(t, std::memory_order_relaxed);
	d.store(2, std::memory_order_release);	//��ԭ�Ӳ���ǰ���е�дԭ�Ӳ����������
}

void Thread4()
{
	//��ԭ�Ӳ���������ɲ���ִ��֮��Ķ�ԭ�Ӳ���
	while (d.load(std::memory_order_acquire) != 2)
		;
	std::cout << c.load(std::memory_order_relaxed) << std::endl;	//1
}

//�����˳���quick_exit��at_quick_exit
//��Ӧ��exit��atexit

//��ֹ������
//�쳣�˳���terminate��abort
//�����˳���exit		ע�ắ��atexit
//			C++11������quick_exit		ע�ắ��at_quick_exit
/*
	exit���������������Զ��������������������һ������atexitע��ĺ�����
		��ע�ắ�������õ�˳����ע���˳��պ��෴
	C++11����������˳���quick_exit�������ú�������ִ������������ֻ��ʹ������ֹ
*/
#define QUICK_EXIT_FLAG	
void OpenDevice(){ std::cout << "device is opened." << std::endl; }
void ResetDeviceStatus(){ std::cout << "device status is reset." << std::endl; }
void CloseDevice(){ std::cout << "device is closed." << std::endl; }

struct A{
	~A(){ std::cout << "Destruct A." << std::endl; }
};

int main()
{
	std::cout << "=========ԭ��������1========" << std::endl;
	std::thread t1(Thread1);
	std::thread t2(Thread2);

	t1.join();
	t2.join();

	std::cout << "=========ԭ��������2========" << std::endl;
	std::thread t3(Thread3);
	std::thread t4(Thread4);

	t3.join();
	t4.join();

#if defined(EXIT_FLAG)
	/*������
		device is opened.
		device status is reset.
		device is closed.
	*/
	std::cout << "=========exit========" << std::endl;
	atexit(CloseDevice);
	atexit(ResetDeviceStatus);
	OpenDevice();
	exit(0);

#elif defined(QUICK_EXIT_FLAG)
	/*�����������в������a����������
		device is closed.
	*/
	std::cout << "=========�����˳�qucik_exit========" << std::endl;
	A a;
	at_quick_exit(CloseDevice);
	quick_exit(0);
#else

#endif
	return 0;
}