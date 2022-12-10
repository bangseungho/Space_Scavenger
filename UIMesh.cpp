#include "UIMesh.h"

Shader* UIMesh::uiShader = nullptr;

unsigned int UIMesh::ortho_projection;
unsigned int UIMesh::texture1_Location;

unsigned int UIMesh::modelLocation;
unsigned int UIMesh::vColorLocation;

UIMesh::UIMesh(Object* obj) : Mesh(obj)
{
	if (uiShader == nullptr)
	{
		uiShader = Shader::allProgram.find("UI")->second;
		ortho_projection = glGetUniformLocation(uiShader->program, "projectionTransform");
		texture1_Location = glGetUniformLocation(uiShader->program, "texture1");
	}
}

UIMesh::~UIMesh()
{
}

void UIMesh::MeshInit()
{
	VAO = new GLuint;
	VBO = new GLuint;
	EBO = new GLuint;

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		1, 0, 3,
		2, 1, 3,
	};

	glGenVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	glGenBuffers(1, VBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &my_texture);
	glBindTexture(GL_TEXTURE_2D, my_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �̹��� ������ ���ϸ� �Ųٷ� ����
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(image_file, &width, &height, &nrChannels, 0);

	// ���� ���� ���� ���߱�
	float ratio;
	if (width > height) {
		ratio = static_cast<float>(height) / width;
		object->transform.local->scale.y *= ratio;
	}
	else {
		ratio = static_cast<float>(width) / height;
		object->transform.local->scale.x *= ratio;
	}

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void UIMesh::Draw()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = ortho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
	glUniformMatrix4fv(ortho_projection, 1, GL_FALSE, value_ptr(projection));

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(object->transform.model));
	glUniform1i(texture1_Location, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, my_texture);

	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}