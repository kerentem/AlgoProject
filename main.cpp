#include "WeightedGraph.h"
#include "Program.h"

int main(int argc, char** argv)
{
	Program* p = new Program(argv[1], argv[2]);
	try
	{
		p->executeProgram();
		delete p;
	}
	catch (const std::exception&)
	{
		cout << "exception";
	}

}