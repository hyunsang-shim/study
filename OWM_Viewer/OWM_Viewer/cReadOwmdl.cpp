#include "stdafx.h"
#include "cReadOwmdl.h"


cReadOwmdl::cReadOwmdl()
{

}


cReadOwmdl::~cReadOwmdl()
{

}

OWMAP cReadOwmdl::ReadFile(std::string Filename)
{
	OWMAP ret;

	ifstream file;
	file.open(Filename.c_str(), ios::in | ios::binary);

	int nFSize;
	file.seekg(0, ios::end);
	int filesize = (int)file.tellg();
	printf("File Size in %d Bytes.\n", filesize);
	file.seekg(0, ios::beg);
	char tmp;
	unsigned int cnt = 0;
	int copied = 0;

	if (file.is_open())
	{
		unsigned short major;
		char tmp[64];
		file.read(tmp, sizeof(unsigned short));
		tmp[sizeof(unsigned short)] = '\0';
		ret.major = (unsigned short)tmp;
		cout << ret.major << endl;
		file.close();

		return ret;
	}
	else
	{
		printf("Couldn't open File. Program will be quit.");
		int a;
		scanf_s("%d", a);
		PostQuitMessage(0);
	}
}

vector<object> cReadOwmdl::GetObjects(ifstream * fp, unsigned int size)
{
	vector<object> ret;
	object tmp;


	struct object {
		std::string model_file;
		unsigned int entity_count;
		std::vector<entity> entities;
	};

	int cnt = 0;

	while (cnt++ < size)
	{
		char tmp_str;
		char read[1024];

		do {
			fp->read(&tmp_str, 1);
			if (tmp_str != NULL)
			{
				(tmp.model_file).append(1, tmp_str);
			}
		} while (tmp_str != NULL);


		fp->read(read, sizeof(unsigned int));
		memcpy(&tmp.entity_count, read, sizeof(unsigned int));


		tmp.entities = GetEntities(fp, tmp.entity_count);

		ret.push_back(tmp);

	}



	return ret;
}

vector<detail> cReadOwmdl::GetDetails(ifstream * fp, unsigned int size)
{
	vector<detail> ret;
	detail tmp;

	/*
	std::string			model_file;
	std::string			material_file;
	D3DXVECTOR3			pos;
	D3DXVECTOR3			vecScale;
	D3DXQUATERNION		quat;
	*/


	int cnt = 0;

	while (cnt++ < size)
	{
		char tmp_str;
		char read[1024];

		do {
			fp->read(&tmp_str, 1);
			if (tmp_str != NULL)
			{
				(tmp.model_file).append(1, tmp_str);
			}
		} while (tmp_str != NULL);


		do {
			fp->read(&tmp_str, 1);
			if (tmp_str != NULL)
			{
				(tmp.material_file).append(1, tmp_str);
			}
		} while (tmp_str != NULL);


		fp->read(read, sizeof(D3DXVECTOR3));
		memcpy(&tmp.pos, read, sizeof(D3DXVECTOR3));
		
		fp->read(read, sizeof(D3DXVECTOR3));
		memcpy(&tmp.vecScale, read, sizeof(D3DXVECTOR3));

		fp->read(read, sizeof(D3DXQUATERNION));
		memcpy(&tmp.quat, read, sizeof(D3DXQUATERNION));



		ret.push_back(tmp);
	}


	return ret;

}

vector<light> cReadOwmdl::GetLights(ifstream * fp, unsigned int size)
{
	vector<light> ret;
	light tmp;

	/*
	D3DXVECTOR3		pos;
	D3DXQUATERNION	quat;
	unsigned int	light_type;
	float			field_of_view;
	D3DCOLORVALUE	color;

	*/

	int cnt = 0;

	while (cnt++ < size)
	{
		char tmp_str;
		char read[1024];

		fp->read(read, sizeof(D3DXVECTOR3));
		memcpy(&tmp.pos, read, sizeof(D3DXVECTOR3));

		fp->read(read, sizeof(D3DXQUATERNION));
		memcpy(&tmp.quat, read, sizeof(D3DXQUATERNION));


		fp->read(read, sizeof(unsigned int));
		memcpy(&tmp.light_type, read, sizeof(unsigned int));

		fp->read(read, sizeof(float));
		memcpy(&tmp.field_of_view, read, sizeof(float));

		fp->read(read, sizeof(D3DCOLORVALUE));
		memcpy(&tmp.color, read, sizeof(D3DCOLORVALUE));

		ret.push_back(tmp);
	}

	
	return ret;
}

