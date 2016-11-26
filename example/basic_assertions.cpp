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
  describe("Basic assertions");

  it("handles integer equality");
	{
		Assert::That(5, Is().EqualTo(5));
	}

  it("detects integer inequality");
	{
		AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
	}

  it("detects if Not() fails");
	{
		AssertTestFails(Assert::That(5, Is().Not().EqualTo(5)), "Expected: not equal to 5\nActual: 5\n");
	}

  it("handles strings");
	{
		Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
	}

  it("handles strings without explicit template specialization");
	{
		Assert::That("kim", Is().EqualTo("kim"));
	}

  it("handles GreaterThan()");
	{
		Assert::That(5, Is().GreaterThan(4));
	}

  it("detects when GreaterThan() fails");
	{
		AssertTestFails(Assert::That(5, Is().GreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}

  it("handles LessThan()");
	{
		Assert::That(5, Is().LessThan(6));
	}

  it("detects when LessThan() fails");
	{
		AssertTestFails(Assert::That(6, Is().LessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}

  it("throws explicit failure message");
	{
		AssertTestFails(Assert::Failure("foo"), "foo");
	}

  it("contains location information");
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

  it("ensures exception is thrown");
    {

      AssertThrows(std::runtime_error, throwRuntimeError());
    }

  it("ignores the error");
    {
      ConfigurableAssert<IgnoreErrors>::That(1, Equals(2));
    }

  describe("Assertion expression templates");

  it("handles integer equality");
	{
		Assert::That(5, Equals(5));
	}

  it("detects integer inequality");
	{
		AssertTestFails(Assert::That(5, Equals(4)), "equal to 4");
	}

  it("detects if !Equals() fails");
	{
		AssertTestFails(Assert::That(5, !Equals(5)),
        "Expected: not equal to 5\nActual: 5\n");
	}

  it("handles strings");
	{
		Assert::That(std::string("joakim"), Equals(std::string("joakim")));
	}

  it("handles strings without explicit template specialization");
	{
		Assert::That("kim", Equals("kim"));
	}

  it("handles IsGreaterThan()");
	{
		Assert::That(5, IsGreaterThan(4));
	}

  it("handles IsGreaterThanOrEqualTo()");
	{
		Assert::That(4, IsGreaterThanOrEqualTo(4));
		Assert::That(5, IsGreaterThanOrEqualTo(4));
	}

  it("detects when IsGreaterThan() fails");
	{
		AssertTestFails(Assert::That(5, IsGreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}

  it("detects when IsGreaterThanOrEqualTo() fails");
	{
		AssertTestFails(Assert::That(4, IsGreaterThanOrEqualTo(5)),
        "Expected: greater than or equal to 5\nActual: 4\n");
	}

  it("handles IsLessThan()");
	{
		Assert::That(5, IsLessThan(6));
	}

  it("handles IsLessThanOrEqualTo()");
	{
		Assert::That(5, IsLessThanOrEqualTo(6));
		Assert::That(6, IsLessThanOrEqualTo(6));
	}

  it("detects when IsLessThan() fails");
	{
		AssertTestFails(Assert::That(6, IsLessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}

  it("detects when IsLessThanOrEqualTo() fails");
	{
		AssertTestFails(Assert::That(6, IsLessThanOrEqualTo(5)),
			"Expected: less than or equal to 5\nActual: 6\n");
	}

#ifdef SNOWHOUSE_HAS_NULLPTR
  it("handles IsNull()");
    {
       Assert::That(nullptr, IsNull());
    }

  it("handles Is().Null()");
    {
       Assert::That(nullptr, Is().Null());
    }

  it("handles !IsNull()");
    {
       int anInt = 0;
       Assert::That(&anInt, ! IsNull());
    }

  it("detects when IsNull() fails (real address)");
    {
       int anInt = 0;
       std::ostringstream message;
       message << "Expected: equal to nullptr\nActual: " << &anInt << "\n";
       AssertTestFails(Assert::That(&anInt, IsNull()), message.str());
    }

  it("detects when Is().Null() fails");
    {
       int anInt = 0;
       std::ostringstream message;
       message << "Expected: equal to nullptr\nActual: " << &anInt << "\n";
       AssertTestFails(Assert::That(&anInt, Is().Null()), message.str());
    }

  it("detects when !IsNull() fails (nullptr)");
    {
       std::ostringstream message;
       message << "Expected: not equal to nullptr\nActual: nullptr\n";

       AssertTestFails(Assert::That(nullptr, ! IsNull()), message.str());
    }
#endif
}
