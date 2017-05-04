
#include "ShaderManagerGL.h"
#include "Trajectory.h"

Trajectory::Trajectory() :
    position(0)
{
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0f);
}

Trajectory::~Trajectory()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
}

void Trajectory::plotPoint(int x, int y, float r)
{
    if (position + 1 < positions.size())
    {
        ++position;

        positions[position].x = (GLfloat)(x + r);
        positions[position].y = (GLfloat)(y + r);

        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * positions.size(), &positions[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
}

void Trajectory::startFrom(int x, int y, float r)
{
    auto vs = "data/shaders/Trajectory.vert";
    auto fs = "data/shaders/Trajectory.frag";

    program = ShaderManagerGL::get()->getShader(vs, fs);
    matrix.ortho(vec2(0, 1280), vec2(0, 720));
    startPoint = vec2(x + r, y + r);

    for (GLint i = 0; i < 800; i++)
    {
        positions.push_back(vec2(x + r, y + r));
    }
}

void Trajectory::resetStart(float x, float y)
{
    startPoint = vec2(x, y);

    for (GLint i = 0; i < 800; i++)
    {
        positions[i] = vec2(x + 5.0f, y + 5.0f);
    }
}

void Trajectory::onRender()
{
    program->use();
    program->setMatrix("Projection", matrix.getProjection());
    program->setMatrix("Model", matrix.getModel());
    program->setMatrix("View", matrix.getView());

    glUniform2fv(program->getUniform("Start"), 1, glm::value_ptr(startPoint));
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_LINE_STRIP, 0, position);
    glBindVertexArray(0);

    program->release();
}

void Trajectory::clear()
{
    position = 0;

    for (auto i = 0; i < 800; i++)
    {
        positions[i] = vec2(0, 0);
    }
}

MatrixGL* Trajectory::getMatrix()
{
    return &matrix;
}