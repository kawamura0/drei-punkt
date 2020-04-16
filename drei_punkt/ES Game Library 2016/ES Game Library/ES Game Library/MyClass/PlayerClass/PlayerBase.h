#pragma once

#include"../../ESGLib.h"

class PlayerBase {
public:
	PlayerBase() {};
	~PlayerBase() {};

	bool Initialize();

	void Update();
	void Draw3D();
	void DrawUI();

private:

};