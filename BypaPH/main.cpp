#include <Windows.h>
#include "BypaPH.hpp"

#define TARGET_PROCESS 19880
#define ADDR_INT_TO_MANIPULATE (PVOID)0x28C2DFF724

using namespace std;

int main(int argc, char *argv[])
{
	auto bypass = new BypaPH(TARGET_PROCESS);

	int iReadFromTarget = 0;
	SIZE_T bytesRead = 0;

	// Read (safe IOCTL)
	iReadFromTarget = bypass->qRVM<int>(ADDR_INT_TO_MANIPULATE, &bytesRead);
	cout << dec << "iReadFromTarget = " << iReadFromTarget << " | bytesRead = " << bytesRead << endl;

	// Write
	int iWriteInTarget = 987654;
	SIZE_T bytesWritten = 0;
	const auto status = bypass->qWVM(ADDR_INT_TO_MANIPULATE, &iWriteInTarget, sizeof(iWriteInTarget), &bytesWritten);
	cout << "qWVM returned 0x" << hex << status << endl;

	// Read again (this time with the unsafe IOCTL)
	iReadFromTarget = bypass->qRVMu<int>(ADDR_INT_TO_MANIPULATE, &bytesRead);
	cout << dec << "iReadFromTarget = " << iReadFromTarget << " | bytesRead = " << bytesRead << endl;

	delete bypass;
	system("pause");
	return EXIT_SUCCESS;
}