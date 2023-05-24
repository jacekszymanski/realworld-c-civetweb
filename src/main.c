#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[]) {
  const char *cw_options[] = {
    "listening_ports", "8080",
    "request_timeout_ms", "2000",
    "error_log_file", "error.log",
    0
  };
}
