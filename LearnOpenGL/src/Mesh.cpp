#include "pch.h"
#include "Mesh.h"


	
	Mesh::Mesh() : m_VAO{}, m_VBO{}, m_IBO{}, m_IndexCount{}
	{}

	Mesh::~Mesh()
	{
		Clear();
	}

	void Mesh::Create(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
	{
		m_IndexCount = indices.size();

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		{
			glGenBuffers(1, &m_IBO);

			auto indexVectorSize = sizeof(GLfloat) * indices.size();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVectorSize, indices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &m_VBO);

			auto vertexVectorSize = sizeof(unsigned int) * vertices.size();
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexVectorSize, vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			// Unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
	}

	void Mesh::Create(GLfloat* vertices, int vSize, unsigned int* indices, int iSize)
	{
		m_IndexCount = iSize;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		{
			glGenBuffers(1, &m_IBO);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * iSize, indices, GL_STATIC_DRAW);

			glGenBuffers(1, &m_VBO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vSize, vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			// Unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
	}

	void Mesh::Render()
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::Clear()
	{
		if (m_IBO != 0)
		{
			glDeleteBuffers(1, &m_IBO);
			m_IBO = 0;
		}

		if (m_VBO != 0)
		{
			glDeleteBuffers(1, &m_VBO);
			m_VBO = 0;
		}

		if (m_VAO != 0)
		{
			glDeleteVertexArrays(1, &m_VAO);
			m_VAO = 0;
		}

		m_IndexCount = 0;
	}
