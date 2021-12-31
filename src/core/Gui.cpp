#include "Gui.hpp"
#include "App.hpp"
#include "Win.hpp"
#include "Texture.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <SDL.h>

namespace DI{

Scope<DI::GUIData> _guiData;
extern Scope<DI::WinData> _winData;
extern Scope<DI::AppData> _appData;
extern Scope<DI::DebugData> _debugData;

void GUIHandler::Init(GUIData& data){
    
    DI_LOG_TRACE("GUIHandler say: Init GUI.");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    data.mainViewport_pos = glm::vec2(0.0f,0.0f);
    data.mainViewport_size = glm::vec2(100.0f,100.0f);
    data._resize_now = ImGuiWindowFlags_None;
    data._mainDoc_pos = 0;
    data._mainDoc_min = 300;
    data._airline_min = 30;
    data._header_min  = 30;
    data.layouts.push_back("left handled");
    data.layouts.push_back("right handled(in dev)");
    data.layouts.push_back("top minimal(in dev)");
    data.layouts.push_back("bottom minimal(in dev)");
    data.flags_minimal = C_Scope<ImGuiWindowFlags>();
    data.flags_moveable = C_Scope<ImGuiWindowFlags>();
    data.flags_tab_to_win = C_Scope<ImGuiWindowFlags>();
    *data.flags_minimal = (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
    *data.flags_moveable = (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );
	*data.flags_tab_to_win  = (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings |  ImGuiWindowFlags_NoDocking);
    data.io = &ImGui::GetIO();
    data.io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Quicksand-VariableFont_wght.ttf",16);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/BebasNeue-Regular.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Inconsolata-VariableFont.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/IndieFlower-Regular.ttf",24);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Orbitron-VariableFont_wght.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/PressStart2P-Regular.ttf",15);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Righteous-Regular.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Rock3D-Regular.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/Shizuru-Regular.ttf",20);
    data.io->Fonts->AddFontFromFileTTF( "res/fonts/SigmarOne-Regular.ttf",20);
	data.io->Fonts->AddFontFromFileTTF( "res/fonts/TwinkleStar-Regular.ttf",20);
    ImGui::StyleColorsDark();
  
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(_winData->win, (void*)_winData->context);
    ImGui_ImplOpenGL3_Init("#version 130");
}
void GUIHandler::Kill(GUIData& data){
	DI_LOG_TRACE("GUIHandler say: Kill GUI.");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
void GUIHandler::Update(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
     
    updateHeader();
    updateMainDoc();
    updateAirline();
    updateMainViewport();
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void GUIHandler::EventsUpdate(GUIData& data, SDL_Event& event){
    ImGui_ImplSDL2_ProcessEvent(&event);
}
void GUIHandler::ViewportUpdate(GUIData& data){
    data.mainViewport_pos.x = data.MainDocSize.x;
    data.mainViewport_pos.y = data.MainDocPos.y;
    data.mainViewport_size.x = _winData->size.x - data.MainDocSize.x;
    data.mainViewport_size.y = _winData->size.y - (data.AirlineSize.y + data.HeaderSize.y);
    glViewport(data.mainViewport_pos.x,data.mainViewport_pos.y, data.mainViewport_size.x, data.mainViewport_size.y);
}
void GUIHandler::updateAirline(){
    _guiData->AirlineSize = glm::vec2(_winData->size.x,_guiData->_airline_min);
    _guiData->AirlinePos = glm::vec2(0,_winData->size.y - _guiData->_airline_min);
    ImGui::SetNextWindowSize( ImVec2(_guiData->AirlineSize.x,_guiData->AirlineSize.y ) );
    ImGui::SetNextWindowPos( ImVec2(_guiData->AirlinePos.x,_guiData->AirlinePos.y));
    ImGui::Begin("Airline", nullptr ,*_guiData->flags_minimal | _guiData->_resize_now);
    ImGui::End();
}
void GUIHandler::updateHeader(){
    _guiData->HeaderSize = glm::vec2(_winData->size.x, _guiData->_header_min );
    _guiData->HeaderPos = glm::vec2(0,0);
    ImGui::SetNextWindowSize( ImVec2(_guiData->HeaderSize.x,_guiData->HeaderSize.y ) );
    ImGui::SetNextWindowPos( ImVec2(_guiData->HeaderPos.x,_guiData->HeaderPos.y));
    ImGui::Begin("Header", NULL ,*_guiData->flags_minimal | _guiData->_resize_now);
    // Session
    if (ImGui::Button("Session"))
        ImGui::OpenPopup("session_popup");
    ImGui::SameLine();
    if (ImGui::BeginPopup("session_popup")){
        if (ImGui::Selectable("export")){

        }
        if (ImGui::Selectable("import")){
                       
        }
        if (ImGui::Selectable("quit")){
            _winData->isOpen = false;          
        }
        ImGui::EndPopup();
    }
    // Preferences
    ImGui::SameLine();
    if (ImGui::Button("Preferences"))
        ImGui::OpenPopup("settings_popup");
    ImGui::SameLine();
    if (ImGui::BeginPopup("settings_popup")){
        if (ImGui::BeginMenu("window")){
                if (ImGui::Selectable("fullscreen")) {
                    if (!_guiData->isFullscreen){
                        _guiData->isFullscreen = true;
                        SDL_DisplayMode dm;
                        SDL_GetDesktopDisplayMode(0,&dm);
                        glViewport(0,0,dm.w,dm.h);
                        SDL_SetWindowFullscreen(_winData->win,SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                    else {
                        _guiData->isFullscreen = false;
                        SDL_SetWindowFullscreen(_winData->win,0);
                    }
                }
                if (ImGui::Selectable("hide all docs")) {
                    _guiData->isHideAllDocs = true;
                    _guiData->_mainDoc_pos = -30;
                    _guiData->_mainDoc_min = 1;
                    _guiData->_airline_min = 1;
                    _guiData->_header_min  = 1;
                    _guiData->_resize_now = ImGuiWindowFlags_AlwaysAutoResize;
                }
                ImGui::EndMenu();
            }
        if (ImGui::BeginCombo("layout",_guiData->current_layout.c_str())){
            for (int n = 0; n < _guiData->layouts.size(); n++){
                if (ImGui::Selectable(_guiData->layouts[n].c_str())){
                    _guiData->current_layout = _guiData->layouts[n];
                }
            }
            ImGui::EndCombo();
        }
        ImFont* font_current = ImGui::GetFont();
        if (ImGui::BeginCombo("font",font_current->GetDebugName())){
            for (int n = 0; n < _guiData->io->Fonts->Fonts.Size; n++){
                ImFont* font = _guiData->io->Fonts->Fonts[n];
                ImGui::PushID((void*)font);
                if (ImGui::Selectable(font->GetDebugName(), font == font_current))
                    _guiData->io->FontDefault = font;
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }
        ImGui::EndPopup();
    }
    // About
    ImGui::SameLine();
    if (ImGui::Button("About"))
        ImGui::OpenPopup("about_popup");
    ImGui::SameLine();
    if (ImGui::BeginPopup("about_popup")){
        
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.14f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(198.0f/360.f, 0.31f, 0.07f, 1.0f));
        if (ImGui::Button("WhoAmI"))
            ImGui::OpenPopup("WhoAmI");
        ImGui::PopStyleColor(3);
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("WhoAmI", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            ImGui::Text("I'm guy who just love some neat graphycs stuff.\nAlso I love make games and learn math using programms and coding.\n\n");
            ImGui::Separator();
            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.14f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(198.0f/360.f, 0.31f, 0.07f, 1.0f));
        if (ImGui::Button("ContactMe"))
            ImGui::OpenPopup("ContactMe");
        ImGui::PopStyleColor(3);                       
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("ContactMe", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            ImGui::Text("Email: ChedrDen@gmail.com");
            ImGui::Separator();
            ImGui::Text("Tweeter: @ChedrDen");
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.14f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(198.0f/360.f, 0.3f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(198.0f/360.f, 0.31f, 0.07f, 1.0f));
        if (ImGui::Button("WhatIsThis"))
            ImGui::OpenPopup("WhatIsThis");
        ImGui::PopStyleColor(3);                       
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("WhatIsThis", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            ImGui::Text("This is my custom graphycs engine using for learning purpoces and just for fun.");
            ImGui::Spacing();
            ImGui::Text("For now this engine support:\n");
            ImGui::BulletText("\tAll exported types of models (from Blender)");
            ImGui::BulletText("\tSimple material system");
            ImGui::Spacing();
            ImGui::Text("In the future it will support:\n");
            ImGui::BulletText("\tEditing models");
            ImGui::BulletText("\tBuild in, shader whriter");
            ImGui::BulletText("\tScripting (on python and c++)");
            ImGui::BulletText("\tPhysict (Bullet physics engine)");
            ImGui::BulletText("\tMultiwindow support");
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}
void GUIHandler::updateMainDoc(){
    _guiData->MainDocPos = glm::vec2(_guiData->_mainDoc_pos,_guiData->_airline_min);
    int index_dranddr = 0;
    ImGui::SetNextWindowPos( ImVec2(_guiData->MainDocPos.x,_guiData->MainDocPos.y));
    ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
    ImGui::SetNextWindowSizeConstraints(ImVec2( _guiData->_mainDoc_min, _winData->size.y - _guiData->_airline_min*2),    ImVec2(_winData->size.x/2, _winData->size.y - _guiData->_airline_min*2)); 
    ImGui::Begin("MainDoc", nullptr ,*_guiData->flags_minimal ^ ImGuiWindowFlags_NoResize ^ ImGuiWindowFlags_NoDocking | _guiData->_resize_now );//disable (to 0) resize flag from data.flags_minimar
    _guiData->MainDocSize = glm::vec2( ImGui::GetWindowSize().x - _guiData->_mainDoc_pos * (-1), ImGui::GetWindowSize().y );
    ImGuiID dockspace_id = ImGui::GetID("MainDoc");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_Reorderable ;
    if (!_guiData->isHideAllDocs && ImGui::BeginTabBar("MyTabBar", tab_bar_flags)){
        if (!_guiData->tab_to_win_status.isFileMan && ImGui::BeginTabItem("FileSystem")){
            _guiData->_resize_now = ImGuiWindowFlags_None;
            _guiData->_mainDoc_min = 300;
            if (ImGui::BeginDragDropSource()){
                ImGui::SetDragDropPayload("FILEMANAGER_WIN",nullptr,0);
                ImGui::Text("FileManager");
                ImGui::EndDragDropSource();
            }
            updateFileSys();
            ImGui::EndTabItem();
        }
        if (!_guiData->tab_to_win_status.isEntityMan && ImGui::BeginTabItem("Entities")){
            _guiData->_resize_now = ImGuiWindowFlags_None;
            _guiData->_mainDoc_min = 300;
            if (ImGui::BeginDragDropSource()){
                ImGui::SetDragDropPayload("ENTITIES_WIN",nullptr,0);
                ImGui::Text("EntitiesManager");
                ImGui::EndDragDropSource();
            }
            //updateEntities();    
            ImGui::EndTabItem();
        }
        if (!_guiData->tab_to_win_status.isConsoleMan && ImGui::BeginTabItem("Console")){
            _guiData->_resize_now = ImGuiWindowFlags_None;
            _guiData->_mainDoc_min = 300;
            if (ImGui::BeginDragDropSource()){
                ImGui::SetDragDropPayload("CONSOLE_WIN",nullptr,0);
                ImGui::Text("ConsoleManager");
                ImGui::EndDragDropSource();
            }
            updateConsole();
            ImGui::EndTabItem();
        }
        if (!_guiData->tab_to_win_status.isScriptMan && ImGui::BeginTabItem("Scripting")){
            _guiData->_resize_now = ImGuiWindowFlags_None;
            _guiData->_mainDoc_min = 300;
            if (ImGui::BeginDragDropSource()){
                ImGui::SetDragDropPayload("SCRIPT_WIN",nullptr,0);
                ImGui::Text("ScriptManager");
                ImGui::EndDragDropSource();
            }
            //updateEntities();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if ((_guiData->tab_to_win_status.isFileMan && 
        _guiData->tab_to_win_status.isEntityMan && 
        _guiData->tab_to_win_status.isConsoleMan &&
        _guiData->tab_to_win_status.isScriptMan) && !_guiData->isHideAllDocs){
        _guiData->_mainDoc_min = 10;
        _guiData->_resize_now = ImGuiWindowFlags_AlwaysAutoResize;
    }

    ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
    ImGui::DockBuilderAddNode(dockspace_id,ImGuiWindowFlags_None ); // Add empty node

    ImGuiID right;
    ImGuiID left;

    ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.7f, &right, &left);
    ImGui::DockBuilderDockWindow("ImageView", right);
    ImGui::DockBuilderDockWindow("ImportView", left);

    ImGui::DockBuilderFinish(dockspace_id);

    ImGui::End();
}
void GUIHandler::updateMainViewport(){

    ViewportUpdate(*_guiData);
    ImGui::SetNextWindowSize( ImVec2(_guiData->mainViewport_size.x,_guiData->mainViewport_size.y ) );
    ImGui::SetNextWindowPos( ImVec2(_guiData->mainViewport_pos.x,_guiData->mainViewport_pos.y));
    ImGui::Begin("viewport",NULL,*_guiData->flags_moveable | ImGuiWindowFlags_NoBackground);
    // Where to drop drag and drops stuff
    ImGui::Image(0,ImGui::GetWindowSize(),ImVec2(0, 0),ImVec2(1, 1),ImVec4(0, 0, 0, 0));
    if (ImGui::BeginDragDropTarget()){
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MODEL_ON")){
            std::string path((char*)payload->Data,payload->DataSize);
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_ON")){
            std::string path((char*)payload->Data,payload->DataSize);
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_ON")){
            std::string path((char*)payload->Data,payload->DataSize);
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCRIPT_ON")){
            std::string path((char*)payload->Data,payload->DataSize);
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILEMANAGER_WIN")){
            _guiData->tab_to_win_status.isFileMan = true;
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITIES_WIN")){
            _guiData->tab_to_win_status.isEntityMan = true;
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONSOLE_WIN")){
            _guiData->tab_to_win_status.isConsoleMan = true;
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCRIPT_WIN")){
            _guiData->tab_to_win_status.isScriptMan = true;
        }
        ImGui::EndDragDropTarget();
    }
    // Create button for undo hiding all docs
    if (_guiData->isHideAllDocs){
        ImGui::SetCursorPos(ImVec2(0,ImGui::GetWindowSize().y - 30 ));
        if (ImGui::Button("show docs")){
            _guiData->isHideAllDocs = false;
            _guiData->_mainDoc_pos = 0;
            _guiData->_mainDoc_min = 300;
            _guiData->_airline_min = 30;
            _guiData->_header_min  = 30;
            _guiData->_resize_now = ImGuiWindowFlags_None;
        }
    }
    ImGui::End();

    if (_guiData->tab_to_win_status.isFileMan){
        ImGui::SetNextWindowSize( ImVec2(250.0f,250.0f),ImGuiCond_Appearing);
        ImGui::SetNextWindowPos( ImVec2(_appData->mousePos.x,_appData->mousePos.y),ImGuiCond_Appearing);
        ImGui::Begin("File manager",&_guiData->tab_to_win_status.isFileMan,*_guiData->flags_tab_to_win);
        updateFileSys();
        ImGui::End();
    }
    if (_guiData->tab_to_win_status.isEntityMan){
        ImGui::SetNextWindowSize( ImVec2(250.0f,250.0f),ImGuiCond_Appearing);
        ImGui::SetNextWindowPos( ImVec2(_appData->mousePos.x,_appData->mousePos.y),ImGuiCond_Appearing);
        ImGui::Begin("Entities manager",&_guiData->tab_to_win_status.isEntityMan,*_guiData->flags_tab_to_win);
        ImGui::End();
    }
    if (_guiData->tab_to_win_status.isConsoleMan){
        ImGui::SetNextWindowSize( ImVec2(250.0f,250.0f),ImGuiCond_Appearing);
        ImGui::SetNextWindowPos( ImVec2(_appData->mousePos.x,_appData->mousePos.y),ImGuiCond_Appearing);
        ImGui::Begin("Console manager",&_guiData->tab_to_win_status.isConsoleMan,*_guiData->flags_tab_to_win | ImGuiWindowFlags_HorizontalScrollbar);
        updateConsole();
        ImGui::End();
    }
    if (_guiData->tab_to_win_status.isScriptMan){
        ImGui::SetNextWindowSize( ImVec2(250.0f,250.0f),ImGuiCond_Appearing);
        ImGui::SetNextWindowPos( ImVec2(_appData->mousePos.x,_appData->mousePos.y),ImGuiCond_Appearing);
        ImGui::Begin("Script manager",&_guiData->tab_to_win_status.isScriptMan,*_guiData->flags_tab_to_win);
        ImGui::End();
    }
}
void GUIHandler::updateFileSys(){
    if (ImGui::TreeNode(_guiData->current_folder.c_str())){
        for (auto & i : ListDirectory(_guiData->current_folder)){
            ImGui::SetNextItemOpen(false,ImGuiCond_Always);
            // Folders, they are contain something
            if (i.second.size() > 0){
                if (ImGui::TreeNode(i.first.c_str())){
                    _guiData->current_folder = _guiData->current_folder + "/" + i.first;
                    if (i.first == ".."){// Up to dir
                        _guiData->current_folder = _guiData->current_folder.substr(0,_guiData->current_folder.rfind("/"));
                        _guiData->current_folder = _guiData->current_folder.substr(0,_guiData->current_folder.rfind("/"));
                    }

                    ImGui::TreePop();
                }
            }
            // Files, they are contain nothing
            else{
                //Just mark useable files
                DragableRes type = DragableRes::NOTHING;
                ImVec4 color(1,1,1,1);
                for (const auto& j : std::vector<std::string>({"png","jpeg","jpg","obj","ply","dae","gltf","fbx","x3d","glb","stl","frag","vert","cpp","c","py"}) )
                    if (i.first.substr(i.first.rfind(".")+1) == j){
                        if (j == "png" || j == "jpeg" || j == "jpg"){
                            color = ImVec4(0.12f,1.0f,0.12f,1.0f);
                            type = DragableRes::TEXTURE;
                        }
                        else if (j == "obj" || j == "ply" || j == "dae" || j == "gltf" || j == "fbx" || j == "x3d" || j == "glb" || j == "stl"){
                            color = ImVec4(0.7529, 0.2431, 0.8117, 1.0f);
                            type = DragableRes::MODEL;
                        }
                        else if (j == "frag" || j == "vert"){
                            color = ImVec4(0.8117, 0.9411, 0.1803, 1.0f);
                            type = DragableRes::SHADER;
                        }
                        else if (j == "cpp" || j == "c" || j == "py"){
                            color = ImVec4(0.1411, 0.6823, 0.7019, 1.0f);
                            type = DragableRes::SCRIPT;
                        }
                        continue;
                    }
                ImGui::PushStyleColor(ImGuiCol_Text,color);
                ImGui::Selectable(i.first.c_str());
                ImGui::PopStyleColor();
                if (type != DragableRes::NOTHING){
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)){
                        // Send path to file
                        switch(type){
                            case DragableRes::MODEL:{
                                ImGui::SetDragDropPayload("MODEL_ON",std::string(_guiData->current_folder + "/" + i.first).c_str(),(_guiData->current_folder.size() + 1 + i.first.size()) * sizeof(char));
                                break;
                            }
                            case DragableRes::TEXTURE:{
                                ImGui::SetDragDropPayload("TEXTURE_ON",std::string(_guiData->current_folder + "/" + i.first).c_str(),(_guiData->current_folder.size() + 1 + i.first.size()) * sizeof(char));
                                break;
                            }
                            case DragableRes::SHADER:{
                                ImGui::SetDragDropPayload("SHADER_ON",std::string(_guiData->current_folder + "/" + i.first).c_str(),(_guiData->current_folder.size() + 1 + i.first.size()) * sizeof(char));
                                break;
                            }
                            case DragableRes::SCRIPT:{
                                ImGui::SetDragDropPayload("SCRIPT_ON",std::string(_guiData->current_folder + "/" + i.first).c_str(),(_guiData->current_folder.size() + 1 + i.first.size()) * sizeof(char));
                                break;
                            }
                        }
                        // Create preview
                        ImGui::Text(i.first.c_str());
                        ImGui::EndDragDropSource();
                    }
                }
            }
        }
        ImGui::TreePop();
    }
}
void GUIHandler::updateConsole(){
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_Reorderable ;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)){
        if (ImGui::BeginTabItem("Debug")){
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text("DI");
            ImGui::Separator();
            ImGui::Text("%d vertices, %d indices ", _guiData->io->MetricsRenderVertices, _guiData->io->MetricsRenderIndices);
            ImGui::Text("Active windows %d", _guiData->io->MetricsRenderWindows, _guiData->io->MetricsActiveAllocations);
            ImGui::Text("Active allocations %d", _guiData->io->MetricsActiveAllocations);
            ImGui::Separator();
            ImGui::Separator();
            ImGui::Text("App");
            ImGui::Separator();
            ImGui::Text("Common");
            ImGui::Text("OpenGL calls: %d",_debugData->counterDICalls);
            ImGui::Text("FPS: %g",1 / CoreTime::tic);
            ImGui::Text("In use");
            ImGui::Text("Scene verticies: %d\t Scene elements(indecies): %d",_debugData->counterDIVerticies_inUse,_debugData->counterDIElements_inUse);
            ImGui::Text("Scene meshes: %d",_debugData->counterDIMeshes_inUse);
            ImGui::Text("Scene models: %d",_debugData->counterDIModels_inUse);
            ImGui::Text("Scene textures: %d",_debugData->counterDITextures_inUse);
            ImGui::Text("Scene shaders: %d",_debugData->counterDIShaders_inUse);
            ImGui::Separator();
            ImGui::Text("In mem(all)");
            ImGui::Text("Scene verticies: %d\t Scene elements(indecies): %d",_debugData->counterDIVerticies_inMem,_debugData->counterDIElements_inMem);
            ImGui::Text("Scene meshes: %d",_debugData->counterDIMeshes_inMem);
            ImGui::Text("Scene models: %d",_debugData->counterDIModels_inMem);
            ImGui::Text("Scene textures: %d",_debugData->counterDITextures_inMem);
            ImGui::Text("Scene shaders: %d",_debugData->counterDIShaders_inMem);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Logs")){
            ImGuiTextFilter  filter;
            ImGui::SameLine();
            filter.Draw("Find",-50);
            if (filter.IsActive()){
                for (int i = 0; i < Log::_logData->buffer.size(); ++i){
                    if (Log::_logData->buffer[i].first.find(filter.InputBuf) != std::string::npos){
                        glm::vec4 col = Log::_logData->buffer[i].second;
                        ImGui::PushStyleColor(ImGuiCol_Text,ImVec4(col.r,col.g,col.b,col.a));
                        ImGui::TextUnformatted(Log::_logData->buffer[i].first.c_str());
                        ImGui::PopStyleColor();
                    }
                }
            }
            else{
                for (int i = 0; i < Log::_logData->buffer.size(); ++i){
                    glm::vec4 col = Log::_logData->buffer[i].second;
                    ImGui::PushStyleColor(ImGuiCol_Text,ImVec4(col.r,col.g,col.b,col.a));
                    ImGui::TextUnformatted(Log::_logData->buffer[i].first.c_str());
                    ImGui::PopStyleColor();
                }
            }
            // Set button stick to bottom
            ImGui::SetCursorPos(ImVec2(ImGui::GetScrollX(),ImGui::GetWindowSize().y - 30 + ImGui::GetScrollY()));
            ImGui::Separator();
            if (ImGui::ButtonEx("Clear"))//Make button on bottom 
                Log::_logData->buffer.clear();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
void GUIHandler::createImgButtom(const std::string path, glm::vec2 size, glm::vec4 bg_col, glm::vec4 tint_col){
    Scope<Texture> tx(new Texture());
    TextureHandler::Set(*tx,path); 
    ImTextureID my_tex_id = (void*)tx->id;
    int frame_padding = -1 ;                             // -1 == uses default padding (style.FramePadding)
    ImVec2 Isize;                     // Size of the image we want to make visible
    Isize.x = size.x;
    Isize.y = size.y;
    ImVec2 uv0 = ImVec2(0.0f, 0.0f);                        // UV coordinates for lower-left
    ImVec2 uv1 = ImVec2(Isize.x / tx->width, Isize.y / tx->height);// UV coordinates for (32,32) in our texture
    ImVec4 Ibg_col = ImVec4(bg_col.r,bg_col.g,bg_col.b,bg_col.a);         // Black background
    ImVec4 Itint_col = ImVec4(tint_col.r,tint_col.g,tint_col.b,tint_col.a);       // No tint
    if (ImGui::ImageButton(my_tex_id, Isize, uv0, uv1, frame_padding, Ibg_col, Itint_col))
        DI_LOG_TRACE("click");
}

}