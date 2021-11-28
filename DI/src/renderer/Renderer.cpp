#include "Core.hpp"
#include "Renderer.hpp"
#include "Buffer.hpp"


namespace DI{

void RenderHandler::DrawElements(Mesh &mesh){
	glBindVertexArray(mesh.buffer.vao);
    glDrawElements(GL_TRIANGLES,mesh.elements.count,GL_UNSIGNED_INT,0);
}
void RenderHandler::DrawArrays(Mesh &mesh){
	glBindVertexArray(mesh.buffer.vao);
    glDrawArrays(GL_TRIANGLES,0,mesh.elements.count);
}

};