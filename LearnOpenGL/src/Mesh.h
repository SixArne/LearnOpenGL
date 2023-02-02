#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>



class Mesh
{
public:
		
	Mesh();
	~Mesh();

	void Create(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
	void Create(GLfloat* vertices, int vSize, unsigned int* indices, int iSize);
	void Render();
	void Clear();

private:
	GLuint m_VBO{};
	GLuint m_VAO{};
	GLuint m_IBO{};
	GLsizei m_IndexCount{};
};




#endif


