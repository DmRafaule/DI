#include "Renderer.hpp"
#include "Core.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Material.hpp"


namespace DI{

void RenderHandler::Draw(Model &model, Shader& shader){
	for (int i = 0; i < model.meshes.size(); ++i){
        DI::MaterialHandler::UseMaterial(*model.materials[i],shader);            
        DI::RenderHandler::DrawElements(*model.meshes[i]);
    }
}
void RenderHandler::DrawElements(Mesh &mesh){
	glBindVertexArray(mesh.buffer.vao);
    glDrawElements(GL_TRIANGLES,mesh.elements.count,GL_UNSIGNED_INT,0);
}
void RenderHandler::DrawArrays(Mesh &mesh){
	glBindVertexArray(mesh.buffer.vao);
    glDrawArrays(GL_TRIANGLES,0,mesh.elements.count);
}

};