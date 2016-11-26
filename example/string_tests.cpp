#include "tests.h"
using namespace snowhouse;

void StringTests()
{
  describe("StringTests");

  it("ShouldHandleStringContainsConstraint");
  {
    Assert::That("abcdef", Contains("bcde"));
  }

  it("StringConstraintShouldHandleMatchAtBeginningOfString");
  {
    Assert::That("abcdef", Contains("a"));
  }

  it("ShouldDetectFailingContains");
  {
    AssertTestFails(Assert::That("abcdef", Contains("hello")), "contains hello");
  }

  it("ShouldHandleStringStartingWithConstraint");
  {
    Assert::That("abcdef", StartsWith("abc"));
  }

  it("ShouldHandleStringEndingWithConstraint");
  {
    Assert::That("abcdef", EndsWith("def"));
  }

  it("ShouldHandleOperatorsForStrings");
  {
    Assert::That("abcdef", StartsWith("ab") && EndsWith("ef"));
  }

  it("ShouldHandleStringsWithMultipleOperators");
  {
    Assert::That("abcdef", StartsWith("ab") && !EndsWith("qwqw"));
  }

  it("ShouldHandleOfLength");
  {
    Assert::That("12345", HasLength(5));
  }

  it("ShouldHandleWeirdLongExpressions");
  {
    Assert::That("12345", HasLength(5) && StartsWith("123") && !EndsWith("zyxxy"));
  }

  it("ShouldHandleStdStrings");
  {
    Assert::That("12345", Contains(std::string("23")));
  }

  it("ShouldHandleSimpleChar");
  {
    Assert::That("12345", StartsWith('1'));
  }
}
