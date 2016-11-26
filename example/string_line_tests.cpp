#include "tests.h"
using namespace snowhouse;

void StringLineTests()
{
  describe("StringLineTests");

  it("CanAssertThatAtLeastOneLineInAStreamMatches");
  {
    Assert::That("First line\n", Has().AtLeast(1).EqualTo("First line"));
  }

  it("CanDetectWhenAssertionFails");
  {
    AssertTestFails(Assert::That("First line\n", Has().AtLeast(1).EqualTo("Second line")), "Expected: at least 1 equal to Second line");
  }

  it("CanHandleLineMissingNewline");
  {
    Assert::That("First line", Has().AtLeast(1).EqualTo("First line"));
  }

  it("CanHandleSeveralLines");
  {
    std::string lines = "First line\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }

  it("CanHandleWindowsLineEndings");
  {
    std::string lines = "First line\r\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(3).EndingWith("line"));
  }

  it("CanMatchBeginningOfLinesWithWindowsLineEndings");
  {
    std::string lines = "First line\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(1).StartingWith("Second"));
  }

  it("CanHandleEmptyLinesWhenUsingWindowsLineEndings");
  {
    std::string lines = "\r\nSecond line\r\n\r\n";
    Assert::That(lines, Has().Exactly(2).OfLength(0));
  }

  it("CanHandleLastLineMissingNewlineForWindowsLineEndings");
  {
    std::string lines = "First line\r\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }

  it("CanHandleAllEmptyLines");
  {
    Assert::That("\n\n\n\n\n\n", Has().Exactly(6).OfLength(0));
  }

  it("CanHandleAllEmptyLinesWithWindowsLineEndings");
  {
    Assert::That("\r\n\r\n\r\n", Has().Exactly(3).OfLength(0));
  }


  describe("StringLineParserTests");

  it("CanParseEmptyString");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("", res);

    Assert::That(res, HasLength(0));
  }

  it("CanParseSingleLine");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("Simple line", res);

    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("Simple line"));
  }

  it("CanParseTwoLines");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("One line\nTwo lines", res);

    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("CanParseThreeLines");
  {
    std::vector<std::string> res;

    StringLineParser::Parse("One line\nTwo lines\nThree lines", res);

    Assert::That(res, HasLength(3));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
    Assert::That(res, Has().Exactly(1).EqualTo("Three lines"));
  }

  it("CanHandleStringEndingWithNewline");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\n", res);
    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
  }

  it("CanHandleSingleLineWithWindowsLineEnding");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\n", res);
    Assert::That(res, HasLength(1));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
  }

  it("CanHandleTwoLinesWithWindowsLineEndings");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\nTwo lines", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("CanHandleEmptyLineWithNewline");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\n", res);
    Assert::That(res, Is().OfLength(1).And().Exactly(1).OfLength(0));
  }

  it("CanHandleTwoEmptyLines");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\n\n", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(2).OfLength(0));
  }

  it("CanHandleTwoEmptyLinesWithWindowsLineEndings");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("\r\n\r\n", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(2).OfLength(0));
  }

  it("CanHandleCarriageReturnOnly");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\rTwo lines", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }

  it("CanHandleCarriageReturnOnlyAtEndOfString");
  {
    std::vector<std::string> res;
    StringLineParser::Parse("One line\r\nTwo lines\r", res);
    Assert::That(res, HasLength(2));
    Assert::That(res, Has().Exactly(1).EqualTo("One line"));
    Assert::That(res, Has().Exactly(1).EqualTo("Two lines"));
  }
}
