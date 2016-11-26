#include "tests.h"
using namespace snowhouse;

void MapTests()
{
  describe("MapContaining");

  std::map<std::string, int> ages;
  ages["joakim"] = 38;
  ages["maria"] = 36;
  ages["hanna"] = 6;
  ages["moa"] = 4;

  it("should determine if key exists");
  {
    Assert::That(ages, Is().Containing("joakim"));
  }

  it("should give a proper message when fails");
  {
    AssertTestFails(Assert::That(ages, Is().Not().Containing("hanna")),
        "Expected: not contains hanna");
  }

  it("should determine if key exists");
  {
    Assert::That(ages, Contains("joakim"));
  }

  it("should give a proper message when containing fails");
  {
    AssertTestFails(Assert::That(ages, !Contains("hanna")),
        "Expected: not contains hanna");
  }
}
