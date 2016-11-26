#include "tests.h"
using namespace snowhouse;

template <typename T>
void SequenceContainerActual()
{
  const char* ExpectedActual = "\nActual: [ 1, 2, 3, 5, 8 ]";

  T container;
  container.clear();
  container.push_back(1);
  container.push_back(2);
  container.push_back(3);
  container.push_back(5);
  container.push_back(8);

  it("ShouldHandleAllOperator");
  {
    Assert::That(container, Has().All().GreaterThan(1).Or().LessThan(4));
  }

  it("ShouldHandleFailingAllOperator");
  {
    AssertTestFails(Assert::That(container, Has().All().GreaterThan(4)), std::string("Expected: all greater than 4") + ExpectedActual);
  }

  it("SHouldHandleInvalidExpressionAfterAllOperator");
  {
    AssertTestFails(Assert::That(container, Has().All().Not()), "The expression contains a not operator without any operand");
  }

  it("ShouldHandleNoExpressionAfterAllOperator");
  {
    AssertTestFails(Assert::That(container, Has().All()), "The expression after \"all\" operator does not yield any result");
  }

  it("ShouldHandleAtLeastOperator");
  {
    Assert::That(container, Has().AtLeast(1).LessThan(5));
  }

  it("ShouldHandleFailingAtLeastOperator");
  {
    AssertTestFails(Assert::That(container, Has().AtLeast(2).LessThan(2)), std::string("Expected: at least 2 less than 2") + ExpectedActual);
  }

  it("ShouldHandleExactlyOperator");
  {
    Assert::That(container, Has().Exactly(1).EqualTo(3));
  }

  it("ShouldHandleFailingExactlyOperator");
  {
    AssertTestFails(Assert::That(container, Has().Exactly(2).EqualTo(3)), std::string("Expected: exactly 2 equal to 3") + ExpectedActual);
  }

  it("ShouldHandleAtMostOperator");
  {
    Assert::That(container, Has().AtMost(1).EqualTo(5));
  }

  it("ShouldHandleFailingAtMostOperator");
  {
    AssertTestFails(Assert::That(container, Has().AtMost(1).EqualTo(3).Or().EqualTo(5)), std::string("Expected: at most 1 equal to 3 or equal to 5") + ExpectedActual);
  }

  it("ShouldHandleNoneOperator");
  {
    Assert::That(container, Has().None().EqualTo(666));
  }

  it("ShouldHandleFailingNoneOperator");
  {
    AssertTestFails(Assert::That(container, Has().None().EqualTo(5)), std::string("Expected: none equal to 5") + ExpectedActual);
  }

  it("ShouldHandleContaining");
  {
    Assert::That(container, Contains(3));
  }

  it("ShouldDetectFailingContains");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("ShouldHandleOfLength");
  {
    Assert::That(container, HasLength(5));
  }

  it("ShouldHandleFailingOfLength");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("ShouldHandleContaining_ExpressionTemplates");
  {
    Assert::That(container, Contains(3));
  }

  it("ShouldDetectFailingContains_ExpressionTemplates");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("ShouldHandleOfLength_ExpressionTemplates");
  {
    Assert::That(container, HasLength(5));
  }

  it("ShouldHandleFailingOfLengthForVectors");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("ShouldHandleIsEmpty");
  {
    T is_empty;

    Assert::That(is_empty, IsEmpty());
  }

  it("ShouldHandleFailingIsEmpty");
  {
    AssertTestFails(Assert::That(container, IsEmpty()), "of length 0");
  }

  it("ShouldHandleFluentIsEmpty");
  {
    T is_empty;

    Assert::That(is_empty, Is().Empty());
  }

  it("ShouldHandleFailingFluentIsEmpty");
  {
    AssertTestFails(Assert::That(container, Is().Empty()), "of length 0");
  }

  it("ShouldHandlerEqualsContainer");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, EqualsContainer(expected));
  }

  it("ShouldHandleEqualsContainer_Fluent");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, Is().EqualToContainer(expected));
  }

  it("ShouldHandleFailingEqualsContainer");
  {
    const int e[] = {4, 2, 4};
    std::list<int> expected(e, e + sizeof(e) / sizeof(e[0]));

    AssertTestFails(Assert::That(container, EqualsContainer(expected)), "Expected: [ 4, 2, 4 ]");
  }

  it("ShouldHandleFailingEqualsContainer_Fluent");
  {
    const int e[] = {4, 2, 4};
    std::list<int> expected(e, e + sizeof(e) / sizeof(e[0]));

    AssertTestFails(Assert::That(container, Is().EqualToContainer(expected)), "Expected: [ 4, 2, 4 ]");
  }
}

void SequenceContainerTests()
{
  describe("SequenceContainerTests(vector)");
  SequenceContainerActual<std::vector<int> >();

  describe("SequenceContainerTests(list)");
  SequenceContainerActual<std::list<int> >();

  describe("SequenceContainerTests(deque)");
  SequenceContainerActual<std::deque<int> >();
}
