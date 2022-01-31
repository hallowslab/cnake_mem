#include <pybind11/pybind11.h>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main(char* procID, int address, int newValue) {

	DWORD pID = atoi(procID);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);


	if (handle == NULL) {
		return 1;
	} else {
		LPVOID mem_addr = (LPVOID)address;
		cout << "address: " << address << "\n";
		cout << "mem_addr: " << mem_addr << "\n";
		WriteProcessMemory(handle, mem_addr, &newValue, sizeof(newValue), 0);
	}

	return 0;
}

namespace py = pybind11;

PYBIND11_MODULE(c_writter, m) {
	m.doc() = "pybind11 memory writter plugin"; // optional module docstring

	m.def("writter", &main, "A function that writes to process memory");
}