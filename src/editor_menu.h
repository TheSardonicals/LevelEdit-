#pragma once
#include "headers.h"

#ifndef editor_menu_h
#define editor_menu_h

class EditorMenu{
    public:
        bool hide_lower_options = false;
        EditorMenu(int *, int *, ImVec4 *);
        ~EditorMenu();
        void Process();
    private:
        bool hide_stats = false;
        bool align_menu_to_screen = true;
        int * window_width;
        int * window_height;
        ImVec4 * clear_color;
};
#endif