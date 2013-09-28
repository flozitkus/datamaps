#include <iostream>
#include <fstream>
#include <string>
#include "vector_tile.pb.h"

#define XMAX 4096
#define YMAX 4096

extern "C" {
	#include "graphics.h"
	#include "clip.h"
}

class env {
public:
	mapnik::vector::tile tile;
	mapnik::vector::tile_layer *layer;
	mapnik::vector::tile_feature *feature;
};

double *graphics_init() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	env *e = new env;

	e->layer = e->tile.add_layers();
	e->layer->set_name("layer");
	e->layer->set_version(1);
	e->layer->set_extent(4096);

	e->feature = e->layer->add_features();
	e->feature->set_type(mapnik::vector::tile::LineString);

	return (double *) e;
}

void out(double *src, double *cx, double *cy, int width, int height, int transparency, double gamma, int invert, int color, int color2, int saturate, int mask) {
	env *e = (env *) src;

	std::string s;
	e->tile.SerializeToString(&s);

	std::cout << s;
}

int drawClip(double x0, double y0, double x1, double y1, double *image, double *cx, double *cy, double bright, double hue, int antialias, double thick) {
	int accept = clip(&x0, &y0, &x1, &y1, 0, 0, XMAX / 16.0, YMAX / 16.0);

	if (accept) {
		int xx0 = x0 * 16;
		int yy0 = y0 * 16;
		int xx1 = x1 * 16;
		int yy1 = y1 * 16;

		// Guarding against rounding error

		if (xx0 < 0) {
			xx0 = 0;
		}
		if (xx0 > 4095) {
			xx0 = 4095;
		}
		if (yy0 < 0) {
			yy0 = 0;
		}
		if (yy0 > 4095) {
			yy0 = 4095;
		}

		if (xx1 < 0) {
			xx1 = 0;
		}
		if (xx1 > 4095) {
			xx1 = 4095;
		}
		if (yy1 < 0) {
			yy1 = 0;
		}
		if (yy1 > 4095) {
			yy1 = 4095;
		}
	}

	return 0;
}

void drawPixel(double x, double y, double *image, double *cx, double *cy, double bright, double hue) {

}

void drawBrush(double x, double y, double *image, double *cx, double *cy, double bright, double brush, double hue) {

}