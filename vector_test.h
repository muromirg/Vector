#define LOG_ENABLED
#include <cxxtest/TestSuite.h>
#include "myvector.hpp"
#include <iostream>
#include <string>

class VectorTest : public CxxTest::TestSuite {
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
		try{
			Vector<int> x;
			x.pop_back();
		} catch (MyException& e){
			TS_TRACE(std::string(e.what()) + ' ' +
					 std::string(e.get_info().file) + ' ' + 
					 std::string(e.get_info().function));
	
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
		try{
			Vector<int> x;
			x.insert(10, 1000);
		} catch (MyException& e){
			TS_TRACE(std::string(e.what()) + ' ' +
					 std::string(e.get_info().file) + ' ' + 
					 std::string(e.get_info().function));
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

	void testConstructorsBool()
	{
		try{
			Vector<bool> a(10);

			a[7] = 1;

			Vector<bool> b = a;

			TS_ASSERT_EQUALS(b.at(0), a.at(0));
			b[0] = 100;
			TS_ASSERT_DIFFERS(b.at(0), a.at(0));

			Vector<Vector<bool>> mtx;
			
			for (int i = 0; i < 2; i++)
				mtx.push_back({1, 0, 1, 0, 1});

			bool int_mtx[] = {1, 0, 1, 0, 1};

			for (int i = 0; i < mtx.size(); i++)
				for(int j = 0; j < mtx[0].size(); j++)
					TS_ASSERT_EQUALS(mtx[i][j], int_mtx[j]);
			
		} catch (std::exception& e){
			TS_FAIL(e.what());
		}
	}

	void testPushPopShrinkBool()
	{
		try{
			Vector<bool> x;

			x.push_back(1);

			TS_ASSERT_EQUALS(x.size(), 1);
			TS_ASSERT_EQUALS(x.mem_size(), 1);

			x.push_back(0);
			x.push_back(0);
			x.push_back(1);

			TS_ASSERT_EQUALS(x.size(), 4);
			TS_ASSERT_EQUALS(x.mem_size(), 1);

			x.pop_back();
			x.shrink();

			TS_ASSERT_EQUALS(x.size(), 3);
			TS_ASSERT_EQUALS(x.mem_size(), 1);
		} catch (std::exception& e){
			TS_FAIL(e.what());
		}
		try{
			Vector<bool> x;
			x.pop_back();
		} catch (MyException& e){
			TS_TRACE(std::string(e.what()) + ' ' +
					 std::string(e.get_info().file) + ' ' + 
					 std::string(e.get_info().function));
		}
	}

	void testInsertBool()
	{
		try{
			Vector<bool> x = {1, 0, 1}, y = {1, 0, 0, 1};

			x.insert(0, 1);

			TS_ASSERT(x == y);

		} catch (MyException& e){
			TS_FAIL(e.what());
		}
		try{
			Vector<bool> x;
			x.insert(1, 1000);
		} catch (MyException& e){
			TS_TRACE(std::string(e.what()) + ' ' +
					 std::string(e.get_info().file) + ' ' + 
					 std::string(e.get_info().function));
		}
	}
};
