#include <grrlib.h>

#include "../block.h"
#include "../render.h"

#include "cloth_cyan.h"

blockTexture *tex_cloth_cyan;

static void render(int xPos, int yPos, int zPos, unsigned char pass) {
	if (pass == 1) return;
	drawBlock(xPos, yPos, zPos, tex_cloth_cyan);
}

void cloth_cyan_init() {
	blockEntry entry;
	entry.renderBlock = render;
	registerBlock(27, entry);
	tex_cloth_cyan = getTexture(6, 4);
}
