#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "objRead.h"

using namespace std;

GLuint win_width = 1920;
GLuint win_height = 1080;
GLfloat aspect_ratio{};
GLfloat fovy{};
GLfloat mx;
GLfloat my;

random_device rd;
default_random_engine dre(rd());
uniform_real_distribution<float> urd{ 0.0, 1.0 };

GLvoid Reshape(int w, int h);
GLvoid convertDeviceXYOpenGlXY(int x, int y, float* ox, float* oy);

struct Vec3d
{
	GLfloat _posX;
	GLfloat _posY;
	GLfloat _posZ;
};

struct Color
{
	GLfloat	_r;
	GLfloat	_g;
	GLfloat	_b;
};

struct Vertice
{
	Vec3d _pos;
	Color _color;
};

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

GLvoid convertDeviceXYOpenGlXY(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 600;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

enum class ShaderType {
	vertexshader,
	fragmentshader,
};

class Shader {
	const GLchar* _source;
	ShaderType _type;
	GLuint _shader;
	GLint result;
	GLchar errorLog[512];

public:
	Shader(const GLchar* source, ShaderType type) : _shader{}, result{}, errorLog{} {
		_source = filetobuf(source);
		_type = type;
	}

	GLuint& getShader() {
		return _shader;
	}

	void make_shader() {
		switch (_type) {
		case ShaderType::vertexshader:
			_shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::fragmentshader:
			_shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		glShaderSource(_shader, 1, (const GLchar**)&_source, 0);
		glCompileShader(_shader);
		error_check();
	}

	void error_check() {
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(_shader, 512, NULL, errorLog);
			cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
			return;
		}
	}

	void delete_shader() {
		glDeleteShader(_shader);
	}
};

Shader coord_v_shader{ "coord_vertex.glsl", ShaderType::vertexshader };
Shader obj1_v_shader{ "obj1_vertex.glsl", ShaderType::vertexshader };
Shader temp_f_shader{ "fragment.glsl", ShaderType::fragmentshader };

class ShaderProgram {
	GLuint _s_program;

public:
	ShaderProgram() : _s_program{} {

	}

	GLuint& getSprogram() {
		return _s_program;
	}

	void make_s_program(GLint vertex, GLint fragment) {
		_s_program = glCreateProgram();

		glAttachShader(_s_program, vertex);
		glAttachShader(_s_program, fragment);
		glLinkProgram(_s_program);
	}
};

ShaderProgram obj1_s_program;
ShaderProgram coord_s_program;

void InitShader()
{
	coord_v_shader.make_shader();
	obj1_v_shader.make_shader();
	temp_f_shader.make_shader();

	obj1_s_program.make_s_program(obj1_v_shader.getShader(), temp_f_shader.getShader());
	coord_s_program.make_s_program(coord_v_shader.getShader(), temp_f_shader.getShader());

	coord_v_shader.delete_shader();
	obj1_v_shader.delete_shader();
	temp_f_shader.delete_shader();
}

class Camera {
	glm::vec4 pivot;
	glm::vec4 target;

	glm::vec3 Pos;
	glm::vec3 Dir;
	glm::vec3 Up;
	glm::mat4 view;

	glm::vec4 final_transform;
	glm::vec4 final_dir_transform;

	GLfloat rotate_degree;
	glm::vec3 translate_amount;

	GLfloat dir_rotate_degree;
	glm::vec3 dir_translate_amount;

public:
	Camera() {

	}

	void translate(glm::vec3 trans) {
		translate_amount += trans;
	}

	void rotate(GLfloat degree) {
		rotate_degree += degree;
	}

	void dir_translate(glm::vec3 trans) {
		dir_translate_amount += trans;
	}

	void dir_rotate(GLfloat degree) {
		dir_rotate_degree += degree;
	}

	void setting(glm::vec4 pos_pivot, glm::vec4 target_pivot, glm::vec3 up_pivot) {
		pivot = pos_pivot;
		target = target_pivot;
		Up = up_pivot;

		final_transform = glm::vec4(pivot);
		final_dir_transform = glm::vec4(target);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(rotate_degree), glm::vec3(0.0, 1.0, 0.0));
		trans = glm::translate(trans, glm::vec3(translate_amount));
		final_transform = trans * final_transform;

		glm::mat4 dir_trans = glm::mat4(1.0f);
		dir_trans = glm::translate(dir_trans, glm::vec3(dir_translate_amount));
		dir_trans = glm::rotate(dir_trans, (GLfloat)glm::radians(dir_rotate_degree), glm::vec3(0.0, 1.0, 0.0));
		final_dir_transform = trans * dir_trans * final_dir_transform;

		Pos = glm::vec3(final_transform);
		Dir = glm::vec3(final_dir_transform);
		view = glm::mat4(1.0f);
		view = glm::lookAt(Pos, Dir, Up);
	}

	glm::mat4 getView() {
		return view;
	}
};

class Object
{
	glm::vec4 pivot;
	GLfloat rotate_degree;
	glm::vec3 translate_amount;
	glm::vec3 scale_amount;
	glm::mat4 transform = glm::mat4(1.0f); // 변환 행렬
	glm::mat4 final_transform = glm::mat4(1.0f);

	vector<Color> colors;

