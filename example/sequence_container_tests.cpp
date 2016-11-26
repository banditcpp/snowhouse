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

  it("should handle all operator");
  {
    Assert::That(container, Has().All().GreaterThan(1).Or().LessThan(4));
  }

  it("should handle failing all operator");
  {
    AssertTestFails(Assert::That(container, Has().All().GreaterThan(4)), std::string("Expected: all greater than 4") + ExpectedActual);
  }

  it("should handle invalid expression after all operator");
  {
    AssertTestFails(Assert::That(container, Has().All().Not()), "The expression contains a not operator without any operand");
  }

  it("should handle no expression after all operator");
  {
    AssertTestFails(Assert::That(container, Has().All()), "The expression after \"all\" operator does not yield any result");
  }

  it("should handle at least operator");
  {
    Assert::That(container, Has().AtLeast(1).LessThan(5));
  }

  it("should handle failing at least operator");
  {
    AssertTestFails(Assert::That(container, Has().AtLeast(2).LessThan(2)), std::string("Expected: at least 2 less than 2") + ExpectedActual);
  }

  it("should handle exactly operator");
  {
    Assert::That(container, Has().Exactly(1).EqualTo(3));
  }

  it("should handle failing exactly operator");
  {
    AssertTestFails(Assert::That(container, Has().Exactly(2).EqualTo(3)), std::string("Expected: exactly 2 equal to 3") + ExpectedActual);
  }

  it("should handle at most operator");
  {
    Assert::That(container, Has().AtMost(1).EqualTo(5));
  }

  it("should handle failing at most operator");
  {
    AssertTestFails(Assert::That(container, Has().AtMost(1).EqualTo(3).Or().EqualTo(5)), std::string("Expected: at most 1 equal to 3 or equal to 5") + ExpectedActual);
  }

  it("should handle none operator");
  {
    Assert::That(container, Has().None().EqualTo(666));
  }

  it("should handle failing none operator");
  {
    AssertTestFails(Assert::That(container, Has().None().EqualTo(5)), std::string("Expected: none equal to 5") + ExpectedActual);
  }

  it("should handle containing");
  {
    Assert::That(container, Contains(3));
  }

  it("should detect failing contains");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("should handle of length");
  {
    Assert::That(container, HasLength(5));
  }

  it("should handle failing of length");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("should handle containin_ expression templates");
  {
    Assert::That(container, Contains(3));
  }

  it("should detect failing contains expression templates");
  {
    AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
  }

  it("should handle length expression templates");
  {
    Assert::That(container, HasLength(5));
  }

  it("should handle failing of length for vectors");
  {
    AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  it("should handle is empty");
  {
    T is_empty;

    Assert::That(is_empty, IsEmpty());
  }

  it("should handle failing is empty");
  {
    AssertTestFails(Assert::That(container, IsEmpty()), "of length 0");
  }

  it("should handle fluent is empty");
  {
    T is_empty;

    Assert::That(is_empty, Is().Empty());
  }

  it("should handle failing fluent is empty");
  {
    AssertTestFails(Assert::That(container, Is().Empty()), "of length 0");
  }

  it("should handler equals container");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, EqualsContainer(expected));
  }

  it("should handle equals container");
  {
    std::list<int> expected;
    expected.assign(container.begin(), container.end());

    AssertThat(container, Is().EqualToContainer(expected));
  }

  it("should handle failing equals container");
  {
    const int e[] = {4, 2, 4};
    std::list<int> expected(e, e + sizeof(e) / sizeof(e[0]));

    AssertTestFails(Assert::That(container, EqualsContainer(expected)), "Expected: [ 4, 2, 4 ]");
  }

  it("should handle failing equals container");
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
