#include "WeightedGraph.h"
#include "Program.h"

int main(int argc, char** argv)
{
	Program p = Program(argv[1], argv[2]);
	try
	{
		p.executeProgram();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();

		ofstream myfile;
		myfile.open(argv[2]);
		if (e.what() == Error::NO_MST) {
			myfile.open(argv[2], ios::ate);
			myfile << e.what() << endl;
		}
		else {
			myfile.open(argv[2]);
			myfile << e.what() << endl;
		}
		myfile.close();
	}

}