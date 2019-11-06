// FileViewer.cpp

#include "FileViewer.h"

using namespace std;

void FileViewer::display()
{
    const string long_separator(window_width_ + 7, '-');
    const string short_separator(8, '-');

    system(clear_command);

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  open  search  quit\n";
    cout << short_separator << endl;
}

void FileViewer::execute_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            buffer_.move_to_next_page();
            break;
        }

        case 'o': {
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);
            if (!buffer_.open(file_name))
                error_message_ = "Could not open " + file_name;
            break;
        }

        case 'p': {
            buffer_.move_to_previous_page();
            break;
        }

        // Homework A4 solution
        case 's': {
            cout << "search string: ";
            string search_str;
            getline(cin, search_str);

            bool success = buffer_.move_to_searched_string(search_str);

            if (!success) {
                error_message_ = "string \"" + search_str + "\" was not found";
            }
            break;
        }

        case 'g': {
            cout << "link number: ";
            string link_str;
            cin >> link_str;
            istringstream in(link_str);
            unsigned int link_num;
            in >> link_num;

            if(!in)
            {
                error_message_ = "browser given invalid argument";
                break;
            }

            bool success = buffer_.go(link_num);

            if (!success){
                error_message_ = "attempted to access a nonexistent directory";
            }
            break;
        }

        case 'b': {

            bool success = buffer_.step_back();

            if (!success){
                error_message_ = "no previous history";
            }
            break;

        }

        case 'q': {
            done = true;
            break;
        }
    }
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cout << "Window width? ";
    cin >> window_width_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);
    buffer_.set_window_width(window_width_);

    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}


