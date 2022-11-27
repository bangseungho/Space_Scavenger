#include "Collider.h"

VertexBlock* Collider::_Block = nullptr;
list<Collider*> Collider::allCollider;
bool Collider::isPrint = false;

Collider::Collider()
{

	if (_Block == nullptr)
	{
		_Block = new VertexBlock;
		ReadObj((char*)"Cube.obj", *_Block);
	}

	block = _Block;

	tag = "NULL";
	color.R = 0;
	color.G = 0;

	isCollide = true;
	isTrigger = false;
	isMouseCollide = false;
	isWindowCollide = false;

	allCollider.push_back(this);
}

Collider::~Collider()
{
	allCollider.erase(remove(allCollider.begin(), allCollider.end(), this), allCollider.end());
}

void Collider::Init()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_VERTICES);
	glGenBuffers(1, &VAO_VERTICES_INDEX);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_VERTICES);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices->size(), &block->vertices[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_VERTICES_INDEX); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->vertexIndices->size(), &block->vertexIndices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
}

void Collider::DrawBox()
{
	glUseProgram(s_program);

	if (!isCollide)
		return;

	mat4 collideModel = scale(object->transform.model, vec3(1.00001));

	glUniformMatrix4fv(Mesh::modelLocation, 1, GL_FALSE, value_ptr(collideModel));
	glUniform4f(Mesh::vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, cBlock.vertices.size());
	glDrawElements(GL_TRIANGLES, block->vertexIndices->size() * 3, GL_UNSIGNED_SHORT, 0);
}
// Right Front Top 점을 정해주면 된다.
// 즉 가로 세로 높이의 크기를 정해주면 된다.
void Collider::SetBox_OBB(const vec3& d)
{
	size = d/2;
	for (int i = 0; i < 3; i++)
	{
		defaultAxis[i] = axis[i] = vec3(0);
		axisLen[i] = 0;
	}

	defaultAxis[0].x = axisLen[0] = d.x / 2;
	defaultAxis[1].y = axisLen[1] = d.y / 2;
	defaultAxis[2].z = axisLen[2] = d.z / 2;
}


void Collider::GetBox_OBB()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = rotate(localModel, radians(object->transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(object->transform.localRotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(object->transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, object->transform.localScale);

	worldModel = rotate(worldModel, radians(object->transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(object->transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(object->transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = scale(worldModel, object->transform.worldScale);

	mat4 model = localModel * worldModel;

	for (int i = 0; i < 3; i++)
	{
		//axis[i] = defaultAxis[i];
		axis[i] = model * vec4(defaultAxis[i],1);
		axisLen[i] = length(axis[i]);
		axis[i] = normalize(axis[i]);
	}
		//axis[i] = object->transform.model * vec4(defaultAxis[i], 1);

	if (isPrint)
	{
		cout << this->tag << endl;
		for (int i = 0; i < 3; i++)
			cout << axis[i] << endl;
		for (int i = 0; i < 3; i++)
			cout << axisLen[i] << endl;
	}
}


// TODO
// 충돌 체크가 제데로 안됨
// 아마 Vec3Dot 쪽의 문제인듯 함
// dis와 axis 초기화 문제도 있는 듯
bool Collider::OBBCollision(const Collider& a,const Collider& b)
{
	color.SetColor({ 0, 0, 1, 1 });
	if (!a.isCollide || !b.isCollide)
		return false;

	vec3 dis; // a, b의 거리
	double c[3][3];
	double absC[3][3];
	double d[3];
	const double cutoff = 0.999999; // 투영벡터를 늘려줄 변수
	double r, r1, r2;	// 투영된 길이
	bool isExitsParallelPair = false;

	//dis = abs(a.object->transform.model * vec4(0,0,0,1) - b.object->transform.model * vec4(0,0,0,1));
	dis = b.object->transform.worldPosition - a.object->transform.worldPosition;

	for (int n = 0; n < 3; n++)
	{
		for (int i = 0; i < 3; i++)
		{
			c[n][i] = Vec3Dot(a.axis[n], b.axis[i]);
			absC[n][i] = abs(c[n][i]);
			if (absC[n][i] > cutoff)
				isExitsParallelPair = true;
		}
		d[n] = Vec3Dot(dis, a.axis[n]);
		r = abs(d[n]);
		r1 = a.axisLen[n];
		r2 = b.axisLen[0] * absC[n][0] + b.axisLen[1] * absC[n][1] + b.axisLen[2] * absC[n][2];
		//r2 = absC[n][0] + absC[n][1] + absC[n][2];
		if (r > r1 + r2)
			return false;
	}
	for (int n = 0; n < 3; n++)
	{
		r = abs(Vec3Dot(dis, b.axis[n]));
		r1 = a.axisLen[0] * absC[0][n] + a.axisLen[1] * absC[1][n] + a.axisLen[2] * absC[2][n];
		//r1 = absC[0][n] + absC[1][n] + absC[2][n];
		r2 = b.axisLen[n];
		if (r > r1 + r2)
			return false;
	}

	if (isExitsParallelPair)
		return true;

	{
		r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
		r1 = a.axisLen[1] * absC[2][0] + a.axisLen[2] * absC[1][0];
		r2 = b.axisLen[1] * absC[0][2] + b.axisLen[2] * absC[0][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
		r1 = a.axisLen[1] * absC[2][1] + a.axisLen[2] * absC[1][1];
		r2 = b.axisLen[0] * absC[0][2] + b.axisLen[2] * absC[0][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
		r1 = a.axisLen[1] * absC[2][2] + a.axisLen[2] * absC[1][2];
		r2 = b.axisLen[0] * absC[0][1] + b.axisLen[1] * absC[0][0];
		if (r > r1 + r2)
			return false;
	}

	{
		r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
		r1 = a.axisLen[0] * absC[2][0] + a.axisLen[2] * absC[0][0];
		r2 = b.axisLen[1] * absC[1][2] + b.axisLen[2] * absC[1][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
		r1 = a.axisLen[0] * absC[2][1] + a.axisLen[2] * absC[0][1];
		r2 = b.axisLen[0] * absC[1][2] + b.axisLen[2] * absC[1][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
		r1 = a.axisLen[0] * absC[2][2] + a.axisLen[2] * absC[0][2];
		r2 = b.axisLen[0] * absC[1][1] + b.axisLen[1] * absC[1][0];
		if (r > r1 + r2)
			return false;
	}

	{
		r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
		r1 = a.axisLen[0] * absC[1][0] + a.axisLen[1] * absC[0][0];
		r2 = b.axisLen[1] * absC[2][2] + b.axisLen[2] * absC[2][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
		r1 = a.axisLen[0] * absC[1][1] + a.axisLen[1] * absC[0][1];
		r2 = b.axisLen[0] * absC[2][2] + b.axisLen[2] * absC[2][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
		r1 = a.axisLen[0] * absC[1][2] + a.axisLen[1] * absC[0][2];
		r2 = b.axisLen[0] * absC[2][1] + b.axisLen[1] * absC[2][0];
		if (r > r1 + r2)
			return false;
	}

	color.SetColor({ 1, 0, 0, 1 });
	return true;
}