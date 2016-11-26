#include "tests.h"
using namespace snowhouse;

void BooleanOperators()
{
  describe("Boolean operators");

  it("handles IsFalse()");
  {
    Assert::That(false, IsFalse());
  }

  it("handles failing IsFalse()");
  {
    AssertTestFails(Assert::That(true, IsFalse()), "Expected: false");
  }

  it("handles IsTrue()");
  {
    Assert::That(true, IsTrue());
  }

  it("handles failing IsTrue()");
  {
    AssertTestFails(Assert::That(false, IsTrue()), "Expected: true");
  }

  it("handles Is().True()");
  {
    Assert::That(true, Is().True());
    AssertTestFails(Assert::That(false, Is().True()), "Expected: true");
  }

  it("handles Is().False()");
  {
    Assert::That(false, Is().False());
    AssertTestFails(Assert::That(true, Is().False()), "Expected: false");
  }

  it("treats assert without constraint as boolean constrains");
  {
    Assert::That(true);
  }
}
