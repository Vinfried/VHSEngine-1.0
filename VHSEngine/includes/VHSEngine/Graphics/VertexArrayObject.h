#pragma once

#include "VHSEngine/CoreMinimal.h"

const PositionMatrix TrianglePositions{
	//x		//y		//z		//R	  //G   //B		tex coords
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //bottom left --- 0
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	//bottom right --- 1
	 0.0f,	 0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f	//top --- 2
};

const IndicesMatrix TriangleIndices{
	0, 1, 2
};

const PositionMatrix PolyPositions{
	//x		//y		//z		//R	  //G	//B		// tex coords
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,	//bottom left --- 0
	 0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f, //bottom right --- 1
	 0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f, //top right --- 2
	-0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f//top left --- 3

	};

const IndicesMatrix PolyIndices{
	
	/*Square*/

	0, 3, 2,	//triangle 1
	2, 1, 0		//triangle 2

};

const PositionMatrix CirclePositions{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,	//bottom left --- 0
	 0.5f,	-0.5f,	0.0f,	//bottom right --- 1
	 0.5f,	 0.5f,	0.0f,	//top right --- 2
	-0.5f,	 0.5f,	0.0f,	//top left --- 3
	 0.0f,	 0.75f,	0.0f,	//top --- 4
	 0.0f,	-0.75f,	0.0f,	//bottom --- 5
	 0.75f,	 0.0f,	0.0f,	//right --- 6
	-0.75f,	 0.0f,	0.0f	//left --- 7
};

const IndicesMatrix CircleIndices{
	
	/*Hexagon*/

	4, 3, 2,	//triangle 1
	3, 7, 2,	//triangle 2
	7, 6, 2,	//triangle 3
	7, 0, 6,	//triangle 4
	0, 1, 6,	//triangle 5
	0, 1, 5		//triangle 6
};

class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;

	//this is out version of unsigned int
	//ID - ID for the VAO
	//VAB - ID for the vertices
	//EAB - ID for the indices
	vhsuint ID, VAB, EAB;
};