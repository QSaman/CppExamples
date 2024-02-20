struct S
{
	int a;
	S() : a(7)
	{
	}

	void inc()
	{
		++a;
	}
	int getA()
	{
		return a;
	}
};

void f(int a)
{
	++a;
}

int main()
{
	S s;
	s.inc();
	int a = s.getA();
	++a;
	a++;
	f(a);
} 
