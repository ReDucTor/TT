#pragma once
#include "Surface.h"
#include <vector>
#include <sstream>
#include <iomanip>

class AnimatedSurface {
public:
	AnimatedSurface(std::string path, unsigned int nSurfaces, unsigned int framePerSurf)
		:
		nSurfaces(nSurfaces),
		framePerSurf(framePerSurf),
		currentSurface(0),
		frame(0),
		basex(0),
		basey(0)
	{
		for (unsigned int index = 0; index < nSurfaces; index++) {
			std::stringstream s;
			s << std::setw(4) << std::setfill('0') << index;
			std::string filename = path + s.str() + ".png";
			Surfaces.emplace_back(Surface::FromFile(filename));
			s.str("");
		}
	}
	AnimatedSurface(std::string path, unsigned int nSurfaces, unsigned int framePerSurf, float basex, float basey)
		:
		nSurfaces(nSurfaces),
		framePerSurf(framePerSurf),
		currentSurface(0),
		frame(0),
		basex(basex),
		basey(basey)
	{
		for (unsigned int index = 0; index < nSurfaces; index++) {
			std::stringstream s;
			s << std::setw(4) << std::setfill('0') << index;
			std::string filename = path + s.str() + ".png";
			Surfaces.emplace_back(Surface::FromFile(filename));
			s.str("");
		}
	}
	~AnimatedSurface() {
		Surfaces.clear();
	}
	void Draw(int xoff, int yoff, Graphics &gfx) {
		Surfaces[currentSurface].Draw(xoff + basex, yoff + basey, gfx);
	}
	void DrawAlfa(float xoff, float yoff, Graphics& gfx) {
		Surfaces[currentSurface].DrawAlfa(xoff + basex, yoff + basey, gfx);
	}
	void Update() {
		frame++;
		if (frame == framePerSurf) {
			currentSurface++;
			currentSurface %= nSurfaces;
			frame = 0;
		}
	}
private:
	std::vector<Surface> Surfaces;
	const unsigned int nSurfaces;
	const unsigned int framePerSurf;
	unsigned currentSurface;
	unsigned int frame;
	float basex;
	float basey;
};