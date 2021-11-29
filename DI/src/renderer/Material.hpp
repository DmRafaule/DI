#pragma once

#include "Core.hpp" 

namespace DI{

struct Shader;

enum NumArgs{
	ONE,
	TWO,
	THREE,
	FOUR
};
enum TypeArgs{
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4,
	FL,
	DOB,
	IN,
	UIN,
};

struct Material{
	Shader *shader;
	std::vector<std::pair<std::string,std::pair<TypeArgs,NumArgs>>> uniforms;
};


class MaterialHandler{
public:
private:
};

}