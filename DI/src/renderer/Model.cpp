#include "Model.hpp"
#include "Buffer.hpp"


namespace DI{
   
	void ModelHandler::Load(Model& model,std::string path){
   		Assimp::Importer importer;
   		const aiScene *scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs);

   		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      		DI_LOG_ERROR("ERROR::ASSIMP::{0}",importer.GetErrorString());
      	else
      		DI_LOG_INFO("Loaded model, success.");
      	
    	processNode(model, scene->mRootNode, scene);
    }
    void ModelHandler::processNode(Model& model, aiNode *node, const aiScene *scene){
    	
   		for(unsigned int i = 0; i < node->mNumMeshes; i++){
      		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
      		model.meshes.push_back(processMesh(mesh, scene));
   		}
   		// then do the same for each of its children
   		for(unsigned int i = 0; i < node->mNumChildren; i++){
      		processNode(model, node->mChildren[i], scene);
   		}
    }
    Ref<Mesh> ModelHandler::processMesh(aiMesh *mesh, const aiScene *scene){
		Ref<Mesh> m(new Mesh());

	   	//process vertecies data(pos, colors, normals, texcoord)
	   	m->verticies.count = mesh->mNumVertices * 8;
	   	m->verticies.data = new float[m->verticies.count];
	   	int counter = 0;
	   	for(unsigned int i = 0; i < mesh->mNumVertices; i++){
	   		static_cast<float*>(m->verticies.data)[counter]   = mesh->mVertices[i].x;
	      	static_cast<float*>(m->verticies.data)[counter+1] = mesh->mVertices[i].y;
	      	static_cast<float*>(m->verticies.data)[counter+2] = mesh->mVertices[i].z;
	      	static_cast<float*>(m->verticies.data)[counter+3] = mesh->mNormals[i].x;
	      	static_cast<float*>(m->verticies.data)[counter+4] = mesh->mNormals[i].y;
	      	static_cast<float*>(m->verticies.data)[counter+5] = mesh->mNormals[i].z;

	      	if (mesh->mTextureCoords[0]){
	      	   	static_cast<float*>(m->verticies.data)[counter+6] = mesh->mTextureCoords[0][i].x;
	      	   	static_cast<float*>(m->verticies.data)[counter+7] = mesh->mTextureCoords[0][i].y;
	        }
	      	counter += 8;
	   	}
	   	counter = 0;

	   	//process elements data
	   	m->elements.count = 0;
	   	for(unsigned int i = 0; i < mesh->mNumFaces; i++){
	      	aiFace face = mesh->mFaces[i];
	      	m->elements.count += face.mNumIndices;
	   	} 
	   	m->elements.data = new unsigned int[m->elements.count];
   		for(unsigned int i = 0; i < mesh->mNumFaces; i++){
      		aiFace face = mesh->mFaces[i];
      		for(unsigned int j = 0; j < face.mNumIndices; j++){
         		static_cast<unsigned int*>(m->elements.data)[counter] = face.mIndices[j];
         		counter++;
         	}
   		} 
   		counter = 0;

   		for (unsigned int i = 0; i < scene->mNumMaterials; i++){
   			
   		}
   		for (unsigned int i = 0; i < scene->mNumLights; i++){
   			
   		}
   		for (unsigned int i = 0; i < scene->mNumCameras; i++){
   			
   		}

	   	return m;
    }
  
} // namespace DI