	objRead objReader;
	GLint obj;
	unsigned int modelLocation;
	const char* modelTransform;

	//======================VAO, VBO========================//
	GLuint vao;
	GLuint ebo;
	GLuint vbo_position;
	GLuint vbo_normal;
	GLuint vbo_color;

public:
	Object(const char* modelTransform, const char* objfile) {
		obj = objReader.loadObj_normalize_center(objfile);
		this->modelTransform = modelTransform;

		for (int i{}; i < objReader.nr_outvertex.size(); ++i) {
			colors.push_back({ urd(dre), urd(dre), urd(dre) });
		}
	}
	~Object() {

	}

	GLvoid set_vbo() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &ebo);
		glGenBuffers(1, &vbo_position);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
		glBufferData(GL_ARRAY_BUFFER, objReader.nr_outvertex.size() * sizeof(glm::vec3), &objReader.nr_outvertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objReader.vertexIndices.size() * sizeof(glm::vec3), &objReader.vertexIndices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &vbo_color);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
		glBufferData(GL_ARRAY_BUFFER, objReader.nr_outvertex.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(obj1_s_program.getSprogram(), "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	void rotate(GLfloat degree) {
		rotate_degree += degree;
	}

	void translate(glm::vec3 trans) {
		translate_amount += trans;
	}

	void scale(glm::vec3 scale) {
		scale_amount += scale;
	}

	void setting(glm::vec4 Pos_pivot) {
		pivot = Pos_pivot;

		final_transform = glm::mat4(1.0f);

		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(translate_amount));
		transform = glm::rotate(transform, glm::radians(rotate_degree), glm::vec3(0.0, 1.0, 0.0));
		transform = glm::scale(transform, glm::vec3(scale_amount));

		final_transform = transform * final_transform;
	}

	GLvoid draw(ShaderProgram s_program, Camera cam, glm::mat4& projection) {
		glUseProgram(s_program.getSprogram());
		glBindVertexArray(vao);
		unsigned int obj1_modelLocation = glGetUniformLocation(s_program.getSprogram(), modelTransform);
		glUniformMatrix4fv(obj1_modelLocation, 1, GL_FALSE, glm::value_ptr(final_transform));
		glPointSize(10);
		unsigned int viewLocation_obj1 = glGetUniformLocation(s_program.getSprogram(), "viewTransform"); //--- 뷰잉 변환 설정
		unsigned int projLoc_obj1 = glGetUniformLocation(s_program.getSprogram(), "projection");
		glUniformMatrix4fv(viewLocation_obj1, 1, GL_FALSE, &cam.getView()[0][0]);
		glUniformMatrix4fv(projLoc_obj1, 1, GL_FALSE, &projection[0][0]);
		glDrawElements(GL_TRIANGLES, obj, GL_UNSIGNED_INT, 0);
	}
};

vector<Object> cube;
Camera cam_1;

void InitBuffer()
{
	cube[0].set_vbo();

	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(0);
}

GLvoid display()
{
	//====================set viewport======================//
	//glViewport(0, 0, win_width, win_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//=====================set cam_1, projection=============//
	cam_1.setting({ 0.0, 3.0, 2.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 });
	glm::mat4 projection = glm::mat4(1.0f);
	unsigned int projLoc_coord = glGetUniformLocation(coord_s_program.getSprogram(), "projection");

	//===================set cooordinate====================//
	projection = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);
	glUseProgram(coord_s_program.getSprogram());
	unsigned int viewLocation_coord = glGetUniformLocation(coord_s_program.getSprogram(), "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation_coord, 1, GL_FALSE, &cam_1.getView()[0][0]);
	glUniformMatrix4fv(projLoc_coord, 1, GL_FALSE, &projection[0][0]);
	glDrawArrays(GL_LINES, 0, 6);

	//======================set object======================//
	cube[0].setting(glm::vec4(1.0f));
	cube[0].draw(obj1_s_program, cam_1, projection);


	//======================set mode========================//
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	if (h == 0)
		h = 1;
	aspect_ratio = GLfloat(w) / h;
	glViewport(0, 0, w, h);
}
static GLfloat cnt = 0;
void TimerFunction(int value)
{
	//cube[0].rotate(0.1f);
	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, 1);
}

void Init()
{
	int width_num;
	int height_num;
	cout << "input width_num : ";
	cin >> width_num;
	cout << "input height_num : ";
	cin >> height_num;
	cout << width_num << " : " << height_num;

	cube.push_back(Object{ "obj1_modelTransform", "cube.obj" });
	cube[0].scale(glm::vec3(0.1f, 0.1f, 0.1f));
	//under_body.init("obj1_modelTransform", "body.obj");
	//under_body.scale(0.2, 0.05, 0.2);
	//under_body.translate(0.0, 0.05, 0.0);
}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("MOUNTAIN MAGE");
	//--- GLEW 초기화하기
	glClearColor(0.1, 0.1, 0.1, 1.0f);
	glewExperimental = GL_TRUE;
	glewInit();
	Init();
	InitShader();
	InitBuffer();
	glutDisplayFunc(display);
	//glutMouseFunc(Mouse);
	//glutKeyboardFunc(Keyboard);
	//glutSpecialFunc(special);
	//glutSpecialUpFunc(KeyUp);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}