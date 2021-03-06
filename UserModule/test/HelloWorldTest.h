#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>
#include <mockcpp/mockcpp.hpp>

#include <UserModule/HelloWorld.h>

struct Interface 
{
    virtual int func() = 0;
    virtual ~Interface(){}
};

FIXTURE(HelloWorld, base test)
{
    MockObject<Interface> mocker;

	TEST(1 + 2 => 3)
	{
	    ASSERT_EQ(3, add(1, 2));
	}
	
	TEST(mem leak test)
	{
	    char *p = new char[13];
		delete [] p;
	}
	
	TEST(mockcpp global mocker test)
	{
	    MOCKER(add)
		  .stubs()
		  .will(returnValue(200));
		ASSERT_EQ(200, add(1, 2));

        GlobalMockObject::verify();
	}

    TEST(mockcpp mock object test)
    {        
        MOCK_METHOD(mocker, func)
            .expects(once())
            .will(returnValue(3));
        ASSERT_EQ(3, mocker->func());
        mocker.verify();
    }

    // @test(id = parent1)
    TEST(������1)
    {

    }
    
    // @test(id = parent2-test)
    TEST(������2)
    {

    }

    // @test(depends=parent1)
    TEST(����1)
    {

    }

    // @test(depends=parent2-test)
    TEST(����2)
    {
    }
};

FIXTURE(HelloWorld2, ����)
{
    TEST(�������1)
    {
    }
    TEST(�������2)
    {
    }

};

FIXTURE(DataDrivenTest)
{
	DATA_PROVIDER( names, 1
		, DATA_GROUP((const char*)"darwin") 
		, DATA_GROUP((const char*)"arthur") 
		, DATA_GROUP((const char*)"steven"));

	// @test(data="names")
	PTEST( (const char* name), this is a parametered() test)
	{
		INFO(name);
	}
};
