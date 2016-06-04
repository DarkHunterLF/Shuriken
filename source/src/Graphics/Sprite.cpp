#include "Sprite.h"



Sprite::Sprite() : _vboID(0)
{
}


Sprite::~Sprite()
{
	if (!_vboID)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (!_vboID)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	vertexData[0].setPosition(_x, _y);
	vertexData[0].setUV(0.0f, 1.0f);

	vertexData[1].setPosition(_x + _width, _y);
	vertexData[1].setUV(1.0f, 1.0f);

	vertexData[2].setPosition(_x, _y + _height);
	vertexData[2].setUV(0.0f, 0.0f);

	vertexData[3].setPosition(_x + _width, _y);
	vertexData[3].setUV(1.0f, 1.0f);

	vertexData[4].setPosition(_x, _y + _height);
	vertexData[4].setUV(0.0f, 0.0f);

	vertexData[5].setPosition(_x + _width, _y + _height);
	vertexData[5].setUV(1.0f, 0.0f);


	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 255, 255, 255);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinds the GL_ARRAY_BUFFER as it is set to zero
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0); //Only using first element

	//Position attibute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // 0 = glEnableVertexAttribarray, 2 = elements of each point
	//Color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinds the GL_ARRAY_BUFFER as it is set to zero
}