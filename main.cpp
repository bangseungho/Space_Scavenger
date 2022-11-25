#include "Cube.h"
#include "Player.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseWheel(int wheel, int direction, int x, int y);
void Motion(int x, int y);
void MouseEntry(int state);

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

// 마우스
bool isMouseRight = false;

Camera* fristCamera;
Camera camera;
Render objectRender;

list<Object*> Object::allObject;

Cube cube_Obj;
Player player;

void Init()
{
	Render::objectRender = &objectRender;

	Object::modelLocation = glGetUniformLocation(s_program, "modelTransform");
	Object::vColorLocation = glGetUniformLocation(s_program, "vColor");
	FrameTime::currentTime = clock();

	windowColor.R = windowColor.G = windowColor.B = 0;

	fristCamera = &camera;
	camera.name = "Main";
	camera.cameraPos.z = 100;
	camera.isPitch = true;
	camera.target_Pos = &player.transform;

	cube_Obj.transform.worldScale *= 0.1;

	for (const auto& obj : Object::allObject)
		obj->Init();
	for (const auto& collider : Collider::allCollider)
		collider->Init();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("21");
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	Init();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	glutPassiveMotionFunc(Motion);
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
		collider->GetBox_OBB();
	}

	// 모든 충돌 처리
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->Collision();
	}

	// 충돌한 물체들의 밀림 처리
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	{
		// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		objectRender.Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (const auto& collider : Collider::allCollider)
			collider->DrawBox();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	Object::key = -1;
	Object::specialKey = -1;

	FrameTime::oneFrame = (clock() - FrameTime::currentTime) / 1000.0f;
	FrameTime::currentTime += FrameTime::oneFrame * 1000.0f;

	glutSwapBuffers();
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	windowSize_W = w;
	windowSize_H = h;
}

void KeyBoard(unsigned char key, int x, int y)	
{
	Object::key = key;
	switch (key)
	{
	//case 'q':
	//	exit(1);
	//	break;
	}

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
	}
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	vec2 realStartMouse = RealPosition(StartMouse);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isMouseRight = !isMouseRight;
	}

	glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
	if (direction < 0)
	{
		cout << "Zoom out" << endl;
		camera.LookAtView(10);
	}
	else
	{
		cout << "Zoom in " << endl;
		camera.LookAtView(-10);
	}
}

void Motion(int x, int y)
{
	vec2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	//ShowCursor(isMouseRight);
	if (!isMouseRight)
	{
		vec2 diffPos = (mouse_Pos - StartMouse) * FrameTime::oneFrame * vec2(10);
		player.transform.worldRotation.y -= diffPos.x;
		player.transform.worldRotation.x -= diffPos.y;
	}

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	glutPostRedisplay();
}

void MouseEntry(int state)
{
	if (state == GLUT_LEFT)
	{
		if (!isMouseRight)
		{
			//glutWarpPointer(windowSize_W / 2, windowSize_H / 2);
			StartMouse = { (float)windowSize_W / 2, (float)windowSize_H / 2 };
			StartMouse = Coordinate(StartMouse);
			StartMouse.y = -StartMouse.y;
		}
	}
}