#include "tests.h"
using namespace snowhouse;

void OperatorTests()
{
  describe("OperatorTests");

  it("should handle and operator expression templates");
  {
    Assert::That(5, IsLessThan(6) && IsGreaterThan(4));
  }

  it("should handle and operator");
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }

  it("should handle and operator fail expression templates");
  {
    AssertTestFails(Assert::That(5, IsLessThan(7) && IsGreaterThan(5)),
        "less than 7 and greater than 5");
  }

  it("should handle and operator fail");
  {
    AssertTestFails(Assert::That(5, Is().LessThan(7).And().GreaterThan(5)),
        "less than 7 and greater than 5");
  }

  it("should handle or operator");
  {
    Assert::That(12, Is().LessThan(7).Or().GreaterThan(5));
  }

  it("should handle or operator expression templates");
  {
    Assert::That(12, IsLessThan(7) || IsGreaterThan(5));
  }

  it("should handle or operator fails");
  {
    AssertTestFails(Assert::That(67, Is().LessThan(12).Or().GreaterThan(99)),
        "less than 12 or greater than 99");
  }

  it("should handle or operator fails expression templates");
  {
    AssertTestFails(Assert::That(67, IsLessThan(12) || IsGreaterThan(99)),
        "less than 12 or greater than 99");
  }

  it("should handle not operators");
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  it("should handle not operators expression templates");
  {
    Assert::That(5, !Equals(4));
  }

  it("should handle not operators fails");
  {
    AssertTestFails(Assert::That(12, Is().Not().EqualTo(12)), "not equal to 12");
  }

  it("should handle not operators fails expression templates");
  {
    AssertTestFails(Assert::That(12, !Equals(12)), "not equal to 12");
  }

  it("should handle not operators for strings");
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  it("should handle not operators for strings expression templates");
  {
    Assert::That("joakim", !Equals("harry"));
  }

  it("should handle both left and right associative operators");
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }

  it("should handle both left and right associative operators expression templates");
  {
    Assert::That(5, IsGreaterThan(4)&& !IsLessThan(3));
  }

  it("yields error on malformed expression");
  {
    AssertTestFails(Assert::That(4, Is().Not()),
        "The expression contains a not operator without any operand");
  }

  describe("EqualsWithDelta");

  it("should fail for actual larger than delta");
  {
    AssertTestFails(Assert::That(3.9, EqualsWithDelta(3, 0.5)),
        "Expected: equal to 3 (+/- 0.5)");
  }

  it("should fail for actual less than delta");
  {
    AssertTestFails(Assert::That(2.49, EqualsWithDelta(3, 0.5)),
        "Expected: equal to 3 (+/- 0.5)");
  }

  it("should succeed");
  {
    Assert::That(2, EqualsWithDelta(1.9, 0.1));
  }

  it("should fail for actual larger than delta");
  {
    AssertTestFails(Assert::That(3.9, Is().EqualToWithDelta(3, 0.5)),
        "Expected: equal to 3 (+/- 0.5)");
  }

  it("should fail for actual less than delta");
  {
    AssertTestFails(Assert::That(2.49, Is().EqualToWithDelta(3, 0.5)),
        "Expected: equal to 3 (+/- 0.5)");
  }

  it("should succeed");
  {
    Assert::That(2, Is().EqualToWithDelta(1.9, 0.1));
  }

}
