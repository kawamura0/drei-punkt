#pragma once
#include"../../ESGLib.h"

class Cable
{
public:
	Cable(){};
	~Cable(){};

	bool Initialize();
	bool ModelInitialize();
	bool ObbInitialize();
	bool StatusInitialize();

	void Update();
	
	void Draw3D();
	void ObbDraw();

private:

	Material mtrl;

	MODEL cable_[3];
	MODEL obb_mad_;

	float R_;
	float G_;
	float B_;
	float dist[3];

	OrientedBoundingBox cable_obb_;
	
};