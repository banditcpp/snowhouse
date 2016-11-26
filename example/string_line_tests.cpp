#include "tests.h"
using namespace snowhouse;

void StringLineTests()
{
  describe("StringLineTests");

  it("can assert that at least one line in a stream matches");
  {
    Assert::That("First line\n", Has().AtLeast(1).EqualTo("First line"));
  }

  it("can detect when assertion fails");
  {
    AssertTestFails(Assert::That("First line\n", Has().AtLeast(1).EqualTo("Second line")), "Expected: at least 1 equal to Second line");
  }

  it("can handle line missing newline");
  {
    Assert::That("First line", Has().AtLeast(1).EqualTo("First line"));
  }

  it("can handle several lines");
  {
    std::string lines = "First line\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }

  it("can handle windows line endings");
  {
    std::string lines = "First line\r\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(3).EndingWith("line"));
  }

  it("can match beginning of lines with windows line endings");
  {
    std::string lines = "First line\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(1).StartingWith("Second"));
  }

  it("can handle empty lines when using windows line endings");
  {
    std::string lines = "\r\nSecond line\r\n\r\n";
    Assert::That(lines, Has().Exactly(2).OfLength(0));
  }

  it("can handle last line missing newline for windows line endings");
  {
    std::string lines = "First line\r\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }

  it("can handle all empty lines");
  {
    Assert::That("\n\n\n\n\n\n", Has().Exactly(6).OfLength(0));
  }

  it("can handle all empty lines with windows line endings");
  {
    Assert::That("\r\n\r\n\r\n", Has().Exactly(3).OfLength(0));
  }


  describe("StringLineParserTests");

  it("can parse empty string");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("", res);

    Assert::That(res, HasLength(0));
  }

  it("can parse single line");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("Simple line", res);

    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("Simple line"));
  }

  it("can parse two lines");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("One line\nTwo lines", res);

    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("can parse three lines");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("One line\nTwo lines\nThree lines", res);

    Assert::That(res, HasLength(3));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
    Assert::That(res, Has().Exactly(1).EqualTo("Three lines"));
  }

  it("can handle string ending with newline");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\n", res);
    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
  }

  it("can handle single line with windows line ending");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\n", res);
    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
  }

  it("can handle two lines with windows line endings");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\nTwo lines", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("can handle empty line with newline");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\n", res);
    Assert::That(res, Is().OfLength(1).And().Exactly(1).OfLength(0));
  }

  it("can handle two empty lines");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\n\n", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(2).OfLength(0));
  }

  it("can handle two empty lines with windows line endings");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\r\n\r\n", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(2).OfLength(0));
  }

  it("can handle carriage return only");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\rTwo lines", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("can handle carriage return only at end of string");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\nTwo lines\r", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }
}
