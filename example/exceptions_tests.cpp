//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <stdexcept>
#include "tests.h"
using namespace snowhouse;


class ClassWithExceptions
{
public:
  int LogicError()
  {
    throw std::logic_error("not logical!");
  }

  double RangeError()
  {
    throw std::range_error("range error!");
  }

  void NoError()
  {
  }
};

void ExceptionTests()
{
  ClassWithExceptions objectUnderTest;

  describe("ExceptionTests");

  it("CanDetectExceptions");
  {
    AssertThrows(std::exception, objectUnderTest.LogicError());
  }

  it("CanAssertOnLastException");
  {
    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));
  }

  it("CanDetectWhenWrongExceptionIsThrown");
  {
    AssertTestFails(AssertThrows(std::logic_error, objectUnderTest.RangeError()), "Wrong exception");
  }

  it("CanPrintExpectedExceptionTypeWhenWrongExceptionIsThrown");
  {
    AssertTestFails(AssertThrows(std::logic_error, objectUnderTest.RangeError()), "Expected std::logic_error");
  }

  it("CanHaveSeveralExceptionAssertionsInSameSpec");
  {
    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));

    AssertThrows(std::range_error, objectUnderTest.RangeError());
    Assert::That(LastException<std::range_error>().what(), Contains("range error!"));
  }

  it("CanHaveSeveralExceptionAssertionForTheSameExceptionInSameSpec");
  {
    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));

    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));
  }

  it("CanDetectWhenNoExceptionIsThrown");
  {
    AssertTestFails(AssertThrows(std::logic_error, objectUnderTest.NoError()), "No exception");
  }

  it("CanPrintExpectedExceptionWhenNoExceptionIsThrown");
  {
    AssertTestFails(AssertThrows(std::logic_error, objectUnderTest.NoError()), "Expected std::logic_error");
  }

  it("ExceptionsAreDestoryedWhenWeExitScope");
  {
    {
      AssertThrows(std::logic_error, objectUnderTest.LogicError());
    }
    AssertThrows(AssertionException, LastException<std::logic_error>());
    Assert::That(LastException<AssertionException>().GetMessage(), Contains("No exception was stored"));
  }
}
