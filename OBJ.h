#pragma once
#include "Afx.h"
#include <string>

typedef struct VertexBlock {
	vector<Face>* vertexIndices, * uvIndices, * normalIndices;
	vector<vec3> vertices;
	vector<vec2> vertices_uvs;
	vector<vec3> vertices_normals;
	vec3 max, min;
	int groupCount;
	string* usemtlName;
}VertexBlock;

typedef struct MaterialBlock {
// 모델링 프로그램에 따른 변수
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

	// 안쓰는 변수
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
	void ReadObj(char* fileName) { ReadObj("", fileName); };
	void ReadObj(string path, string objFileName);
	void ReadMaterial(string mtlName);

private: // 공용
	void SkipCommand(FILE* f);

private:	// obj 관련
	void PushVertex(FILE* obj);
	void PushUV(FILE* obj);
	void PushNormal(FILE* obj);
	void PushFaceIndex(FILE* obj);
	void PushusemtlName(FILE* obj);

private:	// mtl 관련
	void PushMTLName(FILE* obj, string& usemtlName);
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
	map<string, MaterialBlock> mBlock;
	bool isOnMTL;

private:
	string objName;
	string materialName;
};

