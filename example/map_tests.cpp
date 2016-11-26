#include "tests.h"
using namespace snowhouse;

void MapTests()
{
  describe("Containing (std::map)");

  std::map<std::string, int> ages;
  ages["joakim"] = 38;
  ages["maria"] = 36;
  ages["hanna"] = 6;
  ages["moa"] = 4;

  it("determines if key exists");
  {
    Assert::That(ages, Is().Containing("joakim"));
  }

  it("gives a proper message when fails");
  {
    AssertTestFails(Assert::That(ages, Is().Not().Containing("hanna")),
        "Expected: not contains hanna");
  }

  it("determines if key exists");
  {
    Assert::That(ages, Contains("joakim"));
  }

  it("gives a proper message when Contains() fails");
  {
    AssertTestFails(Assert::That(ages, !Contains("hanna")),
        "Expected: not contains hanna");
  }
}
