#pragma once

mesh FetchMesh(const char * path, float scale, vert origin) {
	mesh ret;
	ifstream infile(path);
	char type;
	float data0;	float data1;	float data2;
	string sdata0;	string sdata1;	string sdata2;
	string temp;
	int linenum = 0;	int vertnum = 0;	int edgenum = 0;	int facenum = 0;
	int vnormnum = 0;	int fnormnum = 0;	int cordnum = 0;	int fcordnum = 0;
	string snorm0;	string snorm1;	string snorm2;
	int inorm0;	int inorm1;	int inorm2;
	string vert0;	string vert1;	string vert2;
	int itex0;	int itex1;	int itex2;
	string tex0;	string tex1;	string tex2;
	for (string line; std::getline(infile, line);) {
		istringstream in(line);
		in >> type;
		if (type == 'o') {
			in >> temp;
			ret.ref = temp;
		}
		else {
			if (type == 's') {
				in >> temp;
				if (temp == "off") {
					ret.sh$ = 0;
				}
				else {
					ret.sh$ = strtof(temp.c_str(), 0);
				}
			}
			else {
				if (type == 'v') {
					in >> data0 >> data1 >> data2;
					ret.varr[vertnum].x = (data0);
					ret.varr[vertnum].z = (data1);
					ret.varr[vertnum].y = (data2);
					vertnum++;
				}
				else {
					if (type == 't') {
						in >> data0 >> data1;
						ret.tcarr[cordnum].u = data0;
						ret.tcarr[cordnum].v = data1;
						cordnum++;
					}
					else {
						if (type == 'n') {
							in >> data0 >> data1 >> data2;
							ret.vnarr[vnormnum].x = (data0 * scale) + origin.x;
							ret.vnarr[vnormnum].y = (data1 * scale) + origin.y;
							ret.vnarr[vnormnum].z = (data2 * scale) + origin.z;
							vnormnum++;
						}
						else {
							if (type == 'f') {
								// vertex indice / texture coordinate / vertex normal								
								in >> sdata0 >> sdata1 >> sdata2;
								vert0 = sdata0.substr(0, sdata0.find("/"));		vert1 = sdata1.substr(0, sdata1.find("/"));		vert2 = sdata2.substr(0, sdata2.find("/"));
								ret.farr[facenum].vr1 = stoi(vert0) - 1;	ret.farr[facenum].vr2 = stoi(vert1) - 1;	ret.farr[facenum].vr3 = stoi(vert2) - 1;
								ret.farr[facenum].c.x = (ret.varr[ret.farr[facenum].vr1].x + ret.varr[ret.farr[facenum].vr2].x + ret.varr[ret.farr[facenum].vr3].x) / 3;
								ret.farr[facenum].c.y = (ret.varr[ret.farr[facenum].vr1].y + ret.varr[ret.farr[facenum].vr2].y + ret.varr[ret.farr[facenum].vr3].y) / 3;
								ret.farr[facenum].c.z = (ret.varr[ret.farr[facenum].vr1].z + ret.varr[ret.farr[facenum].vr2].z + ret.varr[ret.farr[facenum].vr3].z) / 3;
								tex0 = sdata0.substr(sdata0.find("/"), sdata0.find_last_of(("/")));
								tex1 = sdata1.substr(sdata1.find("/"), sdata1.find_last_of(("/")));
								tex2 = sdata2.substr(sdata2.find("/"), sdata2.find_last_of(("/")));
								if (!tex0.length() > 0 && !tex1.length() > 0 && !tex2.length() > 0) {
									itex0 = stoi(tex1);	itex1 = stoi(tex1);	itex2 = stoi(tex2);
									ret.carr[facenum].s1.u = ret.tcarr[itex0].u;
									ret.carr[facenum].s2.u = ret.tcarr[itex1].u;
									ret.carr[facenum].s3.u = ret.tcarr[itex2].u;
									ret.carr[facenum].s1.v = ret.tcarr[itex0].v;
									ret.carr[facenum].s2.v = ret.tcarr[itex1].v;
									ret.carr[facenum].s3.v = ret.tcarr[itex2].v;
								}
								snorm0 = sdata0.substr(sdata0.find_last_of("/") + 1, sdata0.length());
								snorm1 = sdata1.substr(sdata1.find_last_of("/") + 1, sdata1.length());
								snorm2 = sdata2.substr(sdata2.find_last_of("/") + 1, sdata2.length());
								if (snorm0.length() > 0 && snorm1.length() > 0 && snorm2.length() > 0) {
									inorm0 = stoi(snorm0) - 1;		inorm1 = stoi(snorm1) - 1;		inorm2 = stoi(snorm2) - 1;
									ret.fnarr[facenum].v1.x = ret.vnarr[inorm0].x;
									ret.fnarr[facenum].v1.y = ret.vnarr[inorm0].y;
									ret.fnarr[facenum].v1.z = ret.vnarr[inorm0].z;
									ret.fnarr[facenum].v2.x = ret.vnarr[inorm1].x;
									ret.fnarr[facenum].v2.y = ret.vnarr[inorm1].y;
									ret.fnarr[facenum].v2.z = ret.vnarr[inorm1].z;
									ret.fnarr[facenum].v3.x = ret.vnarr[inorm2].x;
									ret.fnarr[facenum].v3.y = ret.vnarr[inorm2].y;
									ret.fnarr[facenum].v3.z = ret.vnarr[inorm2].z;
									ret.fnarr[facenum].v4.x = (ret.vnarr[inorm0].x + ret.vnarr[inorm1].x + ret.vnarr[inorm2].x) / 3;
									ret.fnarr[facenum].v4.y = (ret.vnarr[inorm0].y + ret.vnarr[inorm1].y + ret.vnarr[inorm2].y) / 3;
									ret.fnarr[facenum].v4.z = (ret.vnarr[inorm0].z + ret.vnarr[inorm1].z + ret.vnarr[inorm2].z) / 3;
									ret.fnarr[facenum].v4 = NormalizeVector(ret.fnarr[facenum].v4);
								}
								facenum++;
							}
						}
					}
				}
			}
		}
	}
	return ret;
}
