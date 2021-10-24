#include "pch.h"
#include <glad/glad.h>
#include "Enum.h"

//VBO usage types
Enum Enum::STATIC_USAGE = Enum(GL_STATIC_DRAW);
Enum Enum::STREAM_USAGE = Enum(GL_STREAM_DRAW);
Enum Enum::DYNAMIC_USAGE = Enum(GL_DYNAMIC_DRAW);

//datatypes
Enum Enum::FLOAT = Enum(GL_FLOAT);
Enum Enum::FALSE = Enum(GL_FALSE);
Enum Enum::TRUE = Enum(GL_TRUE);

//texture
Enum Enum::TEXTURE_WRAP_CLAMP_TO_EDGE = Enum(GL_CLAMP_TO_EDGE);
Enum Enum::TEXTURE_WRAP_REPEAT = Enum(GL_REPEAT);
Enum Enum::TEXTURE_WRAP_MIRROR = Enum(GL_MIRRORED_REPEAT);
Enum Enum::TEXTURE_FILTER_LINEAR = Enum(GL_LINEAR);
Enum Enum::TEXTURE_FILTER_NEAREST = Enum(GL_NEAREST);
Enum Enum::TEXTURE_CONTAINER_0 = Enum(GL_TEXTURE0);
Enum Enum::COLOR_CHANNEL_RGB = Enum(GL_RGB);
Enum Enum::COLOR_CHANNEL_RGBA = Enum(GL_RGBA);

//primitives
Enum Enum::TRIANGLES = Enum(GL_TRIANGLES);

//buffers
Enum Enum::COLOR_DEPTH_BUFFER_BIT = Enum(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//test
Enum Enum::DEPTH_TEST = Enum(GL_DEPTH_TEST);