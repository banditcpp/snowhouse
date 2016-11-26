#include "tests.h"
using namespace snowhouse;

void StringTests()
{
  describe("StringTests");

  it("should handle string contains constraint");
  {
    Assert::That("abcdef", Contains("bcde"));
  }

  it("should handle match at beginning of string");
  {
    Assert::That("abcdef", Contains("a"));
  }

  it("should detect failing contains");
  {
    AssertTestFails(Assert::That("abcdef", Contains("hello")), "contains hello");
  }

  it("should handle string starting with constraint");
  {
    Assert::That("abcdef", StartsWith("abc"));
  }

  it("should handle string ending with constraint");
  {
    Assert::That("abcdef", EndsWith("def"));
  }

  it("should handle operators for strings");
  {
    Assert::That("abcdef", StartsWith("ab") && EndsWith("ef"));
  }

  it("should handle strings with multiple operators");
  {
    Assert::That("abcdef", StartsWith("ab") && !EndsWith("qwqw"));
  }

  it("should handle of length");
  {
    Assert::That("12345", HasLength(5));
  }

  it("should handle weird long expressions");
  {
    Assert::That("12345", HasLength(5) && StartsWith("123") && !EndsWith("zyxxy"));
  }

  it("should handle std strings");
  {
    Assert::That("12345", Contains(std::string("23")));
  }

  it("should handle simple char");
  {
    Assert::That("12345", StartsWith('1'));
  }
}
