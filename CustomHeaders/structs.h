#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct TEVcolor
{
    char r;
    char g;
    char b;
    char a;
} TEVcolor;

typedef struct TEV
{
    char color_op;
    char alpha_op;
    char color_bias;
    char alpha_bias;
    char color_scale;
    char alpha_scale;
    char color_clamp;
    char alpha_clamp;
    char color_a_in;
    char color_b_in;
    char color_c_in;
    char color_d_in;
    char alpha_a_in;
    char alpha_b_in;
    char alpha_c_in;
    char alpha_d_in;
    TEVcolor constant;
    TEVcolor tev0;
	TEVcolor tev1;
	int active_flags;
} TEV;

typedef struct LiveLOBJ
{
	HSD_Obj parent;	   //0x00
	struct LOBJ *next; //0x08
	u16 flags;		   //0x0C
	u16 priority;	   //0x0E
	GXColor color;	   //0x10
	GXColor hw_color;  //0x14
	Vec3 position;	   //0x1C
	Vec3 interest;	   //0x28
	int x34;
	int x38;
	int x3c;
	int x40;
	int x44;
	int x48;
	int x4c;
	int x50;
	u32 id; //GXLightID
} LiveLOBJ;

#endif