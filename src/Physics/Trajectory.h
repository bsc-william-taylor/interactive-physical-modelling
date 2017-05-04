
#pragma once

#include "ProgramGL.h"
#include "MatrixGL.h"

class Trajectory
{
    ProgramGL* program;
    MatrixGL matrix;

    GLuint position;
    GLuint vertexArray;
    GLuint vertexBuffer;

    vector<vec2> positions;
    vec2 startPoint;
public:
    Trajectory();
    ~Trajectory();

    void plotPoint(int, int, float);
    void resetStart(float, float);
    void startFrom(int, int, float);
    void onRender();
    void clear();

    MatrixGL* getMatrix();
};