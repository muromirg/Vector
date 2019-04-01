#define LOG_ENABLED
#include <cxxtest/TestSuite.h>
#include "myvector.hpp"
#include <iostream>
#include <string>

class VectorTest : public CxxTest::TestSuite{
public:
	void testConstructors()
	{
		try{
			Vector<int> a(10);
			Vector<int> b = {1, 2, 3}, c = b;

			TS_ASSERT_EQUALS(b.at(0), c.at(0));
			c[0] = 100;
			TS_ASSERT_DIFFERS(b.at(0), c.at(0));

			Vector<Vector<int>> mtx;
			
			for (int i = 0; i < 2; i++)
				mtx.push_back({1, 2, 3, 4});

			int int_mtx[] = {1, 2, 3, 4};

			for (int i = 0; i < mtx.size(); i++)
				for(int j = 0; j < mtx[0].size(); j++)
					TS_ASSERT_EQUALS(mtx[i][j], int_mtx[j]);
			
		} catch (std::exception& e){
			TS_FAIL(e.what());
		}
	}

	void testPushPopShrink()
	{
		try{
			Vector<int> x;

			x.push_back(10);

			TS_ASSERT_EQUALS(x.size(), 1);
			TS_ASSERT_EQUALS(x.mem_size(), 3);

			x.push_back(3);
			x.push_back(4);
			x.push_back(6);

			TS_ASSERT_EQUALS(x.size(), 4);
			TS_ASSERT_EQUALS(x.mem_size(), 6);

			x.pop_back();
			x.shrink();

			TS_ASSERT_EQUALS(x.size(), 3);
			TS_ASSERT_EQUALS(x.mem_size(), 3);
		} catch (std::exception& e){
			TS_FAIL(e.what());
		}
	}

	void testInsert()
	{
		try{
			Vector<int> x = {1, 2, 3}, y = {1, 2, 100, 3};

			x.insert(100, 2);

			TS_ASSERT_EQUALS(x, y);

			TS_ASSERT_EQUALS(x.size(), 4);
			TS_ASSERT_EQUALS(x.mem_size(), 6);

		} catch (MyException& e){
			TS_FAIL(e.what());
		}
	}

	void testOperators()
	{
		try{
			Vector<int> x = {1, 2, 3}, y;
			y = x;

			x[0] = 100;
			TSM_ASSERT_DIFFERS("Operator '=' works incorrectly!", x[0], y[0]);

			x[0] = 1;
			TSM_ASSERT("Operator '==' works incorrectly!", x == y);

			Vector<Vector<int>> v1 = {{1, 2, 3}, {4, 5, 6}},
								v2 = {{1, 2, 3}, {4, 6, 5}};
			TSM_ASSERT("Operator '<' works incorrectly!", v1 < v2);
			TSM_ASSERT("Operator '>' works incorrectly!", v2 > v1);

		} catch (MyException& e){
			TS_FAIL(e.what());
		}
	}

	void testGetMethods()
	{
		try{
			Vector<Vector<int>> x;

			x.push_back({1});
			TS_ASSERT_EQUALS(x.size(), 1);
			TS_ASSERT_EQUALS(x.mem_size(), __DATABLOCK);

			x.pop_back();
			TS_ASSERT(x.is_empty());
		} catch (MyException& e){
			TS_FAIL(e.what());
		}
	}
	void testClassVbool()
	{
		uint64_t a = 0;
		size_t index = 62;

		vbool superbool(a, index);
		superbool = true;
		TS_ASSERT(superbool);
		bool x = superbool;

		TSM_ASSERT(std::to_string(a), a == 2);
		TS_ASSERT(x);
		superbool = false;
		x = superbool;
		TS_ASSERT(!x);
	}
	void testVectorBool()
	{
		Vector<bool> vb(1);
		vb[0] = 1;
		vb[1] = 0;
		vb[20] = 1;
		TS_ASSERT(vb[20]);
		TSM_ASSERT(std::to_string(vb[0]) + std::to_string(vb[1]), vb[0] && (!vb[1]));
		Vector<bool> vbb;
		vbb.push_back(1);
		vbb.push_back(0);
		vbb.push_back(1);
		TS_ASSERT(vbb[0] && !vbb[1] && vbb[2]);

		Vector<bool> v3;
		
		for (int i = 0; i < 65; i++)
			v3.push_back(1);
		
		TS_ASSERT(v3[64] && v3[63]);
	}

private:

};
