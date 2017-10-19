#include "stdafx.h"
#include "ExceptionalIfMacroTest.h"
#include "ExceptionalIfMacro.h"

#ifdef ExceptionIfCalleDefine
#undef ExceptionIfCalleDefine
#define ExceptionIfCalleDefine  TestExceptionalIfCalle
#endif

volatile bool g_expHappened = false;

class TestExceptionalIfCalle
{
public:
	static inline void failed()
	{
		g_expHappened = true;
	}
};



namespace if_except_namespace_test
{

	struct testNullObj
	{
		testNullObj(int val) : value(val) {}
		int value;
	};

	bool ExceptionIfTest0()
	{
		testNullObj localObj(0);
		testNullObj* testObj = &localObj;
		g_expHappened = false;

		eif(auto test0 = testObj)
		{
			return test0->value == 0 && g_expHappened == false;
		}

		return false;
	}

	bool ExceptionIfTest1()
	{
		testNullObj localObj(1);
		testNullObj* testObj = &localObj;
		g_expHappened = false;

		eif(auto test0 = testObj)
			return test0->value == 1 && g_expHappened == false;

		return false;
	}

	bool ExceptionIfTest2()
	{
		testNullObj* testObj = nullptr;
		g_expHappened = false;
		eif(auto test0 = testObj)
		{
			return false;
		}

		return g_expHappened;
	}

	bool ExceptionIfTest3()
	{
		testNullObj* testObj = nullptr;
		g_expHappened = false;

		eif(auto test0 = testObj)
			return false;

		return g_expHappened;
	}


	bool ExceptionIfTest4()
	{
		testNullObj* testObj = nullptr;
		g_expHappened = false;

		eif(auto test0 = testObj)
			return false;
		else
			return g_expHappened == false; // call happens after

		return false;
	}

	bool ExceptionIfTest5()
	{
		testNullObj* testObj = nullptr;
		g_expHappened = false;

		eif(auto test0 = testObj)
		{
			return false;
		}
		else
		{
			return g_expHappened == false; // call happens after
		}

		return false;
	}


	bool ExceptionIfTest6()
	{
		testNullObj localObj(0);
		testNullObj* testObj = &localObj;
		g_expHappened = false;

		eif(auto test0 = testObj)
		{
			return test0->value == 0 && g_expHappened == false;
		}
		else
		{
			return false;
		}

		return false;
	}


	bool ExceptionIfTest7()
	{
		testNullObj localObj(0);
		testNullObj* testObj = &localObj;
		testNullObj localObjOther(1);
		testNullObj* testObjOther = &localObjOther;
		bool rtn = false;
		eif(auto test0 = testObj)
		{
			eif(auto test1 = testObjOther)
			{
				rtn = test0->value == 0 && test1->value == 1;
			}
		}
		

		return rtn && g_expHappened == false;
	}


	bool ExceptionIfTest8()
	{
		testNullObj localObj(0);
		testNullObj* testObj = &localObj;
		testNullObj* testObjOther = nullptr;
		bool rtn = false;
		eif(auto test0 = testObj)
		{
			rtn = true;
			eif(auto test1 = testObjOther)
			{
				rtn = false;
			}
		}


		return rtn && g_expHappened == true;
	}

	bool TestAll()
	{
		bool rtn = true;
		for(int i =0 ;i < 3; i++)
		{ 
			rtn &= ExceptionIfTest0();
			rtn &= ExceptionIfTest1();
			rtn &= ExceptionIfTest2();
			rtn &= ExceptionIfTest3();
			rtn &= ExceptionIfTest4();
			rtn &= ExceptionIfTest5();
			rtn &= ExceptionIfTest6();
			rtn &= ExceptionIfTest8();
		}
	
		return rtn;
	}
}

