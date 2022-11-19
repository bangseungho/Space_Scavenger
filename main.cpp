#include "GL_Maze.h"
#include "Player.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

void InitMain();

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

Camera* fristCamera;
Camera mainCamera;
Camera mapCamera;
Camera playerCamera_01;
Render objectRender;

list<Object*> Object::allObject;

Player player;
GL_Maze maze_Object;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("21");
	
	glEnable(GL_DEPTH_TEST);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	{
		windowColor.R = windowColor.G = windowColor.B = 0;

		Render::mainRender = &objectRender;
		fristCamera = &mainCamera;
		mainCamera.cameraPos.y = 0.5;
		mainCamera.isProjection = true;
		mapCamera.isProjection_XZ = true;
		playerCamera_01.isOnePitch = true;

		Object::modelLocation = glGetUniformLocation(s_program, "modelTransform");
		Object::vColorLocation = glGetUniformLocation(s_program, "vColor");
		FrameTime::currentTime = clock();

		player.isActive = false;
		for (const auto& obj : Object::allObject)
		{
			obj->Init();
		}
	}

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// 모든 오브젝트 업데이트
	for (const auto& obj : Object::allObject)
	{
		if (!obj->isActive)
			continue;
		obj->Update();
	}

	// 모든 콜라이더 위치 업데이트
	for (const auto& collider : Collider::allCollider)
		collider->GetBox();

	// 모든 충돌 처리
	for (const auto& obj : Object::allObject)
		obj->Collision();

	// 충돌한 물체들의 밀림 처리
	for (const auto& collider : Collider::allCollider)
		collider->OnTrigger();

	{
		// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		objectRender.Draw();
	}

	{
		// Map ViewPort
		glViewport(windowSize_W * 3 / 4, windowSize_H * 3 / 4, windowSize_W / 4, windowSize_H / 4);
		Camera::mainCamera = &mapCamera;

		objectRender.Draw();
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
	case 'q':
		exit(1);
		break;
	case 'u':
		is_Polygon = !is_Polygon;

		break;
	case 'h':
		is_CullFace = !is_CullFace;
		if (is_CullFace)
		{
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
		}
		break;

	case 'o':
		mainCamera.isProjection = false;
		mainCamera.isProjection_XY = true;
		mainCamera.cameraPos.z = 2;
		break;
	case 'p':
		mainCamera.isProjection = true;
		mainCamera.isProjection_XY = false;
		break;

	case 'y':
		mainCamera.yRotate++;
		mainCamera.cameraPos.x = 2 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 2 * cos(radians(mainCamera.yRotate));
		break;
	case 'Y':
		mainCamera.yRotate--;
		mainCamera.cameraPos.x = 2 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 2 * cos(radians(mainCamera.yRotate));
		break;

	case 'r':
		maze_Object.MakeMaze();
		break;
	case 'v':
		maze_Object.SetWall_YScale(2.0f);
		break;
	case 's':
		player.isActive = true;
		player.transform.worldPosition.x = 0;
		player.transform.worldPosition.z = 0;
		break;

	case 'c':
		player.isActive = false;
		mainCamera.cameraPos = vec3(0, 0, 2);
		maze_Object.ReSet();

		break;
	case '1':
		fristCamera = &playerCamera_01;
		playerCamera_01.cameraPos = vec3(0,0.1,0);
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	Object::specialKey = key;
	playerCamera_01.ProcessInput(key);
	
	switch (key)
	{
	case GLUT_KEY_F1:
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

	Vector2 realStartMouse = RealPosition(StartMouse);

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	Vector2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;
	glutPostRedisplay();
}

void InitMain() 
{
}