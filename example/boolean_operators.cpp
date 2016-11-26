#include "tests.h"
using namespace snowhouse;

void BooleanOperators()
{
  describe("Boolean operators");

  std::cout << "ShouldHandleIsFalseOperator" << std::endl;
  {
    Assert::That(false, IsFalse());
  }

  std::cout << "ShouldHandleWhenIsFalseFails" << std::endl;
  {
    AssertTestFails(Assert::That(true, IsFalse()), "Expected: false");
  }

  std::cout << "ShouldHandleIsTrueOperator" << std::endl;
  {
    Assert::That(true, IsTrue());
  }

  std::cout << "ShouldHandleWhenIsTrueFails" << std::endl;
  {
    AssertTestFails(Assert::That(false, IsTrue()), "Expected: true");
  }

  std::cout << "ShouldHandleFluentIsTrue" << std::endl;
  {
    Assert::That(true, Is().True());
    AssertTestFails(Assert::That(false, Is().True()), "Expected: true");
  }

  std::cout << "ShouldHandleFluentIsFalse" << std::endl;
  {
    Assert::That(false, Is().False());
    AssertTestFails(Assert::That(true, Is().False()), "Expected: false");
  }

  std::cout << "ShouldTreatAssertWithoutConstraintAsBooleanConstrains" << std::endl;
  {
    Assert::That(true);
  }
}
