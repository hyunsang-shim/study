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
	vector<int>					v_nTextureFaceList;
	vector<int>					v_nNormalIndexForFace;
	ST_PNT_VERTEX				tmpPNT;
	vector<string>				v_TexturePath;
	vector<D3DMATERIAL9>		v_mat9Material;
	vector<LPDIRECT3DTEXTURE9>	v_tx9Texture;
	D3DMATERIAL9				tmpMaterial;
	LPDIRECT3DTEXTURE9			tmpTexture;

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

			if (tmp == ID_COMMENT) continue;	// skip comment
			else if (tmp == ID_MATERIAL_LIST)
			{
				cntLines++;
				getline(in, newline);
				sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
				tmp = indicator;

				while (tmp != "}")
				{
					if (tmp == ID_MATERIAL)
					{
						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;

						while (tmp != "}")
						{
							if (tmp == ID_AMBIENT)
							{								
								sscanf_s(newline.c_str(), "%*s %f %f %f", &tmpMaterial.Ambient.r, &tmpMaterial.Ambient.g, &tmpMaterial.Ambient.b);
								tmpMaterial.Ambient.a = 1.0f;
							}
							else if (tmp == ID_DIFFUSE)
							{								
								sscanf_s(newline.c_str(), "%*s %f %f %f", &tmpMaterial.Diffuse.r, &tmpMaterial.Diffuse.g, &tmpMaterial.Diffuse.b);
								tmpMaterial.Diffuse.a = 1.0f;
							}
							else if (tmp == ID_SPECULAR)
							{								
								sscanf_s(newline.c_str(), "%*s %f %f %f", &tmpMaterial.Specular.r, &tmpMaterial.Specular.g, &tmpMaterial.Specular.b);
								tmpMaterial.Specular.a = 1.0f;
							}
							else if (tmp == ID_SHINE_STRENGTH)
							{								
								sscanf_s(newline.c_str(), "%*s %f", &tmpMaterial.Power);
							}
							else if (tmp == ID_MAP_DIFFUSE)
							{
								cntLines++;
								getline(in, newline);
								sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
								tmp = indicator;

								while (tmp != "}")
								{
									if (tmp == ID_BITMAP)
									{
										v_TexturePath.push_back(newline.substr(newline.find_first_of("\"") + 1, newline.find_last_of("\"") - newline.find_first_of("\"") - 1));
										D3DXCreateTextureFromFileA(g_pD3DDevice, v_TexturePath[v_TexturePath.size() - 1].c_str(), &tmpTexture);
										v_tx9Texture.push_back(tmpTexture);
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

						tmpMaterial.Emissive.r = 0.0f;
						tmpMaterial.Emissive.g = 0.0f;
						tmpMaterial.Emissive.b = 0.0f;
						tmpMaterial.Emissive.a = 1.0f;

						v_mat9Material.push_back(tmpMaterial);
					}
					cntLines++;
					getline(in, newline);
					sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
					tmp = indicator;
				}
			}
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
								tmpRet.matMyWorld._11 = x;
								tmpRet.matMyWorld._12 = y;
								tmpRet.matMyWorld._13 = z;
								tmpRet.matMyWorld._14 = 0.0f;

							}
							else if (tmp == ID_TM_ROW2)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);
								tmpRet.matMyWorld._21 = x;
								tmpRet.matMyWorld._22 = y;
								tmpRet.matMyWorld._23 = z;
								tmpRet.matMyWorld._24 = 0.0f;

							}
							else if (tmp == ID_TM_ROW1)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);
								tmpRet.matMyWorld._31 = x;
								tmpRet.matMyWorld._32 = y;
								tmpRet.matMyWorld._33 = z;
								tmpRet.matMyWorld._34 = 0.0f;

							}
							else if (tmp == ID_TM_ROW3)
							{
								float x, z, y;
								sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &z, &y);

								tmpRet.matMyWorld._41 = x;
								tmpRet.matMyWorld._42 = y;
								tmpRet.matMyWorld._43 = z;
								tmpRet.matMyWorld._44 = 1.0f;

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
						if (!tmpRet.ParentNodeName.empty())
						{
							for (int i = 0; i < ret.size(); i++)
							{
								if (ret[i].ParentNodeName == tmpRet.ParentNodeName)
								{
									// 부모 월드 노드의 역행렬 X 내 월드 행렬 = 내 로컬 행렬
									float det = D3DXMatrixDeterminant(&ret[i].ParentWorld);
									D3DXMATRIXA16 ParentInverse;
									D3DXMatrixInverse(&ParentInverse, &det, &ret[i].ParentWorld);
									tmpRet.matMyLocal = ParentInverse * tmpRet.matMyWorld;
									tmpRet.parentNodeIdx = i;
									break;
								}
								else
								{
									tmpRet.matMyLocal = tmpRet.matMyWorld;
									tmpRet.parentNodeIdx = -1;
								}
							}
						}
						else
							tmpRet.matMyLocal = tmpRet.matMyWorld;
					}
					else if (tmp == ID_MESH)
					{
						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;

						while (tmp != "}")
						{							
							if (tmp == ID_TIMEVALUE)
							{
								unsigned short timevalue;
								sscanf_s(newline.c_str(), "%*s, %hd", &timevalue);
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
									sscanf_s(newline.c_str(), "%*s %*d %f %f %f", &x, &y, &z);
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
									float u, v;
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
									sscanf_s(newline.c_str(), "%*s %*d %d %d %d", &a, &c, &b);

									v_nTextureFaceList.push_back(a);
									v_nTextureFaceList.push_back(b);
									v_nTextureFaceList.push_back(c);
									
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
								printf("v_vecVertices : %d\n", v_vecVertices.size());
								printf("v_nFaceList : %d\n", v_nFaceList.size()); 
								printf("v_vecUVs : %d\n", v_vecUVs.size()); 
								printf("v_nTextureFaceList : %d\n", v_nTextureFaceList.size());
								printf("vVecNormals : %d\n", v_vecNormals.size());
								printf("v_nNormalIndexForFace : %d\n\n", v_nNormalIndexForFace.size());
								
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
							
								//printf("i : %d, size() : %d value = %d\n", i, v_nTextureFaceList.size(), v_nTextureFaceList[i]);
								tmpPNT.texture = v_vecUVs[v_nTextureFaceList[i]];
							}
							else
							{
								tmpPNT.texture = D3DXVECTOR2(0.0f, 0.0f);
							}

							tmpRet.vPNT_VERTEX.push_back(tmpPNT);	
						}



						cntLines++;
						getline(in, newline);
						sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
						tmp = indicator;
					}
					else if (tmp == ID_TM_ANIMATION)
					{					}
					else if (tmp == ID_MATERIAL_REF)
					{
						int materialIdx = -1;
						sscanf_s(newline.c_str(), "%*s %d", &materialIdx);
						if (materialIdx >= 0)
						{
							tmpRet.mat9Material = v_mat9Material[materialIdx];
							tmpRet.tx9Texture = v_tx9Texture[materialIdx];

							string tmpTxName = v_TexturePath[materialIdx];
							size_t found = tmpTxName.find_last_of("/");

							if (found != tmpTxName.npos)
								tmpTxName.erase(found + 1);

							tmpRet.TextureName = tmpTxName;
						}

						ret.push_back(tmpRet);

						v_vecVertices.resize(0);
						v_vecNormals.resize(0);
						v_vecUVs.resize(0);
						v_nFaceList.resize(0);
						v_nNormalIndexForFace.resize(0);
						v_nTextureFaceList.resize(0);
						ZeroMemory(&tmpPNT, sizeof(tmpPNT));
						ZeroMemory(&tmpMaterial, sizeof(tmpMaterial));
						ZeroMemory(&tmpTexture, sizeof(tmpTexture));

					}
					/////////////////////////////////////////////////////////////
					cntLines++;
					getline(in, newline);
					sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
					tmp = indicator;
				}
			}

		}
	}

	return ret;
}


