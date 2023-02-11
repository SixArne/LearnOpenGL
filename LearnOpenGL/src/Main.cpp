#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION

#include <VLD/vld.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// CUSTOM
#include "Mesh.h"
#include "Shader.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Texture.h"
#include "Light.h"

const float toRadians = 3.14159265f / 180.f;

Window mainWindow{};
std::vector<Mesh*> meshes{};
std::vector<Shader*> shaders{};

Texture brickTexture{};
Texture dirtTexture{};

Light mainLight{glm::vec3(1.f, 1.f, 1.f), 0.1f};

void CreateObjects()
{
	const std::vector<unsigned int> indices
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	const std::vector<GLfloat> vertices
	{
		// position				UV
		-1.f, -1.f, 0.f,		0.0f, 0.0f,
		0.f, -1.f, 1.f,			0.5f, 0.0f,
		1.f, -1.f, 0.f,			1.0f, 0.0f,
		0.f, 1.f, 0.f,			0.5f, 1.0f,
	};


	Mesh* obj = new Mesh();
	obj->Create(vertices, indices);

	meshes.push_back(obj);

	Mesh* obj2 = new Mesh();
	obj2->Create(vertices, indices);

	meshes.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();

	shader1->CreateFromFiles("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	shaders.push_back(shader1);
}

int main()
{
	mainWindow = Window(1280, 720);
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	// Initialize Logger
	L_CREATE();

	Camera::CameraCreateInfo createInfo{};
	createInfo.startPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	createInfo.startUp = glm::vec3(0.0f, 1.0f, 0.0f);
	createInfo.startYaw = -90.0f;
	createInfo.startPitch = 0.0f;
	createInfo.startMoveSpeed = 5.0f;
	createInfo.startTurnSpeed = 1.0f;

	Camera camera{createInfo};

	std::string brickSourceLocation{ "./src/Textures/brick.png" };
	brickTexture = Texture(brickSourceLocation);
	brickTexture.LoadTexture();

	std::string dirtSourceLocation{ "./src/Textures/dirt.png" };
	dirtTexture = Texture(dirtSourceLocation);
	dirtTexture.LoadTexture();

	brickTexture.UseTexture();

	float deltaTime{};

	GLuint uniformProjection{}, uniformModel{}, uniformView{}, uniformAmbientIntensity{}, uniformAmbientColor{};
	glm::mat4 projection{ glm::perspective(45.f, mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.f) };

	bool show_demo_window{ true };

	while (!mainWindow.GetShouldClose())
	{
		auto start = std::chrono::high_resolution_clock::now();

		// Get + Handle user input events
		glfwPollEvents();

		if (mainWindow.IsFocussed())
		{
			camera.KeyControl(mainWindow.GetKeys(), deltaTime);
			camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaders[0]->UseShader();
		uniformModel = shaders[0]->GetModelLocation();
		uniformProjection = shaders[0]->GetProjectionLocation();
		uniformView = shaders[0]->GetViewLocation();
		uniformAmbientIntensity = shaders[0]->GetAmbientIntensityLocation();
		uniformAmbientColor = shaders[0]->GetAmbientColorLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor);

		glm::mat4 model{1.0f};
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		brickTexture.UseTexture();
		meshes[0]->Render();

		model = glm::mat4{ 1.0f };
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(-0.4f, 0.4f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		dirtTexture.UseTexture();
		meshes[1]->Render();
		glUseProgram(0);

		mainWindow.SwapBuffers();

		auto end = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
	}

	for (auto mesh : meshes)
	{
		delete mesh;
	}

	for (auto shader : shaders)
	{
		delete shader;
	}

	return 0;
}