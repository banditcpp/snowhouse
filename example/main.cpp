#include <snowhouse/snowhouse.h>

using namespace snowhouse;

#include "tests.h"

void BasicAssertions()
{
  std::cout << "================================================" << std::endl;
  std::cout << "    ASSERTIONS " << std::endl;
  std::cout << "================================================" << std::endl;

  std::cout << "ShouldHandleIntegerEquality" << std::endl;  
	{
		Assert::That(5, Is().EqualTo(5));		
	}
	
  std::cout << "ShouldDetectIntegerInequality" << std::endl;
	{
		AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
	}
	
  std::cout << "ShouldDetectIfNotFails" << std::endl;
	{
		AssertTestFails(Assert::That(5, Is().Not().EqualTo(5)), "Expected: not equal to 5\nActual: 5\n");
	}
	
  std::cout << "ShouldHandleStrings" << std::endl;
	{
		Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
	}
	
  std::cout << "ShouldHandleStringsWithoutExplicitTemplateSpecialization" << std::endl;
	{
		Assert::That("kim", Is().EqualTo("kim"));
	}
	
  std::cout << "ShouldHandleGreaterThan" << std::endl;
	{
		Assert::That(5, Is().GreaterThan(4));
	}
	
  std::cout << "ShouldDetectWhenGreaterThanFails" << std::endl;
	{
		AssertTestFails(Assert::That(5, Is().GreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}
	
  std::cout << "ShouldHandleLessThan" << std::endl;
	{
		Assert::That(5, Is().LessThan(6));
	}
	
  std::cout << "ShouldDetectWhenLessThanFails" << std::endl;
	{
		AssertTestFails(Assert::That(6, Is().LessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}
	
  std::cout << "ShouldThrowExplicitFailureMessage" << std::endl;
	{
		AssertTestFails(Assert::Failure("foo"), "foo");
	}

  std::cout << "Should contain location information" << std::endl;
  {
    int line;
    std::string file;

    try
    {
      Assert::That(5, Equals(2), "filename", 32);
    }
    catch(const AssertionException& e)
    {
      line = e.GetLineNumber();
      file = e.GetFilename();
    }

    Assert::That(line, Equals(32));
    Assert::That(file, Equals("filename"));
  }

  std::cout << "================================================" << std::endl;
  std::cout << "    ASSERTIONS EXPRESSION TEMPLATES" << std::endl;
  std::cout << "================================================" << std::endl;

  std::cout << "ShouldHandleIntegerEquality" << std::endl;
	{
		Assert::That(5, Equals(5));
	}                                                            
	
  std::cout << "ShouldDetectIntegerInequality" << std::endl;
	{
		AssertTestFails(Assert::That(5, Equals(4)), "equal to 4");
	}
	
  std::cout << "ShouldDetectIfNotFails" << std::endl;
	{
		AssertTestFails(Assert::That(5, !Equals(5)), 
        "Expected: not equal to 5\nActual: 5\n");
	}
	
  std::cout << "ShouldHandleStrings" << std::endl;
	{
		Assert::That(std::string("joakim"), Equals(std::string("joakim")));
	}
	
  std::cout << "ShouldHandleStringsWithoutExplicitTemplateSpecialization" 
    << std::endl;
	{
		Assert::That("kim", Equals("kim"));
	}
	
  std::cout << "ShouldHandleGreaterThan" << std::endl;
	{
		Assert::That(5, IsGreaterThan(4));
	}
	
  std::cout << "ShouldDetectWhenGreaterThanFails" << std::endl;
	{
		AssertTestFails(Assert::That(5, IsGreaterThan(5)),
        "Expected: greater than 5\nActual: 5\n");
	}
	
  std::cout << "ShouldHandleLessThan" << std::endl;
	{
		Assert::That(5, IsLessThan(6));
	}
	
  std::cout << "ShouldDetectWhenLessThanFails" << std::endl;
	{
		AssertTestFails(Assert::That(6, IsLessThan(5)),
        "Expected: less than 5\nActual: 6\n");
	}
}

void BooleanOperators()
{
  std::cout << "================================================" << std::endl;
  std::cout << "   Boolean operators" << std::endl;
  std::cout << "================================================" << std::endl;

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

void ContainerConstraints();
void CustomMatchers();
void ExceptionTests();
void ExpressionErrorHandling();
void MapTests();
void OperatorTests();
void SequenceContainerTests();
void StringLineTests();
void StringTests();
void StringizeTests();

int main()
{
  try
  {
  BasicAssertions();
  BooleanOperators();
  ContainerConstraints();
  CustomMatchers();
  ExceptionTests();
  ExpressionErrorHandling();
  MapTests();
  OperatorTests();
  SequenceContainerTests();
  StringLineTests();
  StringTests();
  StringizeTests();
  }
  catch(const AssertionException& e)
  {
    std::cout << "Tests failed!" << std::endl;
    std::cout << e.GetMessage() << std::endl;
    return 1;
  }

  return 0;
}
