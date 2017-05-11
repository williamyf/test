// Test160912Functor.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/utility/result_of.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
//#define D_SCL_SECURE_NO_WARNINGS
//#include <boost/signals2.hpp>



// C����ʹ�ú���ָ��ͻص�������ʵ�ַº���������һ����������ĺ�����������ʹ�÷º���

/* Callback function */
int compare_ints_function(void*A, void*B)
{
	int a = *((int*)(A));
	int b = *((int*)(B));
	return a < b;
	return *((int*)(A)) < *((int*)(B));
}

/* Declaration of C sorting function */
void sort(void*first_item, size_t item_size, void*last_item, int(*cmpfunc)(void*, void*))
{
	while (first_item != last_item)
	{
		void* next_item = (char*)first_item + item_size;
		if (!cmpfunc(first_item, next_item))
		{
			int t = *((int*)first_item);
			*((int*)first_item) = *((int*)next_item);
			*((int*)next_item) = t;
			continue;
		}
		first_item = next_item;
	}
}

// ��C++�����ͨ����һ��������������������ķ���ʹ��һ���������������һ����ͨ������
class compare_class
{
public:
	bool operator()(int A, int B) const { return A < B; }
};

// Declaration of C++ sorting function.
template<class ComparisonFunctor>
void sort_ints(int* begin_items, int num_items, ComparisonFunctor c)
{
	for (int i=0; i<num_items; ++i)
	{
		int *addri = begin_items + i;
		for (int j = i + 1; j < num_items; ++j)
		{
			int *addrj = begin_items + j;
			if (!c(*addri,*addrj))
			{
				int t = *addri;
				*addri = *addrj;
				*addrj = t;
			}
		}
	}
}

#include <math.h>


int f(int a, int b)		// ��Ԫ����
{
	return a + b;
}
int g(int a, int b, int c) // ��Ԫ����
{
	return a + b*c;
}
typedef int(*f_type)(int, int);			// ����ָ�붨��
typedef int(*g_type)(int, int, int);	// ����ָ�붨��

template<typename T>
struct summary {
	typedef void result_type;
	summary(T v = T()) :sum(v) {}
	void operator() (T const &x) {
		sum += x;
	}
	T sum;
};
void call_back_func(int i)
{
	std::cout << "call_back_func:";
	std::cout << i * 2 << std::endl;
}
class call_back_obj
{
public:
	call_back_obj(int i) :x(i) {};
	~call_back_obj() {};
	void operator()(int i) {
		std::cout << "call_back_obj:";
		std::cout << i*x++ << std::endl;
	}
private:
	int x;
};
class call_back_factory {
public:
	void call_back_func1(int i) {
		std::cout << "call_back_factory1:";
		std::cout << i * 2 << std::endl;
	}
	void call_back_func2(int i,int j) {
		std::cout << "call_back_factory2:";
		std::cout << i *j * 2 << std::endl;
	}
};
class demo_class
{
public:
	demo_class(int i) :n(i) {}
	~demo_class() {};
	template<typename CallBack>
	void accept(CallBack f)
	{
		func = f;
	}
	void run() { func(n); }
private:
	typedef boost::function<void(int)> func_t;
	func_t func;
	int n;
};

