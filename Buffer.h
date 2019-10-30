// Buffer.h

#ifndef _Buffer_h_
#define _Buffer_h_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

class Buffer
{
public:
    void display() const;
    const std::string & file_name() const { return file_name_; }
    void move_to_next_page();
    void move_to_previous_page();
    bool move_to_searched_string(const std::string & str);
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height_ = h; }
    void set_window_width(int w) { window_width_ = w; }

private:
    std::string make_anchor(const std::string & anchor, const std::string & filename, const std::string & text);
    void format();

    std::vector<std::string> v_lines_;
    std::vector<std::string> v_words_;
    int ix_top_line_ = 0;
    std::string file_name_;
    int window_height_;
    int window_width_;

    std::vector<std::string> anchors_;
};

inline void Buffer::move_to_next_page()
{
    ix_top_line_ += window_height_;
    if (ix_top_line_ >= v_lines_.size())
        ix_top_line_ -= window_height_;
}

inline void Buffer::move_to_previous_page()
{
    ix_top_line_ -= window_height_;
    if (ix_top_line_ < 0)
        ix_top_line_ = 0;
}

#endif
