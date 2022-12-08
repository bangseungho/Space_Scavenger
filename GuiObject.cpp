#define STB_IMAGE_IMPLEMENTATION
#include "GuiObject.h"
#include "stb_image.h"

int GuiObject::Gui_ID_Count = 0;
unsigned int GuiObject::ortho_projection;
unsigned int GuiObject::texture1_Location;

unsigned int GuiObject::modelLocation;
unsigned int GuiObject::vColorLocation;

GuiObject::GuiObject() : transform(), color()
{
	id = Gui_ID_Count++;
	name = "UnName";

	isDraw = true;
	isActive = true;

	allGuiObject.push_back(this);

}

GuiObject::~GuiObject()
{
	allGuiObject.erase(remove(allGuiObject.begin(), allGuiObject.end(), this), allGuiObject.end());
}

void GuiObject::ReadImage(string _FileName)
{
	image_file = _FileName;

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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

	// 이미지 뒤집기 안하면 거꾸로 나옴
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(image_file.c_str(), &width, &height, &nrChannels, 0);

	// 가로 세로 비율 맞추기
	float ratio;
	if (width > height) {
		ratio = static_cast<float>(height) / width;
		transform.worldScale.y *= ratio;
	}
	else {
		ratio = static_cast<float>(width) / height;
		transform.worldScale.x *= ratio;
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

void GuiObject::Update()
{
}

void GuiObject::Init()
{

}

void GuiObject::ObjectDraw()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = ortho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
	glUniformMatrix4fv(ortho_projection, 1, GL_FALSE, &projection[0][0]);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transform.model));
	glUniform1i(texture1_Location, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, my_texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

mat4& GuiObject::SetMatrix()
{
	mat4 lModel = mat4(1.0);

	lModel = translate(lModel, transform.localPivot);
	lModel = translate(lModel, transform.localPosition);
	lModel = rotate(lModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));
	lModel = rotate(lModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	lModel = scale(lModel, transform.localScale);

	*transform.localModel = lModel;
	*transform.model = (*transform.worldModel) * (lModel);

	return *transform.model;
}

void GuiObject::SetActive(bool value)
{
	if (this->isActive == false && value == true)
		this->Enable();
	else if (this->isActive == true && value == false)
		this->Disable();

	this->isActive = value;
}
