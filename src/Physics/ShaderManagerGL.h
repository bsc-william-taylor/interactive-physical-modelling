
#pragma once

#include "ProgramGL.h"

class ShaderManagerGL
{
	static ShaderManagerGL* instance;
	vector<ProgramGL*> programs;
public:
    ShaderManagerGL();
	~ShaderManagerGL();

	ProgramGL* getShader(const std::string&, const std::string&);

	static ShaderManagerGL* get();
};