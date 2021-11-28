#pragma once


namespace DI{
	
	struct Mesh;

	class RenderHandler{
	public:
		// Draw mesh using with "elements"
		static void DrawElements(Mesh &mesh);
		static void DrawArrays(Mesh &mesh);
	private:
		RenderHandler();
	};

};