#include "editor_menu.h"

EditorMenu::EditorMenu(SDL_Renderer * render, int * width, int * height, ImVec4 * clear_color, Pointer * _mouse, map<string, string> * paths, TextureCache * _cache){
    window_width = width;
    window_height = height;
    this->clear_color = clear_color;
    mouse = _mouse;
    renderer = render;

    tile_paths = paths;
    cache = _cache;
    original_button_color = ImGui::GetStyle().Colors[ImGuiCol_Button];

}

void EditorMenu::FillTileList(){
    map<string, SDL_Texture *> tiles;
    for (map<string, string>::iterator it = tile_paths->begin(); it != tile_paths->end(); it++){
        if (tiles.count(it->first) == 0){
            char cstr[it->second.size() + 1];
            strcpy(cstr, it->second.c_str());
            tiles[it->first] = cache->LoadTexture(cstr);
        }
    }
    tile_list = &tiles;
}

void EditorMenu::Process(){
    // Menu Bar with options and such
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("Save File", NULL, false)){
                //Save .mx file contents.
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Options")){
            ImGui::Checkbox("Hide Menu", &hide_lower_options);
            ImGui::Checkbox("Hide Stats", &hide_stats);
            ImGui::Checkbox("Align Menu to bottom corner", &align_menu_to_screen);
            ImGui::SliderFloat("Alpha", &alpha, 0.0f, 1.0f, "Alpha = %.3f");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Stats and information.
    if (!hide_stats){
        ImGui::SetNextWindowBgAlpha(alpha);
        if (ImGui::Begin("Stats")){
            ImGui::ColorEdit3("clear color", (float*)clear_color); // Edit 3 floats representing a color
            ImGui::NewLine();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);  
        }
        ImGui::End();
    }
    
    ImVec2 lower_menu_pos = ImVec2(*window_width - 265, *window_height - 55);
    // Menu for selecting tiles and saving, just like old times.
    if (!hide_lower_options){
        
        if (align_menu_to_screen){
            ImGui::SetNextWindowPos(lower_menu_pos);
        }
        ImGui::SetNextWindowBgAlpha(alpha);
        if (ImGui::Begin("Option Menu", NULL, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize)){
            if (ImGui::Button("Save File", ImVec2(120, 40))){
                // Save .mx file contents.
            }
            ImGui::SameLine();

            // Change button color if it's been clicked, else use original button color.
            if (show_item_menu){ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.46f, 0.47f, 0.48f, 1.00f));}
            else{ImGui::PushStyleColor(ImGuiCol_Button, original_button_color);}

            if (ImGui::Button("Assets", ImVec2(120, 40))){
                if (show_item_menu == false)
                    show_item_menu = true;
                else
                    show_item_menu = false;
                ImGui::SetNextWindowPos(ImVec2(lower_menu_pos.x - 40, lower_menu_pos.y - 400)); 
                ImGui::SetNextWindowSize(ImVec2(310, 400));  
            }

            ImGui::PopStyleColor(1);
        }
        ImGui::End();
    }
    
    if (show_item_menu){
        ImGui::SetNextWindowBgAlpha(max(alpha-.4f, .1f));
        if (ImGui::Begin("Asset Menu", NULL)){
            // Create Game Tile buttons and handle what happens when the buttons are clicked, etc... 
            for (map<string, SDL_Texture *>::iterator it = tile_list->begin(); it != tile_list->end(); it++){
                ImGui::ImageButton(it->second, ImVec2(32.0f, 32.0f), ImVec2(0.0f, 0.0f), ImVec2(32.0f, 32), -1, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            }
            
            
            
        }
        ImGui::End();
    }
}