#include "tests.h"
using namespace snowhouse;

void BooleanOperators()
{
  describe("Boolean operators");

  it("ShouldHandleIsFalseOperator");
  {
    Assert::That(false, IsFalse());
  }

  it("ShouldHandleWhenIsFalseFails");
  {
    AssertTestFails(Assert::That(true, IsFalse()), "Expected: false");
  }

  it("ShouldHandleIsTrueOperator");
  {
    Assert::That(true, IsTrue());
  }

  it("ShouldHandleWhenIsTrueFails");
  {
    AssertTestFails(Assert::That(false, IsTrue()), "Expected: true");
  }

  it("ShouldHandleFluentIsTrue");
  {
    Assert::That(true, Is().True());
    AssertTestFails(Assert::That(false, Is().True()), "Expected: true");
  }

  it("ShouldHandleFluentIsFalse");
  {
    Assert::That(false, Is().False());
    AssertTestFails(Assert::That(true, Is().False()), "Expected: false");
  }

  it("ShouldTreatAssertWithoutConstraintAsBooleanConstrains");
  {
    Assert::That(true);
  }
}
