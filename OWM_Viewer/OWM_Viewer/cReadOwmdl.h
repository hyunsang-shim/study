#pragma once


struct detail {
	std::string			model_file;
	std::string			material_file;
	D3DXVECTOR3			pos;
	D3DXVECTOR3			vecScale;
	D3DXQUATERNION		quat;
};

struct light {

	D3DXVECTOR3 pos;
	D3DXQUATERNION quat;
	unsigned int light_type;
	float field_of_view;
	D3DCOLORVALUE color;
};
struct record {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vecScale;
	D3DXQUATERNION quat;
};

struct entity {
	std::string material_file;
	unsigned int record_count;
	std::vector<record> records;
};

struct object {
	std::string model_file;
	unsigned int entity_count;
	std::vector<entity> entities;
};

struct OWMAP {
	unsigned short major;
	unsigned short minor;
	std::string name;
	unsigned int object_count;
	unsigned int detail_count;
	unsigned int light_count;
	std::vector<object> objects;
	std::vector<detail> details;
	std::vector<light> lights;

	unsigned int	unknown1[2];
	byte			unknown2[4];
	unsigned int	unknown3[2];
	D3DXVECTOR3		unknownPos1;
	D3DXQUATERNION	unknownQuat1;
	D3DXVECTOR3		unknownPos2;
	D3DXQUATERNION	unknownQuat2;
	D3DXVECTOR3		unknownPos3;
	D3DXQUATERNION	unknownQuat3;
	float			unknown4[2];
	unsigned int	unknown5;
	short			unknown6[2];
	unsigned int	unknown7[2];
};


class cReadOwmdl
{
public:
	cReadOwmdl();
	~cReadOwmdl();
	OWMAP ReadFile(std::string Filename);
	vector<object> GetObjects(ifstream* fp, unsigned int size);
	vector<detail> GetDetails(ifstream* fp, unsigned int size);
	vector<light> GetLights(ifstream* fp, unsigned int size);
	vector<entity> GetEntities(ifstream* fp, unsigned int size);
	vector<record> GetRecords(ifstream* fp, unsigned int size);
	void PrintData(string outputFileName);

private:	
	OWMAP			owmap;

};

