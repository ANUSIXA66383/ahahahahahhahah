#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

int main() {
    // Create a new session and process group
    if (setsid() < 0) {
        std::cerr << "Failed to create new session" << std::endl;
        return 1;
    }

    // Change the current working directory to the root directory
    if (chdir("/") < 0) {
        std::cerr << "Failed to change working directory to root" << std::endl;
        return 1;
    }

    // Close all open file descriptors
    for (int i = 0; i < 64; i++) {
        close(i);
    }

    // Open the system log
    openlog("daemon89", LOG_PID, LOG_DAEMON);

    // Monitor system events here
    while (true) {
        syslog(LOG_INFO, "Daemon89 is running...");
        sleep(1);
    }

    // Close the system log
    closelog();

    return 0;
}