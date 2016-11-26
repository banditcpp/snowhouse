#include <stdexcept>
#include "tests.h"
using namespace snowhouse;

void throwRuntimeError() {
   throw std::runtime_error("This is expected");
}

struct IgnoreErrors {
   template <class ExpectedType, class ActualType>
   static void Handle(const ExpectedType&, const ActualType&, const char*, int)
   {
   }

   static void Handle(const std::string&)
   {
   }
};

void BasicAssertions()
{
  describe("BasicAssertions");

  it("should handle integer equality");
	{
		Assert::That(5, Is().EqualTo(5));
	}

  it("should detect integer inequality");
	{
		AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
	}

  it("should detect if not fails");
	{
		AssertTestFails(Assert::That(5, Is().Not().EqualTo(5)), "Expected: not equal to 5\nActual: 5\n");
	}

  it("should handle strings");
	{
		Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
	}

  it("should handle strings without explicit template specialization");
	{
		Assert::That("kim", Is().EqualTo("kim"));
	}

  it("should handle greater than");
	{
		Assert::That(5, Is().GreaterThan(4));
	}

  it("should detect when greater than fails");
	{
		AssertTestFails(Assert::That(5, Is().GreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}

  it("should handle less than");
	{
		Assert::That(5, Is().LessThan(6));
	}

  it("should detect when less than fails");
	{
		AssertTestFails(Assert::That(6, Is().LessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}

  it("should throw explicit failure message");
	{
		AssertTestFails(Assert::Failure("foo"), "foo");
	}

  it("should contain location information");
  {
    int line;
    std::string file;

    try
    {
      Assert::That(5, Equals(2), "filename", 32);
    }
    catch(const AssertionException& e)
    {
      line = e.GetLineNumber();
      file = e.GetFilename();
    }

    Assert::That(line, Equals(32));
    Assert::That(file, Equals("filename"));
  }

  it("should ensure exception is thrown");
    {

      AssertThrows(std::runtime_error, throwRuntimeError());
    }

  it("should ignore the error");
    {
      ConfigurableAssert<IgnoreErrors>::That(1, Equals(2));
    }


  describe("AssertionExpressionTemplates");

  it("should handle integer equality");
	{
		Assert::That(5, Equals(5));
	}

  it("should detect integer inequality");
	{
		AssertTestFails(Assert::That(5, Equals(4)), "equal to 4");
	}

  it("should detect if not fails");
	{
		AssertTestFails(Assert::That(5, !Equals(5)),
        "Expected: not equal to 5\nActual: 5\n");
	}

  it("should handle strings");
	{
		Assert::That(std::string("joakim"), Equals(std::string("joakim")));
	}

  it("should handle strings without explicit template specialization");
	{
		Assert::That("kim", Equals("kim"));
	}

  it("should handle greater than");
	{
		Assert::That(5, IsGreaterThan(4));
	}

  it("should handle greater than or equal to");
	{
		Assert::That(4, IsGreaterThanOrEqualTo(4));
		Assert::That(5, IsGreaterThanOrEqualTo(4));
	}

  it("should detect when greater than fails");
	{
		AssertTestFails(Assert::That(5, IsGreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}

  it("should detect when greater than or equal to fails");
	{
		AssertTestFails(Assert::That(4, IsGreaterThanOrEqualTo(5)),
        "Expected: greater than or equal to 5\nActual: 4\n");
	}

  it("should handle less than");
	{
		Assert::That(5, IsLessThan(6));
	}

  it("should handle less than or equal to");
	{
		Assert::That(5, IsLessThanOrEqualTo(6));
		Assert::That(6, IsLessThanOrEqualTo(6));
	}

  it("should detect when less than fails");
	{
		AssertTestFails(Assert::That(6, IsLessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}

  it("should detect when less than or equal to fails");
	{
		AssertTestFails(Assert::That(6, IsLessThanOrEqualTo(5)),
			"Expected: less than or equal to 5\nActual: 6\n");
	}

#if __cplusplus > 199711L
  it("should handle null");
    {
       Assert::That(nullptr, IsNull());
    }

  it("should handle null");
    {
       Assert::That(nullptr, Is().Null());
    }

  it("should handle not null");
    {
       int anInt = 0;
       Assert::That(&anInt, ! IsNull());
    }

  it("should detect when is null fails");
    {
       int anInt = 0;
       std::ostringstream message;
       message << "Expected: equal to nullptr\nActual: " << &anInt << "\n";
       AssertTestFails(Assert::That(&anInt, IsNull()), message.str());
    }

  it("should detect when is null fails");
    {
       int anInt = 0;
       std::ostringstream message;
       message << "Expected: equal to nullptr\nActual: " << &anInt << "\n";
       AssertTestFails(Assert::That(&anInt, Is().Null()), message.str());
    }

  it("should detect when is not null fails");
    {
       std::ostringstream message;
       message << "Expected: not equal to nullptr\nActual: nullptr\n";

       AssertTestFails(Assert::That(nullptr, ! IsNull()), message.str());
    }
#endif
}
