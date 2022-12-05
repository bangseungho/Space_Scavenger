#include "OBJ.h"

unsigned int OBJ::MaterialBlockLocation;

OBJ::OBJ()
{
}

OBJ::~OBJ()
{
}

void OBJ::ReadObj(char* fileName)
{
	FILE* obj;
	FILE* mtl;
	char lineHeader[1000];
	int groupNum = 0;
	char mtlName[100];

	obj = fopen(fileName, "r");
	while (!feof(obj)) {
		fscanf(obj, "%s", lineHeader);
		if (strcmp(lineHeader, "g") == 0) groupNum++;
		//else if(strcmp(lineHeader, "mtllib") == 0) fscanf(obj, "%s", mtlName);
	}
	//mtl = fopen(mtlName, "r");

	vBlock.vertexIndices = new vector<Face>[groupNum];
	vBlock.normalIndices = new vector<Face>[groupNum];
	vBlock.uvIndices = new vector<Face>[groupNum];
	vBlock.groupCount = -1;
	vBlock.min = vec3(10000); vBlock.max = vec3(-10000);

	rewind(obj);
	while (!feof(obj)) {
		fscanf(obj, "%s", lineHeader);
		if (strcmp(lineHeader, "v") == 0) PushVertex(obj);
		else if (strcmp(lineHeader, "vt") == 0) PushUV(obj);
		else if (strcmp(lineHeader, "vn") == 0) PushNormal(obj);
		else if (strcmp(lineHeader, "f") == 0) PushFaceIndex(obj);
		else if (strcmp(lineHeader, "g") == 0) vBlock.groupCount++;
		memset(lineHeader, '\0', sizeof(lineHeader));
	}
	vBlock.groupCount++;
	vec3 scale = vBlock.max - vBlock.min;

	for (auto& temp : vBlock.vertices)
	{
		temp = temp - vBlock.min;
		temp = ((temp * 2.0f) / scale) - 1.0f;
	}

	objName = fileName;
	fclose(obj);
}

void OBJ::ReadMaterial(char* mtlName)
{
	FILE* obj;
	char lineHeader[1000];
	MaterialBlock mterial;
	int newMTLNum = -1;
	obj = fopen(mtlName, "r");
	while (!feof(obj))
	{
		fscanf(obj, "%s", lineHeader);
		if (strcmp("newmtl", lineHeader) == 0)
		{
			newMTLNum++;
			mBlock.push_back(mterial);
			PushMTLName(obj, mBlock[newMTLNum]);
		}
// 모델링 프로그램에 따른 함수 사용
#ifdef _MAX
		else if (strcmp("Kd", lineHeader) == 0) PushMTLKd(obj, mBlock[newMTLNum]);
		else if (strcmp("Ks", lineHeader) == 0) PushMTLKs(obj, mBlock[newMTLNum]);
		else if (strcmp("Tr", lineHeader) == 0) PushMTLTr(obj, mBlock[newMTLNum]);
		else if (strcmp("d", lineHeader) == 0) PushMTLd(obj, mBlock[newMTLNum]);
		else if (strcmp("Tf", lineHeader) == 0) PushMTLTf(obj, mBlock[newMTLNum]);
		else if (strcmp("Pr", lineHeader) == 0) PushMTLPr(obj, mBlock[newMTLNum]);
		else if (strcmp("Pm", lineHeader) == 0) PushMTLPm(obj, mBlock[newMTLNum]);
		else if (strcmp("Pc", lineHeader) == 0) PushMTLPc(obj, mBlock[newMTLNum]);
		else if (strcmp("Pcr", lineHeader) == 0) PushMTLPcr(obj, mBlock[newMTLNum]);
		else if (strcmp("Ni", lineHeader) == 0) PushMTLNi(obj, mBlock[newMTLNum]);
		else if (strcmp("Ke", lineHeader) == 0) PushMTLKe(obj, mBlock[newMTLNum]);
		else if (strcmp("illum", lineHeader) == 0) PushMTLillum(obj, mBlock[newMTLNum]);
#endif // _MAX

		//else if (strcmp("Ns", lineHeader) == 0) PushMTLNs(obj, mBlock[newMTLNum]);
		//else if (strcmp("Ni", lineHeader) == 0) PushMTLNi(obj, mBlock[newMTLNum]);
		//else if (strcmp("d", lineHeader) == 0) PushMTLd(obj, mBlock[newMTLNum]);
		//else if (strcmp("Tr", lineHeader) == 0) PushMTLTr(obj, mBlock[newMTLNum]);
		//else if (strcmp("Tf", lineHeader) == 0) PushMTLTf(obj, mBlock[newMTLNum]);
		//else if (strcmp("illum", lineHeader) == 0) PushMTLillum(obj, mBlock[newMTLNum]);
		//else if (strcmp("Ka", lineHeader) == 0) PushMTLKa(obj, mBlock[newMTLNum]);
		//else if (strcmp("Kd", lineHeader) == 0) PushMTLKd(obj, mBlock[newMTLNum]);
		//else if (strcmp("Ks", lineHeader) == 0) PushMTLKs(obj, mBlock[newMTLNum]);
		//else if (strcmp("Ke", lineHeader) == 0) PushMTLKe(obj, mBlock[newMTLNum]);
		memset(lineHeader, '\0', sizeof(lineHeader));
	}
}

