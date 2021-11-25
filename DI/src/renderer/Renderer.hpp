#pragma once

#include "Core.hpp"


namespace DI{

	class RenderHandler{
	public:
		static void Draw(Mesh &mesh);
	private:
		RenderHandler();
	};

};