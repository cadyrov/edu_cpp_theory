#include <WinINet.h>
#include <wil/resource.h>

int main() {
    auto wuh = wil::unique_handle ptr(OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId()););
}
