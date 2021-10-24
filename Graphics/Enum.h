#pragma once

typedef unsigned int GLenum;
struct Enum
{
	GLenum val;
	static Enum STATIC_USAGE;
	static Enum STREAM_USAGE;
	static Enum DYNAMIC_USAGE;
	static Enum FLOAT;
	static Enum FALSE;
	static Enum TRUE;
	static Enum TEXTURE_WRAP_CLAMP_TO_EDGE;
	static Enum TEXTURE_WRAP_REPEAT;
	static Enum TEXTURE_WRAP_MIRROR;
	static Enum TEXTURE_FILTER_LINEAR;
	static Enum TEXTURE_FILTER_NEAREST;
	static Enum TEXTURE_CONTAINER_0;
	static Enum COLOR_CHANNEL_RGB;
	static Enum COLOR_CHANNEL_RGBA;
	static Enum TRIANGLES;
	static Enum COLOR_DEPTH_BUFFER_BIT;
	static Enum DEPTH_TEST;
private:
	Enum(GLenum value)
	{
		val = value;
	}
};