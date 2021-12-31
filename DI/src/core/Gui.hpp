#pragma once


#include "Core.hpp"
#include <SDL_events.h>

struct ImGuiIO;
typedef int ImGuiWindowFlags;

namespace DI{
	enum DragableRes : unsigned int{
		MODEL,
		SHADER,
		TEXTURE,
		SCRIPT,
		NOTHING,
	};
	struct DragableTab{
		bool isFileMan = false;
		bool isScriptMan = false;
		bool isConsoleMan = false;
		bool isEntityMan = false;
	};
	
	// Contain all data about UI
	struct GUIData{
		ImGuiIO *io;
		glm::vec2 mainViewport_pos;
		glm::vec2 mainViewport_size;
		glm::vec2 AirlineSize;
		glm::vec2 HeaderSize;
		glm::vec2 MainDocSize;
		glm::vec2 AirlinePos;
		glm::vec2 HeaderPos;
		glm::vec2 MainDocPos;
		Scope<ImGuiWindowFlags> flags_minimal;
		Scope<ImGuiWindowFlags> flags_moveable;
		Scope<ImGuiWindowFlags> flags_tab_to_win;
		ImGuiWindowFlags _resize_now;
		int _mainDoc_min;
		int _mainDoc_pos;
		int _airline_min;
		int _header_min;
		std::string current_folder = ".";
		std::string current_layout = "leftHandled";
		std::vector<std::string> layouts;
		DragableRes current_dragable_res;
		DragableTab tab_to_win_status;
		bool isFullscreen;
		bool isHideAllDocs;
		bool isAirlineOpen = true;
		bool isMainDocOpen = true;
	};
	// Transform and manipulate data
	class  GUIHandler{
	public:

		static void Init(GUIData& data);
		static void Kill(GUIData& data);
		static void ViewportUpdate(GUIData& data);
		static void EventsUpdate(GUIData& data, SDL_Event& event);
		static void Update();
	private:
		// Contain common info about project (FPS, GL calls etc)
		static void updateAirline();
		// Contain some window tweeks and configs
		static void updateHeader();
		// Can be resized horizontal an contain popable tabs for interacting
		static void updateMainDoc();
		static void updateFileSys();
		static void updateConsole();
		static void createImgButtom(const std::string path, glm::vec2 size, glm::vec4 bg_col, glm::vec4 tint_col);
		static void updateMainViewport();
		GUIHandler();
	};
};