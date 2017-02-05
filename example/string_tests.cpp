#include "tests.h"
using namespace snowhouse;

void StringTests()
{
  describe("Strings");

  it("handles string Contains()");
  {
    AssertThat("abcdef", Contains("bcde"));
  }

  it("handles match at beginning of string");
  {
    AssertThat("abcdef", Contains("a"));
  }

  it("detects failing Contains()");
  {
    AssertTestFails(AssertThat("abcdef", Contains("hello")), "contains hello");
  }

  it("handles string StartsWith()");
  {
    AssertThat("abcdef", StartsWith("abc"));
  }

  it("handles string EndsWith()");
  {
    AssertThat("abcdef", EndsWith("def"));
  }

  it("handles operators for strings");
  {
    AssertThat("abcdef", StartsWith("ab") && EndsWith("ef"));
  }

  it("handles strings with multiple operators");
  {
    AssertThat("abcdef", StartsWith("ab") && !EndsWith("qwqw"));
  }

  it("handles HasLength()");
  {
    AssertThat("12345", HasLength(5));
  }

  it("handles weird long expressions");
  {
    AssertThat("12345", HasLength(5) && StartsWith("123") && !EndsWith("zyxxy"));
  }

  it("handles std::string");
  {
    AssertThat("12345", Contains(std::string("23")));
  }

  it("handles simple char");
  {
    AssertThat("12345", StartsWith('1'));
  }
}
