#pragma once


namespace DI{
	
	struct Mesh;
	struct Model;
	struct Shader;

	// Control what and how to draw data to screen
	class RenderHandler{
	public:
		// Draw model
		static void Draw(Model &model,Shader& shader);
	private:
		// Drawing using elements
		static void DrawElements(Mesh &mesh);
		// Drawing using array
		static void DrawArrays(Mesh &mesh);
		RenderHandler();
	};

};