void OBJ::PushVertex(FILE* obj)
{
	vec3 vertex;
	vec3 min = vBlock.min;
	vec3 max = vBlock.max;
	fscanf(obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
	vBlock.vertices.push_back(vertex);
	if (vertex.x < min.x) min.x = vertex.x;
	if (vertex.y < min.y) min.y = vertex.y;
	if (vertex.z < min.z) min.z = vertex.z;
	if (vertex.x > max.x) max.x = vertex.x;
	if (vertex.y > max.y) max.y = vertex.y;
	if (vertex.z > max.z) max.z = vertex.z;

	vBlock.min = min;
	vBlock.max = max;
}

void OBJ::PushUV(FILE* obj)
{
	vec2 uv;
	fscanf(obj, "%f %f\n", &uv.x, &uv.y);
	vBlock.vertices_uvs.push_back(uv);
}

void OBJ::PushNormal(FILE* obj)
{
	vec3 normal;
	fscanf(obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	vBlock.vertices_normals.push_back(normal);
}

void OBJ::PushFaceIndex(FILE* obj)
{
	Face vertexIndex, uvIndex, normalIndex;
	int matches = fscanf(obj, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n",
		&vertexIndex.a, &uvIndex.a, &normalIndex.a,
		&vertexIndex.b, &uvIndex.b, &normalIndex.b,
		&vertexIndex.c, &uvIndex.c, &normalIndex.c);
	if (matches != 9) {
		printf("File can't be read by our simple parser : ( Try exporting with other options\n");
		return;
	}
	vBlock.vertexIndices[vBlock.groupCount].push_back(vertexIndex - 1);
	vBlock.uvIndices[vBlock.groupCount].push_back(uvIndex - 1);
	vBlock.normalIndices[vBlock.groupCount].push_back(normalIndex - 1);
}

void OBJ::PushMTLName(FILE* obj, MaterialBlock& _Material)
{
	fscanf(obj, "%s", _Material.name);
}

void OBJ::PushMTLNs(FILE* obj, MaterialBlock& _Material)
{
	float Ns;
	fscanf(obj, "%f", &Ns);
	_Material.Ns = Ns;
}

void OBJ::PushMTLNi(FILE* obj, MaterialBlock& _Material)
{
	float Ni;
	fscanf(obj, "%f", &Ni);
	_Material.Ni = Ni;
}

void OBJ::PushMTLd(FILE* obj, MaterialBlock& _Material)
{
	float d;
	fscanf(obj, "%f", &d);
	_Material.d = d;
}

void OBJ::PushMTLTr(FILE* obj, MaterialBlock& _Material)
{
	float Tr;
	fscanf(obj, "%f", &Tr);
	_Material.Tr = Tr;
}

void OBJ::PushMTLTf(FILE* obj, MaterialBlock& _Material)
{
	vec3 Tf;
	fscanf(obj, "%f %f %f", &Tf.x, &Tf.y, &Tf.z);
	_Material.Tf = Tf;
}

void OBJ::PushMTLillum(FILE* obj, MaterialBlock& _Material)
{
	float illum;
	fscanf(obj, "%d", &illum);
	_Material.illum = illum;
}

void OBJ::PushMTLKa(FILE* obj, MaterialBlock& _Material)
{
	vec3 Ka;
	fscanf(obj, "%f %f %f", &Ka.x, &Ka.y, &Ka.z);
	_Material.Ka = Ka;
}

void OBJ::PushMTLKd(FILE* obj, MaterialBlock& _Material)
{
	vec3 Kd;
	fscanf(obj, "%f %f %f", &Kd.x, &Kd.y, &Kd.z);
	_Material.Kd = Kd;
}

void OBJ::PushMTLKs(FILE* obj, MaterialBlock& _Material)
{
	vec3 Ks;
	fscanf(obj, "%f %f %f", &Ks.x, &Ks.y, &Ks.z);
	_Material.Ks = Ks;
}

void OBJ::PushMTLKe(FILE* obj, MaterialBlock& _Material)
{
	vec3 Ke;
	fscanf(obj, "%f %f %f", &Ke.x, &Ke.y, &Ke.z);
	_Material.Ke = Ke;
}

void OBJ::PushMTLPr(FILE* obj, MaterialBlock& _Material)
{
	float Pr;
	fscanf(obj, "%f", &Pr);
	_Material.Pr = Pr;
}

void OBJ::PushMTLPm(FILE* obj, MaterialBlock& _Material)
{
	float Pm;
	fscanf(obj, "%f", &Pm);
	_Material.Pm = Pm;
}

void OBJ::PushMTLPc(FILE* obj, MaterialBlock& _Material)
{
	float Pc;
	fscanf(obj, "%f", &Pc);
	_Material.Pc = Pc;
}

void OBJ::PushMTLPcr(FILE* obj, MaterialBlock& _Material)
{
	float Pcr;
	fscanf(obj, "%f", &Pcr);
	_Material.Pcr = Pcr;
}
