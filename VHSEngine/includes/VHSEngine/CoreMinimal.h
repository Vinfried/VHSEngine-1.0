#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vhsuint;

//class/type definitions
class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;
typedef vector<VAOPtr> VAOStack;

class Texture;
typedef shared_ptr<Texture> TexturePtr;
typedef vector<TexturePtr> TexturePtrStack;


class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

typedef vector<float> PositionMatrix;
typedef vector<vhsuint> IndicesMatrix;

//this structure will handle matrices for VAOs
struct ShapeData {
	vector<float> PositionMatrix;
	vector<vhsuint> IndicesMatrix;
};


//a list of the geometric shapes available in VAO
enum class GeometricShapes {
	Triangle = 0,
	Polygon, 
	Circle,

};

//store the parameter required to create a shader program
struct VFShaderParams {
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

//the types of shader that can be accepted in out shader program
enum class ShaderTypes {
	Vertex = 0,
	Fragment
};