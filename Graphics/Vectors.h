#pragma once

namespace vect
{
	struct vec2
	{
		float x, y;
		vec2() = default;
		vec2(float val)
		{
			x = val;
			y = val;
		}
		vec2(float valx, float valy)
		{
			x = valx;
			y = valy;
		}
	};

	struct vec3
	{
		float x, y, z;
		vec3() = default;
		vec3(float val)
		{
			x = val;
			y = val;
			z = val;
		}
		vec3(float valx, float valy, float valz)
		{
			x = valx;
			y = valy;
			z = valz;
		}
	};

	struct vec4
	{
		float x, y, z, w;
		vec4() = default;
		vec4(float val)
		{
			w = val;
			x = val;
			y = val;
			z = val;
		}
		vec4(float valw, float valx, float valy, float valz)
		{
			w = valw;
			x = valx;
			y = valy;
			z = valz;
		}
	};
}
