
/**
 * TestAllocateObject
 */
class TestAllocateObject
{
public:
	enum Step 
	{
		None,
		New,
		Free
	};

	TestAllocateObject()
	{
		step = New;
	}

	~TestAllocateObject()
	{
		step = Free;
	}

public:
	static Step step;
};

TestAllocateObject::Step TestAllocateObject::step = TestAllocateObject::None;
