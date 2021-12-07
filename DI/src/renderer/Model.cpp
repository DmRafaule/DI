#include "Model.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Renderer.hpp"


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
    void ModelHandler::Use(Model& model, Shader& shader){
    	for (int i = 0; i < model.meshes.size(); ++i){
            DI::MaterialHandler::UseMaterial(*model.materials[i],shader);            
            DI::RenderHandler::DrawElements(*model.meshes[i]);
        }
    }
    void ModelHandler::processNode(Model& model, aiNode *node, const aiScene *scene){
    	
   		for(unsigned int i = 0; i < node->mNumMeshes; i++){
      		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
      		model.meshes.push_back(processMesh(model,mesh, scene));
      		model.materials.push_back(processMaterial(model,mesh, scene));
   		}
   		// then do the same for each of its children
   		for(unsigned int i = 0; i < node->mNumChildren; i++){
      		processNode(model, node->mChildren[i], scene);
   		}
    }
    Ref<Mesh> ModelHandler::processMesh(Model& model, aiMesh *mesh, const aiScene *scene){
		Ref<Mesh> m(new Mesh());

	   	//process vertecies data(pos, colors, normals, texcoord)
	   	m->verticies.count = mesh->mNumVertices * 8;
	   	m->verticies.data = new float[m->verticies.count];
	   	int counter = 0;
	   	for(unsigned int i = 0; i < mesh->mNumVertices; i++){
	   		static_cast<float*>(m->verticies.data)[counter]   = mesh->mVertices[i].x;
	      	static_cast<float*>(m->verticies.data)[counter+1] = mesh->mVertices[i].y;
	      	static_cast<float*>(m->verticies.data)[counter+2] = mesh->mVertices[i].z;
	      	counter += 3;
	      	if (mesh->HasNormals()){//*.x3d have not normals
	      	   	static_cast<float*>(m->verticies.data)[counter] = mesh->mNormals[i].x;
	      	   	static_cast<float*>(m->verticies.data)[counter+1] = mesh->mNormals[i].y;
	      	   	static_cast<float*>(m->verticies.data)[counter+2] = mesh->mNormals[i].z;
	      		counter += 3;
	      	}
	      	if (mesh->mTextureCoords[0]){
	      	   	static_cast<float*>(m->verticies.data)[counter] = mesh->mTextureCoords[0][i].x;
	      	   	static_cast<float*>(m->verticies.data)[counter+1] = mesh->mTextureCoords[0][i].y;
	      		counter += 2;
	        }
	   	}
	   	counter = 0;

	   	// process elements(indicies) data
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

	   	return m;
    }
    Ref<Material> ModelHandler::processMaterial(Model& model, aiMesh *mesh, const aiScene *scene){
    	Ref<Material> m(new Material());
    	std::vector<Texture> textures;
    	
    	// proccess textures
   		if (mesh->mMaterialIndex >= 0){	// If mesh have materials
   			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];// Get material for mesh

   			// 1. diffuse maps
    		std::vector<Texture> diffuseMaps = processMaterialTextures(material, aiTextureType_DIFFUSE, "material.diffuse");
    		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  	  		// 2. specular maps
  	  		std::vector<Texture> specularMaps = processMaterialTextures(material, aiTextureType_SPECULAR, "material.specular");
   			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
   			// 3. normal maps
	        std::vector<Texture> normalMaps = processMaterialTextures(material, aiTextureType_HEIGHT, "material.normal");
	        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	        // 4. height maps
	        std::vector<Texture> heightMaps = processMaterialTextures(material, aiTextureType_AMBIENT, "material.height");
	        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}
   		for (int i = 0; i < textures.size(); ++i)
   			MaterialHandler::SetSampler(*m,textures[i]);

		return m;
    }

  	std::vector<Texture> ModelHandler::processMaterialTextures(aiMaterial *mat, aiTextureType type, std::string sampler){
	    // For now this function assume that all textures used by model in the same directory
	    std::vector<Texture> tx;
	    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
	        aiString str;
	        mat->GetTexture(type, i, &str);
	    	// Add check on already loaded textures
	        Texture tx_tmp;
	        std::string filep = std::string(str.C_Str());
	        filep = "res/models/" + filep;
	        DI::TextureHandler::Set(tx_tmp,filep);
	        tx_tmp.path = filep;
	        tx_tmp.sampler = sampler;
	        tx.push_back(tx_tmp);
	    }
	    return tx;
	}  
} // namespace DI


// NOTES:
/*
in processMaterialTextures func there is no check if texture already loaded
*/