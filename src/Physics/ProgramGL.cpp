

#include "ProgramGL.h"

ProgramGL::ProgramGL()
{
}

ProgramGL::~ProgramGL()
{
}

void ProgramGL::outputLog(ShaderType type)
{
    GLint progress;
    glGetShaderiv(shaders[type], GL_COMPILE_STATUS, &progress);

    if (progress == GL_FALSE)
    {
        std::cout << "Errors with " << (type ? "Fragment " : "Vertex ") << "Shader" << std::endl;

        GLint Length = 0;
        glGetShaderiv(shaders[type], GL_INFO_LOG_LENGTH, &Length);
        GLchar* outputBuffer = new GLchar[Length + 1];
        glGetShaderInfoLog(shaders[type], Length, NULL, outputBuffer);
        std::cerr << outputBuffer << std::endl;
        delete[] outputBuffer;
    }
}

std::string ProgramGL::readTextFile(const std::string& fn)
{
    std::stringstream stringstream;
    std::ifstream inputFile(fn);

    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {
            std::string line = "";
            getline(inputFile, line);
            stringstream << line << std::endl;
        }

        inputFile.close();
    }

    return(stringstream.str());
}

GLvoid ProgramGL::setTexture(GLuint ID)
{
    glActiveTexture(GL_TEXTURE0 + ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glUniform1i(glGetUniformLocation(program, "sampler"), 0);
}

GLvoid ProgramGL::setMatrix(const std::string& name, mat4 m)
{
    auto matrix = getUniform(name);
    glUniformMatrix4fv(matrix, 1, false, glm::value_ptr(m));
}

void ProgramGL::create()
{
    program = glCreateProgram();
}

void ProgramGL::link()
{
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
    glLinkProgram(program);
}

void ProgramGL::load(ShaderType type, const std::string& filename)
{
    auto contents = readTextFile(filename);
    auto source = contents.c_str();

    filenames[type] = filename;
    shaders[type] = glCreateShader(!type ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    glShaderSource(shaders[type], 1, &source, NULL);
    glCompileShader(shaders[type]);
}

void ProgramGL::release()
{
    glUseProgram(0);
}

void ProgramGL::use()
{
    glUseProgram(program);
}

GLuint ProgramGL::getAttribute(const std::string& name)
{
    return glGetAttribLocation(this->program, name.c_str());
}

GLuint ProgramGL::getUniform(const std::string& name)
{
    return glGetUniformLocation(this->program, name.c_str());
}

const std::string& ProgramGL::getFS()
{
    return filenames[FragShader];
}

const std::string& ProgramGL::getVS()
{
    return filenames[VertexShader];
}


