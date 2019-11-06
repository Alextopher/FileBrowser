// Buffer.cpp

#include "Buffer.h"

using namespace std;

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
        if (i < v_lines_.size())
            cout << setw(6) << i+1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    ifstream file(new_file_name);
    if (!file)
        return false;

    v_words_.clear();
    v_lines_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.

    string line;
    while (getline(file, line)) {
        istringstream in = istringstream(line);
        string word;
        while (in >> word) {
            cout << word << ",";
            v_words_.push_back(word);
        }
    }

    this -> format();

    file_name_ = new_file_name;

    if(history_.empty())
    {
       history_.push(file_name_);
    }

    ix_top_line_ = 0;
    return true;
}

void Buffer::format()
{
    string f_line;
    for (int i = 0; i < v_words_.size(); i++) {
        string word = v_words_[i];

        if(word == string("<a"))
        {
            word = make_anchor(v_words_[i], v_words_[i + 1], v_words_[i + 2]);
            i += 2;
        }
        else if(word == string("<p>"))
        {
            v_lines_.push_back(f_line);
            f_line = "";
            v_lines_.push_back(f_line); // Blank line
            word = "";
        }
        else if(word == string("<br>"))
        {
            v_lines_.push_back(f_line);
            f_line = "";
            word = "";
        }
        else
        {
            word += " ";
        }

        if (f_line.size() + word.size() > window_width_) {
            v_lines_.push_back(f_line);
            f_line = "";
        }

        f_line += word;
    }
    // Push the last line
    v_lines_.push_back(f_line);
}

string Buffer::make_anchor(const string & anchor, const string & filename, const string & text)
{
    anchors_.push_back(filename);
    ostringstream ss;
    ss << "<" << text << "[" << anchors_.size() << "] ";

    return ss.str();
}

// Homework A4 solution
bool Buffer::move_to_searched_string(const string & str)
{
    for (int i = ix_top_line_; i < v_lines_.size(); i++) {
        if (v_lines_[i].find(str) != string::npos) {
            ix_top_line_ = i;
            return true;
        }
    }
    return false;
}

bool Buffer::go(const unsigned int & location)
{
    if(!(location < (anchors_.size() + 1)))
    {
        return false;
    }

    history_.push(anchors_[location-1]);
    file_name_ = anchors_[location-1];
    open(file_name_);
    return true;
}

bool Buffer::step_back()
{
    if(history_.size() == 1)
    {
        return false;
    }

    history_.pop();
    file_name_ = history_.top();
    open(file_name_);
    return true;
}