void slots1()
{
	std::cout << "slot1 called" << std::endl;
}
void slots2()
{
	std::cout << "slot2 called" << std::endl;
}
int main(void)
{
	int items[] = { 4,3,1,2 };
	//sort((void*)(items), sizeof(int), (void*)(items + 3), compare_ints_function);

	compare_class functor;
	sort_ints(items, sizeof(items) / sizeof(items[0]), functor);


	typedef double (*Func)(double);
	Func func = sqrt;
	boost::result_of<Func(double)>::type t = func(16);
	std::cout << typeid(t).name() << ": " << t << std::endl;

	f_type ff = f;
	f_type pf = &f;
	std::cout << ff(2, 3) << std::endl;
	std::cout << (*ff)(2, 3) << std::endl;
	std::cout << (*pf)(2, 3) << std::endl;
	std::cout << pf(2, 3) << std::endl;

	// �������������
	std::cout << boost::bind(f, 1, 2)() << std::endl;		//�ȼ��� f(1,2)
	std::cout << boost::bind(g, 1, 2, 3)() << std::endl;	//�ȼ��� g(1,2,3)

	int x = 1;
	int y = 2;
	int z = 3;
	std::cout << "ʹ��ռλ��bind�����и���ı仯�������������Ӧ�����Ĺ����������г���һЩռλ�����÷���" << std::endl;
	// �󶨺���
	std::cout << boost::bind(f, _1, 9)(x) << std::endl;				// f(x,9),�൱��bind2nd(f,9)
	std::cout << boost::bind(f, _1, _2)(x, y) << std::endl;			// f(x,y)
	std::cout << boost::bind(f, _2, _1)(x, y) << std::endl;			// f(y,x)
	std::cout << boost::bind(f, _1, _1)(x, y) << std::endl;			// f(x,x),y����������
	std::cout << boost::bind(f, _2, _2)(x, y) << std::endl;			// f(y,y),x����������
	std::cout << boost::bind(g, _1, 8, _2)(x, y) << std::endl;		// g(x,8,y)
	std::cout << boost::bind(g, _3, _2, _2)(x, y, z) << std::endl;	// g(z,y,y),x����������
	// �󶨺���ָ��
	f_type pffun = f;
	g_type pgfun = g;
	std::cout << boost::bind(pffun, _1, 9)(x) << std::endl;				//(*pffun)(x,9)
	std::cout << boost::bind(pgfun, _3, _2, _2)(x, y, z) << std::endl;	//(*pgfun)(z,y,y)
	// �����Ա����
	std::cout << "�����Ա����" << std::endl;
	struct demo
	{
		typedef int result_type;
		int operator()(int a, int b) const
		{
			return a + b;
		}
		int f(int a, int b)
		{
			return a + b;
		}
		void print(int a, int b)
		{
			std::cout << "a+b=" << a + b << std::endl;
		}
		demo(int a = 0, int b = 0) :x(a), y(b) {}
		int x, y;
	};
	demo a, &ra = a;	//���ʵ�����������
	demo *p = &a;		//ָ��
	std::cout << boost::bind(&demo::f, a, _1, 20)(10) << std::endl;
	std::cout << boost::bind(&demo::f, ra, _2, _1)(10, 20) << std::endl;
	std::cout << boost::bind(&demo::f, p, _1, _2)(10, 20) << std::endl;
	std::vector<demo> v(10);
	std::for_each(v.begin(), v.end(), boost::bind(&demo::print, _1, 1, 2));
	// ��public��Ա����
	std::cout << "��public��Ա����" << std::endl;
	std::vector<int> v2(10);
	std::transform(v.begin(), v.end(), v2.begin(), boost::bind(&demo::x, _1));
	BOOST_FOREACH(int x, v2)
		std::cout << x << ",";
	std::cout << std::endl;
	// �󶨺�������
	std::cout << "�󶨺�������" << std::endl;
	std::cout << boost::bind(demo(), _1, _2)(10, 20) << std::endl;
	std::cout << boost::bind(a, _1, _2)(10, 20) << std::endl;
	

	//boost::signals2::signal<void()> sig; // ָ���������void(),����ģ�����ʹ��ȱʡֵ
	//sig.connect(&slots1); // ���Ӳ��1
	//sig.connect(&slots2); // ���Ӳ��2
	//sig(); // ���� operator() �������ź�(�¼�)��������۵���

	std::cout << "function" << std::endl;

	boost::function<int(int,int)> funccc;
	funccc = f;
	std::cout << funccc(111, 222) << std::endl;
	funccc = boost::cref(a);
	std::cout << funccc(222, 222) << std::endl;


	boost::function<int(demo&,int,int)> funbbb;
	funbbb = boost::bind(&demo::f, _1, _2, _3);
	std::cout << funbbb(a,111, 222) << std::endl;
	boost::function<int()> funddd;
	funddd = boost::bind(&demo::f, a, 111, 222);
	std::cout << "funddd()=" << funddd() << std::endl;

	summary<int> s;
	boost::function<void(int const&)> funceee(std::ref(s));
	std::vector<int> vint = { 1,2,3,4 };
	std::for_each(vint.begin(), vint.end(), funceee);
	std::cout << s.sum << std::endl;


	demo_class dc(10);
	dc.accept(call_back_func);
	dc.run();
	dc.run();
	dc.run();
	call_back_obj cbo(2);
	dc.accept(std::ref(cbo));
	dc.run();
	dc.run();
	dc.run();
	call_back_factory cbf;
	dc.accept(boost::bind(&call_back_factory::call_back_func1, cbf, _1));
	dc.run();
	dc.accept(boost::bind(&call_back_factory::call_back_func2, cbf, _1, 5));
	dc.run();
	return 0;
}

