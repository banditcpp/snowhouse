#include "tests.h"
using namespace snowhouse;

void BooleanOperators()
{
  describe("Boolean operators");

  it("should handle is false operator");
  {
    Assert::That(false, IsFalse());
  }

  it("should handle when is false fails");
  {
    AssertTestFails(Assert::That(true, IsFalse()), "Expected: false");
  }

  it("should handle is true operator");
  {
    Assert::That(true, IsTrue());
  }

  it("should handle when is true fails");
  {
    AssertTestFails(Assert::That(false, IsTrue()), "Expected: true");
  }

  it("should handle fluent is true");
  {
    Assert::That(true, Is().True());
    AssertTestFails(Assert::That(false, Is().True()), "Expected: true");
  }

  it("should handle fluent is false");
  {
    Assert::That(false, Is().False());
    AssertTestFails(Assert::That(true, Is().False()), "Expected: false");
  }

  it("should treat assert without constraint as boolean constrains");
  {
    Assert::That(true);
  }
}
