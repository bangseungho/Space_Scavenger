#include "Cube.h"
#include "Player.h"
#include "Map.h"
#include "ChatBox.h"
//#include "ResourcePool.cpp"	// ���ø� Ŭ������ cpp�� ��Ŭ��� �ؾ���
#include "Iron.h"
#include "Light.h"

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

// ���콺
bool isMouseRight = false;

Camera* fristCamera;
Camera camera;
Render objectRender;
guiRender gui_objectRender;

list<Mesh*> Mesh::allMesh;
list<Object*> Object::allObject;
list<GuiObject*> GuiObject::allGuiObject;

// �ӽ� Ŭ����
class GameManager : public Object
{
public:
	Cube cube_Obj;
	Player player;
	Map map;
	ChatBox chat_box;
	Light light;

public:
	void Init() {
		fristCamera->target_Pos = &player.transform;
		cube_Obj.transform.worldScale *= 0.1;

		light.transform.worldPosition.x = 1;
	};
};

GameManager* gameManager;

void Init()
{
	Render::meshtRender = &objectRender;
	guiRender::gui_objectRender = &gui_objectRender;

	Light::lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	Light::lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	Camera::viewPosLocation = glGetUniformLocation(s_program, "viewPos");
	Mesh::modelLocation = glGetUniformLocation(s_program, "modelTransform");
	Mesh::vColorLocation = glGetUniformLocation(s_program, "vColor");
	Object::meterialBlockLoaction = glGetUniformBlockIndex(s_program,"meterial");
	FrameTime::currentTime = clock();

	windowColor.R = windowColor.G = windowColor.B = 0;
	fristCamera = &camera;
	camera.name = "Main";
	camera.cameraPos.z = 10;
	camera.isPitch = true;

	gameManager = new GameManager;

	for (const auto& gui_obj : GuiObject::allGuiObject)
		gui_obj->Init();
	for (const auto& mesh : Mesh::allMesh)
		mesh->MeshInit();
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

	//--- GLEW �ʱ�ȭ�ϱ�
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

	// ��� ������Ʈ ������Ʈ
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

	// GUI ��� ������Ʈ ������Ʈ
	for (const auto& gui_obj : GuiObject::allGuiObject)
	{
		gui_obj->Update();
	}

	// GUI ��� ������Ʈ ����
	for (const auto& gui_obj : GuiObject::allGuiObject)
	{
		gui_obj->SetMatrix();
	}

	// ��� �ݶ��̴� ��ġ ������Ʈ
	for (const auto& collider : Collider::allCollider)
	{
		if (!collider->isCollide)
			continue;
		collider->GetBox_OBB();
	}

	// ��� �浹 ó��
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->Collision();
	}



	// �浹�� ��ü���� �и� ó��
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	{
		// ���� Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		objectRender.Draw();
		gui_objectRender.Draw();

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

	aspect_ratio = GLfloat(w) / h;

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
	StartMouse.y = -StartMouse.y;\

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
		
		camera.LookAtView(1);
	}
	else
	{
		cout << "Zoom in " << endl;
		if (length(camera.cameraPos) > 1)
			camera.LookAtView(-1);
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
		vec2 diffPos = (mouse_Pos - StartMouse) * FrameTime::oneFrame;
		gameManager->player.transform.worldRotation.y -= diffPos.x;
		gameManager->player.transform.worldRotation.x -= diffPos.y;
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
			glutWarpPointer(windowSize_W / 2, windowSize_H / 2);
			StartMouse = { (float)windowSize_W / 2, (float)windowSize_H / 2 };
			StartMouse = Coordinate(StartMouse);
			StartMouse.y = -StartMouse.y;
		}
	}
}