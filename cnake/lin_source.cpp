#include <pybind11/pybind11.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/uio.h>


int main(int procID, int address, size_t newValue) {

    pid_t pID =  procID;
    std::cout << "pID " << pID << "\n";
    std::cout << "newValue " << newValue << "\n";
    std::cout << "newValue ssize_t " << (ssize_t) newValue << "\n";
    void* buf = &newValue;
    // int mem_addr = atoi (address);
    std::cout << "mem_addr " << (void*)address << "\n";
    

    struct iovec iovLocalAddressSpace[1];
    struct iovec iovRemoteAddressSpace[1];

    iovLocalAddressSpace[0].iov_base = buf; //Store data in this buffer
    std::cout << "This buffer: " << iovLocalAddressSpace[0].iov_base << "\n";
    iovLocalAddressSpace[0].iov_len = newValue; //which has this size.
    std::cout << "Has size: " << iovLocalAddressSpace[0].iov_len << "\n";

    iovRemoteAddressSpace[0].iov_base = (void*)address; //The data comes from here
    std::cout << "Remote buffer: " << iovRemoteAddressSpace[0].iov_base << "\n";
    iovRemoteAddressSpace[0].iov_len = newValue; //and has this size.
    std::cout << "Has size: " << iovRemoteAddressSpace[0].iov_len << "\n";

	ssize_t sSize = process_vm_writev(pID, //Remote process id
							iovLocalAddressSpace,  //Local iovec array
							1, //Size of the local iovec array
							iovRemoteAddressSpace,  //Remote iovec array
							1, //Size of the remote iovec array
							0); //Flags, unused
 
    std::cout << "sSize: " << sSize << "\n";

    if (sSize == (ssize_t) newValue) {
        //Success
        return 0;
    } else if (sSize == 0) {
        //Failure
        return 1;
    }

    //Partial read, data might be corrupted
    return 1;
}

namespace py = pybind11;

PYBIND11_MODULE(c_writter, m) {
	m.doc() = "pybind11 memory writter plugin"; // optional module docstring

	m.def("writter", &main, "A function that writes to process memory");
}