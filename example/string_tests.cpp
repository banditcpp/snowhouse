#include "tests.h"
using namespace snowhouse;

void StringTests()
{
  describe("Strings");

  it("handles string Contains()");
  {
    Assert::That("abcdef", Contains("bcde"));
  }

  it("handles match at beginning of string");
  {
    Assert::That("abcdef", Contains("a"));
  }

  it("detects failing Contains()");
  {
    AssertTestFails(Assert::That("abcdef", Contains("hello")), "contains hello");
  }

  it("handles string StartsWith()");
  {
    Assert::That("abcdef", StartsWith("abc"));
  }

  it("handles string EndsWith()");
  {
    Assert::That("abcdef", EndsWith("def"));
  }

  it("handles operators for strings");
  {
    Assert::That("abcdef", StartsWith("ab") && EndsWith("ef"));
  }

  it("handles strings with multiple operators");
  {
    Assert::That("abcdef", StartsWith("ab") && !EndsWith("qwqw"));
  }

  it("handles HasLength()");
  {
    Assert::That("12345", HasLength(5));
  }

  it("handles weird long expressions");
  {
    Assert::That("12345", HasLength(5) && StartsWith("123") && !EndsWith("zyxxy"));
  }

  it("handles std::string");
  {
    Assert::That("12345", Contains(std::string("23")));
  }

  it("handles simple char");
  {
    Assert::That("12345", StartsWith('1'));
  }
}
