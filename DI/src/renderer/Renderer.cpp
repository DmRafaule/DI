#include "Renderer.hpp"


namespace DI{
	void RenderHandler::Draw(Mesh &mesh){
		glBindVertexArray(mesh.buffer.vao);
        glDrawElements(GL_TRIANGLES,mesh.elements.count,GL_UNSIGNED_INT,0);
	}
};