
#include "GameManager.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void TimerFunc(int value);
void Mouse(int button, int state, int x, int y);
void MouseWheel(int wheel, int direction, int x, int y);
void Motion(int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void MouseEntry(int state);

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

Shader objectShader("Object");
Shader uiShader("UI");

Camera* fristCamera;
Camera camera;
Camera uiCamera;
Render objectRender;
guiRender gui_objectRender;

list<Mesh*> Mesh::allMesh;
list<Object*> Object::allObject;
list<GuiObject*> GuiObject::allGuiObject;

GameManager* gameManager;

void InitShader()
{
	objectShader.CreatVertexShader("Vertex.glsl");
	objectShader.CreatFragmentShader("Fragment.glsl");
	objectShader.CreatProgram();

	OBJ::MaterialBlockLocation = glGetUniformLocation(objectShader.program, "mBlock");
	Light::lightColorLocation = glGetUniformLocation(objectShader.program, "lightColor");
	Light::lightPosLocation = glGetUniformLocation(objectShader.program, "lightPos");

	Mesh::vertexLocation = glGetAttribLocation(objectShader.program, "vPos");
	Mesh::uvLoaction = glGetAttribLocation(objectShader.program, "vUV");
	Mesh::normalLocation = glGetAttribLocation(objectShader.program, "vNormal");
	Mesh::modelLocation = glGetUniformLocation(objectShader.program, "modelTransform");
	Mesh::vColorLocation = glGetUniformLocation(objectShader.program, "vColor");
	Mesh::mBlockLocation = glGetUniformBlockIndex(objectShader.program, "mBlock");
	glUniformBlockBinding(objectShader.program, Mesh::mBlockLocation, 0);
	Camera::viewLocation = glGetUniformLocation(objectShader.program, "viewTransform"); //--- 뷰잉 변환 설정
	Camera::projectionLocation = glGetUniformLocation(objectShader.program, "projectionTransform");
	Camera::viewPosLocation = glGetUniformLocation(objectShader.program, "viewPos");

	uiShader.CreatVertexShader("GuiVertex.glsl");
	uiShader.CreatFragmentShader("GuiFragment.glsl");
	uiShader.CreatProgram();

	GuiObject::ortho_projection = glGetUniformLocation(uiShader.program, "projectionTransform");
	GuiObject::texture1_Location = glGetUniformLocation(uiShader.program, "texture1");
}

void Init()
{
	Render::meshtRender = &objectRender;
	guiRender::gui_objectRender = &gui_objectRender;

	FrameTime::currentTime = clock();

	windowColor.R = windowColor.G = windowColor.B = 0;
	Camera::mainCamera = &camera;
	fristCamera = &camera;
	camera.name = "Main";
	camera.cameraPos.z = 10;
	camera.isPitch = true;

	uiCamera.isProjection_XY = true;

	gameManager = new GameManager;

	glUseProgram(*Shader::allProgram.find("UI")->second);
	for (const auto& gui_obj : GuiObject::allGuiObject)
		gui_obj->Init();
	glUseProgram(*Shader::allProgram.find("Object")->second);
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
	glutSpecialFunc(SpecialKeyBoard);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	//glutSetCursor(GLUT_CURSOR_NONE); // 마우스 커서 없애기
	glutPassiveMotionFunc(Motion);
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

	// GUI 모든 오브젝트 업데이트
	for (const auto& gui_obj : GuiObject::allGuiObject)
	{
		gui_obj->Update();
	}

	// GUI 모든 오브젝트 세팅
	for (const auto& gui_obj : GuiObject::allGuiObject)
	{
		gui_obj->SetMatrix();
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
	//for (auto i = 0; i < Collider::allCollider.size() - 1; i++)
	//{
	//	Collider* a = Collider::allCollider[i];
	//	for (auto j = i + 1; j < Collider::allCollider.size(); j++)
	//	{
	//		if (!a->object->ActiveSelf() || !a->isCollide)
	//			break;
	//		Collider* b = Collider::allCollider[j];

	//		if (!b->object->ActiveSelf() || !b->isCollide)
	//			continue;

	//		if (!Collider::OBBCollision(*a, *b))
	//			continue;

	//		a->object->OnCollision(b->object);
	//		b->object->OnCollision(a->object);
	//	}
	//}

	// 충돌한 물체들의 밀림 처리
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	{
		// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		glUseProgram(*Shader::allProgram.find("Object")->second);
		objectRender.Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (const auto& collider : Collider::allCollider)
			collider->DrawBox();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	{	//UI Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = &uiCamera;
		glUseProgram(*Shader::allProgram.find("UI")->second);
		gui_objectRender.Draw();
	}

	Camera::mainCamera = fristCamera;

	Object::key = -1;
	Object::specialKey = -1;
	Object::specialKeyUp = -1;

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

// 리팩토링 필요 state 개념으로 변경 
// 키보드 입력 도구로 몰아 넣기
void SpecialKeyboardUp(int key, int x, int y) 
{
	Object::specialKeyUp = key;

	switch (key)
	{
	}
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

void Mouse(int button, int state, int x, int y)
{
	gameManager->Mouse(button, state, x, y);
	
	glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
	gameManager->MouseWheel(wheel, direction, x, y);
}

void Motion(int x, int y)
{
	gameManager->Motion(x, y);

	glutPostRedisplay();
}

void MouseEntry(int state)
{
	gameManager->MouseEntry(state);

}