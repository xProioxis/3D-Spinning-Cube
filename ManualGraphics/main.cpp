#include <iostream>
#include <numeric>
#include "screen.h"

struct vec3
{
	float x, y, z;
};

struct connection
{
	int a, b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
	float rad = 0;
	rad = x; // this IS NOT the x point, this is just how much other pts are rotd.
	point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
	point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

	rad = y;
	point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
	point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

	rad = z;
	point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
	point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
	float diff_x = x2 - x1;
	float diff_y = y2 - y1;

	float length = std::sqrt((diff_x * diff_x) + (diff_y * diff_y));
	float angle = std::atan2(diff_y, diff_x);

	for (int i = 0; i < length; i++)
	{
		screen.pixel(x1 + std::cos(angle) * i,
			y1 + std::sin(angle) * i
		);
	}

}

int main()
{
	Screen screen;


	std::vector<vec3> points{
		{200,200,200},
		{300,200,200},
		{300,300,200},
		{200,300,200},

		{200,200,300},
		{300,200,300},
		{300,300,300},
		{200,300,300}
	};

	std::vector<connection> connections{
		// numbers represent indices in points vector to connect
		{0, 4}, // connecting front and back
		{1, 5},
		{2, 6},
		{3, 7}, 

		{0, 1}, // front faces (this looks like a loop :])
		{1, 2},
		{2, 3},
		{3, 0},

		{4, 5}, // back face
		{5, 6},
		{6, 7},
		{7, 4},
	};

	vec3 c = { 0, 0, 0 }; // centroid
	for (auto& pt : points)
	{
		c.x += pt.x; // sum up all pts, will help to find average for centroid
		c.y += pt.y;
		c.z += pt.z;
	}

	c.x /= points.size(); // average for each point, to find centroid
	c.y /= points.size();
	c.z /= points.size();

	while (true)
	{
		for (auto& point : points)
		{
			// must add and subtract to rotate pt around center of cube
			// if not, rotation will cause points to go out of screen
			point.x -= c.x;
			point.y -= c.y;
			point.z -= c.z;

			rotate(point, 0.012, 0.006, 0.024);

			point.x += c.x;
			point.y += c.y;
			point.z += c.z;
			screen.pixel(point.x, point.y);
			// z's only purpose is to be a frame of ref. for rotation
		}
		for (auto& conn : connections)
		{ // drawing a line for each necessary point
			line(screen, points[conn.a].x, points[conn.a].y,
				         points[conn.b].x, points[conn.b].y);
		}
		screen.show();
		screen.clear();

		screen.input();
		SDL_Delay(30);
	}
	return 0;
	
}