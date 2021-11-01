#pragma once

namespace mat
{
	struct mat4
	{
		float m[4][4] = 
		{ 
			0.0f, 0.0f ,0.0f ,0.0f,
			0.0f, 0.0f ,0.0f ,0.0f,
			0.0f, 0.0f ,0.0f ,0.0f,
			0.0f, 0.0f ,0.0f ,0.0f 
		};
		mat4(float val)
		{
			m[0][0] = val;
			m[1][1] = val;
			m[2][2] = val;
			m[3][3] = val;
		}
	};
}