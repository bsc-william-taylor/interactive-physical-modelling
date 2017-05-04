
#include "ShaderManagerGL.h"

ShaderManagerGL* ShaderManagerGL::instance = nullptr;

ShaderManagerGL::ShaderManagerGL()
{
}

ShaderManagerGL::~ShaderManagerGL()
{
    for (auto& program : programs)
    {
        SAFE_RELEASE(program);
    }

	programs.clear();
}

ProgramGL* ShaderManagerGL::getShader(const std::string& vs, const std::string& fs)
{
	for(auto& program : programs)
	{
		if(program->getVS() == vs && program->getFS() == fs)
		{
			return program;
		}
	}

	const auto program = new ProgramGL();
	program->create();
	program->load(VertexShader, vs);
	program->load(FragShader, fs);
	program->outputLog(VertexShader);
	program->outputLog(FragShader);	
	program->link();
	programs.push_back(program);
	return program;
}

ShaderManagerGL * ShaderManagerGL::get()
{
	if(instance == nullptr)
	{
		instance = new ShaderManagerGL();
	}

	return instance;
}