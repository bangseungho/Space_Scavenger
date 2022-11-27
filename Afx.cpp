#include "Afx.h"

GLuint s_program;
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü

GLuint gui_s_program;
GLuint gui_vertexShader;
GLuint gui_fragmentShader;

char default_Cube[] = "Cube.obj";

int windowSize_W = 900;
int windowSize_H = 900;

double aspect_ratio = windowSize_W / windowSize_H;

bool isFullScreen = false;
bool isOnTimer = false;

int Time_Duration;

float PI = 3.14159265;

#pragma region VectorFuntion

Face operator-(const Face my, int other)
{
	Face result;
	result.a = my.a - other;
	result.b = my.b - other;
	result.c = my.c - other;
	return result;
}


Vector2 operator+ (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}

Vector2 operator+ (const Vector2 my, const int other)
{
	Vector2 result;
	result.x = my.x + other;
	result.y = my.y + other;

	return result;
}

Vector2 operator- (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x - other.x;
	result.y = my.y - other.y;

	return result;
}

Vector2 operator- (const Vector2 my, const int other)
{
	Vector2 result;
	result.x = my.x - other;
	result.y = my.y - other;

	return result;
}

Vector2 operator* (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x * other.x;
	result.y = my.y * other.y;

	return result;
}

Vector2 operator* (const Vector2 my, const int other)
{
	Vector2 result;
	result.x = my.x * other;
	result.y = my.y * other;

	return result;
}

Vector2 operator/ (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x / other.x;
	result.y = my.y / other.y;

	return result;
}

Vector2 operator/ (const Vector2 my, const int other)
{
	Vector2 result;
	result.x = my.x / other;
	result.y = my.y / other;

	return result;
}

ostream& operator<< (ostream& outputStream, const Vector2& my)
{
	cout << my.x << ", " << my.y;
	return outputStream;
}

Position2 operator+(const Position2 my, const Position2 other)
{
	Position2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}

ostream& operator<< (ostream& outputStream, const vec3& my)
{
	cout << my.x << ", " << my.y << ", " << my.z;
	return outputStream;
}

ostream& operator<< (ostream& outputStream, const Face& my)
{
	cout << my.a << ", " << my.b << ", " << my.c;
	return outputStream;
}

vec3 operator* (const vec3 my, const float other)
{
	vec3 result = my;
	result.x = my.x * other;
	result.y = my.y * other;
	result.z = my.z * other;

	return result;
}

vec3 operator/ (const vec3 my, const float other)
{
	vec3 result = my;
	result.x = my.x / other;
	result.y = my.y / other;
	result.z = my.z / other;

	return result;
}

bool operator== (const vec3 my, const float other)
{
	if (my.x != other) return false;
	if (my.y != other)return false;
	if (my.z != other)return false;

	return true;
}

vec2 StartMouse = vec2(0);

#pragma endregion


float RandomFloat(float first, float second)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomFloat(first, second);

	return randomFloat(gen);
}

#pragma region Defualt_Funtion

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	GLchar* gui_vertexSource;
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	vertexSource = filetobuf("Vertex.glsl");
	gui_vertexSource = filetobuf("GuiVertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	gui_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(gui_vertexShader, 1, (const GLchar**)&gui_vertexSource, 0);
	glCompileShader(gui_vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return;
	}

	GLint gui_result;
	GLchar gui_errorLog[512];
	glGetShaderiv(gui_vertexShader, GL_COMPILE_STATUS, &gui_result);
	if (!gui_result)
	{
		glGetShaderInfoLog(gui_vertexShader, 512, NULL, gui_errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << gui_errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	GLchar* gui_fragmentSource;
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("Fragment.glsl"); // �����׼��̴� �о����
	gui_fragmentSource = filetobuf("GuiFragment.glsl"); // �����׼��̴� �о����

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	gui_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);
	glShaderSource(gui_fragmentShader, 1, (const GLchar**)&gui_fragmentSource, 0);
	glCompileShader(gui_fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return;
	}

	GLint gui_result;
	GLchar gui_errorLog[512];
	glGetShaderiv(gui_fragmentShader, GL_COMPILE_STATUS, &gui_result);
	if (!gui_result)
	{
		glGetShaderInfoLog(gui_fragmentShader, 512, NULL, gui_errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << gui_errorLog << endl;
		return;
	}
}

void InitShader()
{
	GLint result;
	GLchar errorLog[512];

	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	s_program = glCreateProgram();
	gui_s_program = glCreateProgram();
	glAttachShader(s_program, vertexShader);
	glAttachShader(gui_s_program, gui_vertexShader);
	glAttachShader(s_program, fragmentShader);
	glAttachShader(gui_s_program, gui_fragmentShader);
	glLinkProgram(s_program);
	glLinkProgram(gui_s_program);
	glGetProgramiv(s_program, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(s_program, 512, NULL, errorLog);
		cerr << "ERROR: shader program ���� ����\n" << errorLog << endl;
		return;
	}
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(gui_vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(gui_fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(s_program);
	glUseProgram(gui_s_program);
}

void FrameTimer(int value)
{
	glutPostRedisplay();
}


void ReadObj(char* fileName, VertexBlock& block)
{
	FILE* obj;
	char lineHeader[200];
	obj = fopen(fileName, "r");

	//--- 2. �޸� �Ҵ�'
	block.vertices = new vector<vec3>;
	block.vertices_normals = new vector<vec3>;
	block.vertices_uvs = new vector<vec2>;

	block.vertexIndices = new vector<Face>;
	block.uvIndices = new vector<Face>;
	block.normalIndices = new vector<Face>;

	block.max = vec3(0);
	block.min = vec3(0);

	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽� ���� �Է�
	while (!feof(obj)) {
		fscanf(obj, "%s", lineHeader);
		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			block.vertices->push_back(vertex);
			block.max = max(vertex, block.max);
			block.min = min(vertex, block.min);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(obj, "%f %f\n", &uv.x, &uv.y);
			block.vertices_uvs->push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			block.vertices_normals->push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			Face vertexIndex, uvIndex, normalIndex;
			int matches = fscanf(obj, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n", 
				&vertexIndex.a, &uvIndex.a, &normalIndex.a,
				&vertexIndex.b, &uvIndex.b, &normalIndex.b, 
				&vertexIndex.c, &uvIndex.c, &normalIndex.c);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			block.vertexIndices->push_back(vertexIndex - 1);
			block.uvIndices->push_back(uvIndex - 1);
			block.normalIndices->push_back(normalIndex - 1);
		}
		memset(lineHeader, '\0', sizeof(lineHeader));
	}
	//fclose(obj);	// Player �ҷ��ö� ���� ���� ��� ���� ������ ��
}

#pragma endregion
