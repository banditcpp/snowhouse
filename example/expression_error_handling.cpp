#include "tests.h"
using namespace snowhouse;

void ExpressionErrorHandling()
{
  describe("ExpressionErrorHandling");

  std::vector<int> collection;
  collection.push_back(1);
  collection.push_back(2);
  collection.push_back(3);

  it("should report an invalid all operation properly");
  {
    AssertTestFails(Assert::That(collection, Has().All()),
        "The expression after \"all\" operator does not yield any result");
  }

  it("should report an invalid at least operation properly");
  {
    AssertTestFails(Assert::That(collection, Has().AtLeast(2)),
        "The expression after \"at least 2\" operator does not yield any result");
  }

}
