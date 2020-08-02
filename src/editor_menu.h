#pragma once
#include "headers.h"
#include "gametile.h"

#ifndef editor_menu_h
#define editor_menu_h

class EditorMenu{
    public:
        bool hide_lower_options = false;
        bool edit_texture_window = false;
        EditorMenu(int *, int *, ImVec4 *, Pointer *, map<string, string> *, TextureCache *);
        ~EditorMenu();
        void Process(GameTile * &ghost_tile, map<string, vector<GameTile *>> * tile_cache);

        string current_item = "";
    private:
        bool show_item_menu = false;
        float alpha = 1.0f;
        bool hide_stats = false;
        bool align_menu_to_screen = true;
        bool about_window = false;
        bool instruction_manual = false;
        int * window_width;
        int * window_height;
        ImVec4 * clear_color;
        Pointer * mouse;
        map<string, SDL_Texture *> * tile_list;
        vector<vector<string>> tile_paths;
        ImVec4 original_button_color;
        TextureCache * cache;
        SDL_Renderer * renderer;
        GameTile * selected_tile;
        map<string, vector<GameTile *>> block_cache;
};
#endif