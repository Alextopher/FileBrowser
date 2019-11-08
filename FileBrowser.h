// FileBrowser.h

#ifndef _FileBrowser_h_
#define _FileBrowser_h_

#include <cstdlib>
#include <iostream>
#include <string>

#include "Buffer.h"

const char clear_command[] = "cls"; // for Windows
//const char clear_command[] = "clear"; // for Linux and possibly Mac's

class FileBrowser
{
public:
    void run();

private:
    void display();
    void execute_command(char command, bool & done);

    Buffer buffer_;
    int window_height_;
    int window_width_;
    std::string error_message_;

    std::stack<std::string> history_;
};

#endif
