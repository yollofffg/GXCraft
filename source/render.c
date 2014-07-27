#include <grrlib.h>

#include "render.h"
#include "main.h"

GRRLIB_texImg *lastTex = NULL;

static bool testFace(unsigned char face) {
	return face == 0 || face == 6 || face == 8 || face == 37 || face == 38 || face == 39 || face == 40;
}

inline void drawBlock(int xPos, int yPos, int zPos, GRRLIB_texImg *tex) {

	int drawBack  = testFace(theWorld[yPos][xPos][zPos + 1]);
	int drawFront = testFace(theWorld[yPos][xPos][zPos - 1]);
	int drawRight = testFace(theWorld[yPos][xPos + 1][zPos]);
	int drawLeft  = testFace(theWorld[yPos][xPos - 1][zPos]);
	int drawTop   = testFace(theWorld[yPos + 1][xPos][zPos]);
	int drawBott  = testFace(theWorld[yPos - 1][xPos][zPos]);

	int size = 0;
	if (drawBack)  size += 4;
	if (drawFront) size += 4;
	if (drawRight) size += 4;
	if (drawLeft)  size += 4;
	if (drawTop)   size += 4;
	if (drawBott)  size += 4;
	
	if (size == 0) return;
	
	if (lastTex != tex)
		GRRLIB_SetTexture(tex, 0);
	lastTex = tex;

	GX_Begin(GX_QUADS, GX_VTXFMT1, size);

	if (drawBack) {
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,1);
	}

	if (drawFront) {
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,1);
	}

	if (drawRight) {
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,1);
	}

	if (drawLeft) {
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,1);
	}

	if (drawTop) {
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(0,1);
	}

	if (drawBott) {
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(0,1);
	}

	GX_End();
}

inline void drawBlockCrossed(int xPos, int yPos, int zPos, GRRLIB_texImg *tex) {

	if (lastTex != tex)
		GRRLIB_SetTexture(tex, 0);
	lastTex = tex;

	GX_Begin(GX_QUADS, GX_VTXFMT1, 8);

	GX_Position3s16(xPos, 1+yPos, zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(0,0);
	GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(1,0);
	GX_Position3s16( 1+xPos,yPos, 1+zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(1,1);
	GX_Position3s16(xPos,yPos,zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(0,1);

	GX_Position3s16(xPos, 1+yPos, 1+zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(0,0);
	GX_Position3s16( 1+xPos, 1+yPos,zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(1,0);
	GX_Position3s16( 1+xPos,yPos,zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(1,1);
	GX_Position3s16(xPos,yPos, 1+zPos);
	GX_Color1u16(0xFFFF);
	GX_TexCoord2u8(0,1);

	GX_End();
}
