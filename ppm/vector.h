#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef vec3 color3;
typedef vec3 point3;

extern float vec4_dot(vec4 u, vec4 v);
extern vec4 vec4_add(vec4 u, vec4 v);
extern vec4 vec4_substract(vec4 u, vec4 v); // a - b
extern vec4 vec4_mul(vec4 u, float s);
extern float vec4_distance(vec4 u);

extern float vec3_dot(vec3 u, vec3 v);
extern vec3 vec3_cross(vec3 u, vec3 v);
extern vec3 vec3_add(vec3 u, vec3 v);
extern vec3 vec3_substract(vec3 u, vec3 v); // a - b
extern vec3 vec3_mul(vec3 u, float s);
extern float vec3_distance(vec3 u);

#ifdef VECTOR_IMPLEMENTATION

#include <math.h>

inline float vec4_dot(vec4 u, vec4 v)
{
	return (u.x * v.x)
		 + (u.y * v.y)
		 + (u.z * v.z)
		 + (u.w * v.w);
}

inline vec4 vec4_add(vec4 u, vec4 v)
{
	return {
		.x = u.x + v.x,
		.y = u.y + v.y,
		.z = u.z + v.z,
		.w = u.w + v.w,
	};
}

inline vec4 vec4_substract(vec4 u, vec4 v)
{
	return {
		.x = u.x - v.x,
		.y = u.y - v.y,
		.z = u.z - v.z,
		.w = u.w - v.w,
	};
}

inline vec4 vec4_mul(vec4 u, float s)
{
	return {
		.x = u.x * s,
		.y = u.y * s,
		.z = u.z * s,
		.w = u.w * s,
	};
}

inline float vec4_distance(vec4 u)
{
	return sqrtf(u.x*u.x + u.y*u.y + u.z*u.z + u.w*u.w);
}

inline float vec3_dot(vec3 u, vec3 v)
{
	return (u.x * v.x)
		 + (u.y * v.y)
		 + (u.z * v.z);
}

inline vec3 vec3_cross(vec3 u, vec3 v)
{
	return {
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x,
	};
}

inline vec3 vec3_add(vec3 u, vec3 v)
{
	return {
		.x = u.x + v.x,
		.y = u.y + v.y,
		.z = u.z + v.z,
	};
}

inline vec3 vec3_substract(vec3 u, vec3 v)
{
	return {
		.x = u.x - v.x,
		.y = u.y - v.y,
		.z = u.z - v.z,
	};
}

inline vec3 vec3_mul(vec3 u, float s)
{
	return {
		.x = u.x * s,
		.y = u.y * s,
		.z = u.z * s,
	};
}

inline float vec3_distance(vec3 u)
{
	return sqrtf(u.x*u.x + u.y*u.y + u.z*u.z);
}

#endif // VECTOR_IMPLEMENTATION

#endif // VECTOR_H
