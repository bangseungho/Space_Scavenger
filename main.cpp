#include "Data.h"
#include "GameManager.h"
#include "CubeMapManager.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void KeyBoardUp(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void TimerFunc(int value);
void Mouse(int button, int state, int x, int y);
void MouseWheel(int wheel, int direction, int x, int y);
void Motion(int x, int y);
void MouseEntry(int state);

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;
bool is_ColliderDraw = false;

list<Object*> Object::allObject;
list<Object*> Object::initObject;
list<Collider*> Collider::initCollider;
list<Light*> Light::allLight;
list<Mesh*> Mesh::initMesh;

Shader objectShader("Object");
Shader uiShader("UI");
Shader fontShader("Font");

Camera* fristCamera;
Camera camera;
Camera uiCamera;
Render objectRender;
Render uiRender;
Render fontRender;

GameManager* gameManager;
CubeMapManager* skyBoxManager;

void InitShader()
{
	objectShader.CreatVertexShader("Vertex.glsl");
	objectShader.CreatFragmentShader("Fragment.glsl");
	objectShader.CreatProgram();

	OBJ::MaterialBlockLocation = glGetUniformLocation(objectShader.program, "mBlock");

	Camera::viewLocation = glGetUniformLocation(objectShader.program, "viewTransform"); //--- 뷰잉 변환 설정
	Camera::projectionLocation = glGetUniformLocation(objectShader.program, "projectionTransform");
	Camera::viewPosLocation = glGetUniformLocation(objectShader.program, "viewPos");

	uiShader.CreatVertexShader("GuiVertex.glsl");
	uiShader.CreatFragmentShader("GuiFragment.glsl");
	uiShader.CreatProgram();

	fontShader.CreatVertexShader("Font_Vertex.glsl");
	fontShader.CreatFragmentShader("Font_Fragment.glsl");
	fontShader.CreatProgram();
}

void InitRender()
{
	Render::objectRender = &objectRender;
	Render::uiRender = &uiRender;
	Render::fontRender = &fontRender;

	string uiLayer[] = { "Default" , "Resource", "Player", "Equipment" };
	uiRender.SetLayer(*uiLayer);
}

void Init()
{
	InitRender();

	FrameTime::currentTime = clock();

	windowColor.R = windowColor.G = windowColor.B = 0;
	Camera::mainCamera = &camera;
	fristCamera = &camera;
	camera.name = "Main";
	//camera.cameraPos.y = 3;
	camera.cameraPos.y = 5;
	camera.cameraPos.z = -10;
	camera.cameraDirection.z = 4;
	//camera.cameraDirection.y = 1;
	camera.cameraDirection.y = 2;
	camera.isPitch = true;

	uiCamera.isProjection_XY = true;

	gameManager = new GameManager;
	skyBoxManager = new CubeMapManager(&gameManager->player.transform);


	glUseProgram(Shader::allProgram.find("Object")->second->program);
	while (!Mesh::initMesh.empty())
	{
		Mesh::initMesh.front()->MeshInit();
		Mesh::initMesh.pop_front();
	}
	while (!Object::initObject.empty())
	{
		Object::initObject.front()->Init();
		Object::initObject.pop_front();
	}
	while (!Collider::initCollider.empty())
	{
		Collider::initCollider.front()->Init();
		Collider::initCollider.pop_front();
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("21");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	Init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyBoardUp);
	glutSpecialFunc(SpecialKeyBoard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	//glutSetCursor(GLUT_CURSOR_NONE); // 마우스 커서 없애기
	glutPassiveMotionFunc(Motion);
	glutMotionFunc(Motion);
	glutTimerFunc(10, TimerFunc, 1);
	glutEntryFunc(MouseEntry);
	glutMainLoop();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 모든 오브젝트 업데이트
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->Update();
	}

	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;

		obj->SetMatrix();
	}

	// 모든 콜라이더 위치 업데이트
	for (const auto& collider : Collider::allCollider)
	{
		if (!collider->isCollide)
			continue;
		collider->color.SetColor({ 0,0,1,1 });
		collider->GetBox_OBB();
	}

	// 모든 충돌 처리
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->OnCollision();
	}

	{
		glUseProgram(Shader::allProgram.find("Object")->second->program);
		while (!Mesh::initMesh.empty())
		{
			Mesh::initMesh.back()->MeshInit();
			Mesh::initMesh.pop_back();
		}
		while (!Object::initObject.empty())
		{
			Object::initObject.back()->Init();
			Object::initObject.pop_back();
		}
		while (!Collider::initCollider.empty())
		{
			Collider::initCollider.back()->Init();
			Collider::initCollider.pop_back();
		}
	}

	{	// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;
		skyBoxManager->DrawSky();

		glUseProgram(Shader::allProgram.find("Object")->second->program);
		objectRender.Draw();

		if (is_ColliderDraw)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			for (const auto& collider : Collider::allCollider)
				collider->DrawBox();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	{	//UI Viewport
		Camera::mainCamera = &uiCamera;
		glUseProgram(Shader::allProgram.find("UI")->second->program);
		uiRender.UIDraw();
	}

	{	// Font
		glUseProgram(fontShader.program);
		fontRender.FontDraw();
	}

	Camera::mainCamera = fristCamera;

	Object::key = -1;
	Object::keyUp = 0;
	Object::specialKey = -1;
	Object::specialKeyUp = -1;
	button = -1;
	state = -1;

	FrameTime::oneFrame = (clock() - FrameTime::currentTime) / 1000.0f;
	FrameTime::currentTime += FrameTime::oneFrame * 1000.0f;

	glutSwapBuffers();
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	aspect_ratio = GLfloat(w) / h;

	windowSize_W = w;
	windowSize_H = h;
}

void KeyBoard(unsigned char key, int x, int y)	
{
	Object::key = key;

	switch (key)
	{
	case '0':
		exit(1);
		break;
	}

	gameManager->KeyBoard(key, x, y);

	glutPostRedisplay();
}


void KeyBoardUp(unsigned char key, int x, int y)
{
	Object::keyUp = key;

	glutPostRedisplay();
}


void SpecialKeyBoard(int key, int x, int y)
{
	Object::specialKey = key;

	switch (key)
	{
	case GLUT_KEY_F1:
		Collider::isPrint = !Collider::isPrint;
		break;
	case GLUT_KEY_F11:
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case GLUT_KEY_F12:
		is_ColliderDraw = !is_ColliderDraw;
		break;
	}

	gameManager->SpecialKeyboard(key, x, y);
}

// 리팩토링 필요 state 개념으로 변경 
// 키보드 입력 도구로 몰아 넣기
void SpecialKeyboardUp(int key, int x, int y) 
{
	Object::specialKeyUp = key;
	gameManager->SpecialKeyboardUp(key, x, y);
}

void TimerFunc(int value)
{
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;

		obj->MyTimer();
	}

	glutTimerFunc(10, TimerFunc, 1);
}

void Mouse(int _Button, int _State, int x, int y)
{
	mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	button = _Button;
	state = _State;

	gameManager->Mouse(_Button, _State, x, y);

	glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
	gameManager->MouseWheel(wheel, direction, x, y);
}

void Motion(int x, int y)
{
	mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	gameManager->Motion(x, y);

	StartMouse = mouse_Pos;

	glutPostRedisplay();
}

void MouseEntry(int state)
{
	gameManager->MouseEntry(state);

}