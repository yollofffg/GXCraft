#include <grrlib.h>

#include "../block.h"
#include "../render.h"

#include "cloth_blue.h"

blockTexture *tex_cloth_blue;

static void render(int xPos, int yPos, int zPos, unsigned char pass) {
	if (pass == 1) return;
	drawBlock(xPos, yPos, zPos, tex_cloth_blue);
}

void cloth_blue_init() {
	blockEntry entry;
	entry.renderBlock = render;
	registerBlock(28, entry);
	tex_cloth_blue = getTexture(7, 4);
}
