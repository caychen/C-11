#include <iostream>
#include <memory>

//����ָ������������

void CheckWeakPtr(std::weak_ptr<int> & wp)
{
	std::shared_ptr<int> sp = wp.lock();
	if (sp != nullptr)
		std::cout << "still " << *sp << std::endl;
	else
		std::cout << "pointer is invalid" << std::endl;
}

//����ָ��
//unique_ptr��shared_ptr��weak_ptr
//1��unique_ptr������������unique_ptr���͵�ָ������������ڴ�
//		unique_ptr��һ��ɾ���˿������캯�����������ƶ����캯����ָ���װ����
//		����unique_ptr��֧�ֿ������죬����֧�ֽ�һ��unique_ptr���͵�ָ�븳ֵ�����ƣ�������һ��ָ�룬
//		ֻ��ͨ����ֵ��unique_ptr��������ƶ����죬һ������ɹ���
//2��shared_ptr��������ָ�빲��ӵ��ͬһ���ѷ��������ڴ棬
//		ĳ��shared_ptrʧЧ������Ӱ������shared_ptr�Զ����ڴ������
//		shared_ptr��reset����ֻ�ǵ������ü��������ͣ����ᵼ�¶��ڴ���ͷţ�
//		ֻ�е����ü�������ֵ�����ʱ��shared_ptr�Ż��������ͷ���ռ�Ķ��ڴ�ռ�
//3��weak_ptr������ָ��shared_ptrָ��ָ��Ķ����ڴ棬����ӵ�и��ڴ�
//		ʹ��lock��Ա��������ɷ���ָ���ڴ��һ��shared_ptr���󣬲�������ָ��Ķ����ڴ���Чʱ�����ؿ�ָ��nullptr
int main()
{
	std::unique_ptr<int> up1(new int(11));
	std::unique_ptr<int> up2 = up1; //error��unique_ptr������ָ�������ڴ�
	std::cout << *up1 << std::endl;	//11
	std::cout << *up2 << std::endl;	//error������

	std::unique_ptr<int> up3 = std::move(up1);//��up1ǿ��ת����up3����ֵ���ã���up3����˶����ڴ��ʹ��Ȩ��up1��ʧȥ����Ȩ
	std::cout << *up1 << std::endl; //terminate�����д���up1�Ѿ�ʧЧ��ʧȥ��ָ�������Ȩ
	std::cout << *up3 << std::endl; //11
	up3.reset();//��ʽ�ͷ��ڴ�
	up1.reset();//���ᵼ�����д���

	std::cout << *up3 << std::endl; //terminate��up3�ͷ�֮���޷���ʹ��*�����ʶ��ڴ�

	std::shared_ptr<int> sp1(new int(12));
	std::shared_ptr<int> sp2 = sp1; //ok��sp1��sp2��������ڴ�
	std::cout << *sp1 << std::endl; //12
	std::cout << *sp2 << std::endl; //12
	sp1.reset();
	std::cout << *sp2 << std::endl; //12��sp1���ͷţ�����Ӱ��sp2�ķ��ʲ���

	std::weak_ptr<int> wp = sp1;	//ָ��shared_ptr����
	std::cout << *wp << std::endl;	//error����Ȼָ����shared_ptr���󣬵���weak_ptr��ӵ����ָ��Ķ����ڴ�
	CheckWeakPtr(wp); //still 12
	sp1.reset();
	CheckWeakPtr(wp); //still 12
	sp2.reset();
	//����������shared_ptr��reset���������¶Զ��ڴ��������ü�����Ϊ0�����ͷŶ��ڴ�ռ䣬�����ٴε���lock�����󣬷���һ��nullptrָ��
	CheckWeakPtr(wp); //pointer is invalid

	return 0;
}