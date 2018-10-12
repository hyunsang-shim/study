#include "stdafx.h"
#include "cASELoader.h"


cASELoader::cASELoader()
{
}


cASELoader::~cASELoader()
{
}

vector<ASE_Obj> cASELoader::ParseASE(string FileName)
{

	ifstream					in;
	string						newline;
	char						indicator[128];
	vector<ASE_Obj>				ret;
	ASE_Obj						tmpRet;
	int							cntLines = 0;
	vector<D3DXVECTOR3>			v_vecVertices;
	vector<D3DXVECTOR3>			v_vecNormals;
	vector<D3DXVECTOR2>			v_vecUVs;
	vector<int>					v_nFaceList;
	vector<int>				v_nTextureFaceList;
	vector<int>					v_nNormalIndexForFace;
	ST_PNT_VERTEX				tmpPNT;

	ZeroMemory(&ret, sizeof(ret));

	in.open("./woman/woman_01_all.ASE", ios::in);
	cntLines++;

	getline(in, newline);
	sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
	string tmp = indicator;

	// continue when valid file
	if ( tmp == ID_FILEID)
	{
		while (!in.eof())
		{
			cntLines++;
			getline(in, newline);
			sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
			tmp = indicator;
			printf("Line #%05d\n", cntLines);

			if (tmp == ID_COMMENT) continue;	// skip comment
			else if (tmp == ID_GEOMETRY)		// mesh info
			{
				cntLines++;
				getline(in, newline);
				sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
				tmp = indicator;

				while (tmp != "}")
				{

					if (tmp == ID_NODE_NAME)
					{
						tmpRet.MyNodeName = newline.substr(newline.find_first_of("\"")+1, newline.find_last_of("\"") - newline.find_first_of("\"") - 1);
					}	
					else if (tmp == ID_NODE_PARENT)
					{
						tmpRet.ParentNodeName = newline.substr(newline.find_first_of("\"") + 1, newline.find_last_of("\"") - newline.find_first_of("\"") - 1);
					}
					else if (tmp == ID_NODE_TM)
					{
						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;

						while (tmp != "}")
						{
							

							if (tmp == ID_NODE_NAME)
							{
								tmpRet.meshName = newline.substr(newline.find_first_of("\"") + 1, newline.find_last_of("\"") - newline.find_first_of("\"") - 1);
								printf("Line#%05d ID_NODE_NAME [%s]\n", cntLines, tmpRet.meshName.c_str());
							}
							else if (tmp == ID_TM_ROW0)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);
								tmpRet.LocalWorld._11 = x;
								tmpRet.LocalWorld._12 = y;
								tmpRet.LocalWorld._13 = z;
								tmpRet.LocalWorld._14 = 0.0f;

							}
							else if (tmp == ID_TM_ROW2)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);
								tmpRet.LocalWorld._21 = x;
								tmpRet.LocalWorld._22 = y;
								tmpRet.LocalWorld._23 = z;
								tmpRet.LocalWorld._24 = 0.0f;

							}
							else if (tmp == ID_TM_ROW1)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);
								tmpRet.LocalWorld._31 = x;
								tmpRet.LocalWorld._32 = y;
								tmpRet.LocalWorld._33 = z;
								tmpRet.LocalWorld._34 = 0.0f;

							}
							else if (tmp == ID_TM_ROW3)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);

								tmpRet.LocalWorld._41 = x;
								tmpRet.LocalWorld._42 = y;
								tmpRet.LocalWorld._43 = z;
								tmpRet.LocalWorld._44 = 1.0f;

							}
							else if (tmp == ID_TM_POS)
							{
								float x, y, z;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);

								tmpRet.LocalPosition = D3DXVECTOR3(x, y, z);

							}
							else if (tmp == ID_TM_SCALE)
							{
								float scaleX, scaleY, scaleZ;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &scaleX, &scaleZ, &scaleY);

								tmpRet.LocalScale = D3DXVECTOR3(scaleX, scaleY, scaleZ);
							}

							cntLines++;
							getline(in, newline);
							sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
							tmp = indicator;

						}

					}
					else if (tmp == ID_MESH)
					{
						printf("Line #%05d - ID_MESH Start [ %s ]\n", cntLines, tmpRet.MyNodeName.c_str());

						v_vecVertices.resize(0);
						v_vecNormals.resize(0);
						v_vecUVs.resize(0);
						v_nFaceList.resize(0);
						v_nNormalIndexForFace.resize(0);


						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;

						while (tmp != "}")
						{							
							if (tmp == ID_TIMEVALUE)
							{
								
								unsigned short timevalue;
								sscanf_s(newline.c_str(), "%*s, %d", &timevalue);
								tmpRet.Timevalue = timevalue;
							}
							else if (tmp == ID_MESH_VERTEX_LIST)
							{

								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								// Read and Load vertices list
								while (tmp != "}")
								{
									float x, y, z;
									sscanf_s(newline.c_str(), "%*s %*d %f %f %f", &x, &z, &y);
									v_vecVertices.push_back(D3DXVECTOR3(x, y, z));
			

									cntLines++;
									getline(in, newline);
									sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
									tmp = indicator;
								}	
							}
							else if (tmp == ID_MESH_FACE_LIST)
							{

								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								// Read and Load Face vertex index list
								while (tmp != "}")
								{				

										int a, c, b;
										sscanf_s(newline.c_str(), "%*s %*s %*s %d %*s %d %*s %d", &a, &c, &b);

										v_nFaceList.push_back(a);
										v_nFaceList.push_back(b);
										v_nFaceList.push_back(c);


										cntLines++;
										getline(in, newline);
										sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
										tmp = indicator;
								}			
								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;
							}
							else if (tmp == ID_MESH_TVERTLIST)
							{

								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								// Read and Load UV vertex list
								while (tmp != "}")
								{			
									

									float u, v, z;
									sscanf_s(newline.c_str(), "%*s %*d %f %f", &u, &v);

									v_vecUVs.push_back(D3DXVECTOR2(u, 1.0f - v));

									cntLines++;
									getline(in, newline);
									sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
									tmp = indicator;
								}

								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;
								
							}
							else if (tmp == ID_MESH_TFACELIST)
							{
								
								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								// Read and Load UV vertex index list
								while (tmp != "}")
								{
									int a, c, b;
									sscanf_s(newline.c_str(), "%*s %*d %d %d", &a, &b);

									v_nTextureFaceList.push_back(a);
									v_nTextureFaceList.push_back(b);
									
									cntLines++;
									getline(in, newline);
									sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
									tmp = indicator;

								}

							}
							else if (tmp == ID_MESH_NORMALS)
							{
								

								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								while (tmp != "}")
								{
									if (tmp == ID_MESH_FACENORMAL)	{}
									else if (tmp == ID_MESH_VERTEXNORMAL)
									{
										int id;
										float x, y, z;
										sscanf_s(newline.c_str(), "%*s %d %f %f %f", &id, &x, &z, &y);

										v_vecNormals.push_back(D3DXVECTOR3(x, y, z));	
										v_nNormalIndexForFace.push_back(id);
									}

									cntLines++;
									getline(in, newline);
									sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
									tmp = indicator;
								}
								printf("\nDone @ Line #%05d\n", cntLines);

								
							}

							cntLines++;
							getline(in, newline);
							sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
							tmp = indicator;
						}

						// finishing mesh info Reading
						// load'em
						for (int i = 0; i < v_nFaceList.size(); i++)
						{
							tmpPNT.p = v_vecVertices[v_nFaceList[i]];

							tmpPNT.normal = v_vecNormals[v_nNormalIndexForFace[i]];

							if (!v_nTextureFaceList.empty())
							{
							
								tmpPNT.texture = D3DXVECTOR2(v_vecUVs[v_nTextureFaceList[i*2]].x, v_vecUVs[v_nTextureFaceList[i * 2+1]].y);
							}
							else
							{
								tmpPNT.texture = D3DXVECTOR2(0.0f, 0.0f);
							}

							tmpRet.vPNT_VERTEX.push_back(tmpPNT);	
						}

						ret.push_back(tmpRet);


						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;
					}

					cntLines++;
					getline(in, newline);
					sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
					tmp = indicator;
				}
			}

			cntLines++;
			getline(in, newline);
			sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
			tmp = indicator;
		}
	}

	return ret;
}