vector<entity> cReadOwmdl::GetEntities(ifstream * fp, unsigned int size)
{
	vector<entity> ret;
	entity tmp;
	int cnt = 0;

	/*
	
	
struct entity {
	std::string material_file;
	unsigned int record_count;
	std::vector<record> records;
	
	*/
	while (cnt++ < size)
	{
		char tmp_str;
		char read[1024];

		do {
			fp->read(&tmp_str, 1);
			if (tmp_str != NULL)
			{
				(tmp.material_file).append(1, tmp_str);
			}
		} while (tmp_str != NULL);


		fp->read(read, sizeof(unsigned int));
		memcpy(&tmp.record_count, read, sizeof(unsigned int));

		tmp.records = GetRecords(fp, tmp.record_count);

		ret.push_back(tmp);
	}
	return ret;
}

vector<record> cReadOwmdl::GetRecords(ifstream * fp, unsigned int size)
{
	vector<record> ret;
	record tmp;

	/*
	struct record {

	D3DXVECTOR3 pos;
	D3DXVECTOR3 vecScale;
	D3DXQUATERNION quat;

	};
*/
	int cnt = 0;

	while (cnt++ < size)
	{
		char tmp_str;
		unsigned char read[1024];

		fp->read((char*)read, sizeof(D3DXVECTOR3));
		memcpy(&tmp.pos, read, sizeof(D3DXVECTOR3));
		printf("tmp.pos = %f %f %f\n", tmp.pos.x, tmp.pos.y, tmp.pos.z);

		fp->read((char*)read, sizeof(D3DXVECTOR3));
		memcpy(&tmp.vecScale, read, sizeof(D3DXVECTOR3));

		fp->read((char*)read, sizeof(D3DXQUATERNION));
		memcpy(&tmp.quat, read, sizeof(D3DXQUATERNION));

		ret.push_back(tmp);
	}
	return ret;
}

void cReadOwmdl::PrintData(string outputFileName)
{
	ofstream file;
	file.open(outputFileName, ios::out | ios::trunc);
	/*
	unsigned short major;
	unsigned short minor;
	std::string name;
	unsigned int object_count;
	unsigned int detail_count;
	unsigned int light_count;
	std::vector<object> objects;
		std::string model_file;
		unsigned int entity_count;
		std::vector<entity> entities;
			std::string material_file;
			unsigned int record_count;
			std::vector<record> records;
				D3DXVECTOR3 pos;
				D3DXVECTOR3 vecScale;
				D3DXQUATERNION quat;
	std::vector<detail> details;
		std::string			model_file;
		std::string			material_file;
		D3DXVECTOR3			pos;
		D3DXVECTOR3			vecScale;
		D3DXQUATERNION		quat;
	std::vector<light> lights;
		D3DXVECTOR3 pos;
		D3DXQUATERNION quat;
		unsigned int light_type;
		float field_of_view;
		D3DCOLORVALUE color;
	*/

	if (file.is_open())
	{
		char tmp[1024];

		itoa(owmap.major, tmp, 10);
		file << "Major : " << tmp << "\n";

		itoa(owmap.minor, tmp, 10);
		file << "Minor : " << tmp << "\n";

		file << "Map Name : " << owmap.name << "\n";

		file.close();	
	}
	else
	{
		printf("Couldn't open File. Program will be quit.");
		int a;
		scanf_s("%d", a);
		PostQuitMessage(0);
	}
	
}
