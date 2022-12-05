#pragma once
#include "Afx.h"

typedef struct VertexBlock {
	vector<Face>* vertexIndices, * uvIndices, * normalIndices;
	vector<vec3> vertices;
	vector<vec2> vertices_uvs;
	vector<vec3> vertices_normals;
	vec3 max, min;
	int groupCount;
}VertexBlock;

typedef struct MaterialBlock {
	char name[32];
// �𵨸� ���α׷��� ���� ����
#ifdef _MAX
	vec3 Kd;
	vec3 Ks;
	float Tr;
	float d;
	vec3 Tf;
	float Pr;
	float Pm;
	float Pc;
	float Pcr;
	float Ni;
	vec3 Ke;
	int illum;

	// �Ⱦ��� ����
	float Ns;
	vec3 Ka;
#endif // _MAX
}MaterialBlock;

class OBJ
{
public:
	static unsigned int MaterialBlockLocation;
public:
	OBJ();
	~OBJ();
public:
	void ReadObj(char* fileName);
	void ReadMaterial(char* mtlName);

private:	// obj ����
	void PushVertex(FILE* obj);
	void PushUV(FILE* obj);
	void PushNormal(FILE* obj);
	void PushFaceIndex(FILE* obj);

private:	// mtl ����
	void PushMTLName(FILE* obj, MaterialBlock& _Material);
	void PushMTLNs(FILE* obj, MaterialBlock& _Material);
	void PushMTLNi(FILE* obj, MaterialBlock& _Material);
	void PushMTLd(FILE* obj, MaterialBlock& _Material);
	void PushMTLTr(FILE* obj, MaterialBlock& _Material);
	void PushMTLTf(FILE* obj, MaterialBlock& _Material);
	void PushMTLillum(FILE* obj, MaterialBlock& _Material);
	void PushMTLKa(FILE* obj, MaterialBlock& _Material);
	void PushMTLKd(FILE* obj, MaterialBlock& _Material);
	void PushMTLKs(FILE* obj, MaterialBlock& _Material);
	void PushMTLKe(FILE* obj, MaterialBlock& _Material);
	void PushMTLPr(FILE* obj, MaterialBlock& _Material);
	void PushMTLPm(FILE* obj, MaterialBlock& _Material);
	void PushMTLPc(FILE* obj, MaterialBlock& _Material);
	void PushMTLPcr(FILE* obj, MaterialBlock& _Material);

public:
	VertexBlock vBlock;
	vector<MaterialBlock> mBlock;

private:
	string objName;
	string materialName;
};

