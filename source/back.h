/* GIMP RGB C-Source image dump (back.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 2 + 1];
} gimp_image = {
  32, 32, 2,
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\000@\000@\000@\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\000@\000@\040\300\212\372\212"
  "\372\040\300\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\000@\040\300"
  "\212\372\212\372\212\372\212\372\212\372\212\372\040\300\303\030\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\000@\040\300\040\300\212\372\212\372\212\372\212\372\212\372\212"
  "\372\040\300\040\300\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\000@\040\300\040\300\040\300\212\372"
  "\212\372\212\372\212\372\040\300\040\300\040\300\303\030\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\000@\040\200\040"
  "\300\040\300\040\300\040\300\040\300\040\300\040\300\040\300\040\300\040\300\040\200"
  "\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\000@\040\200\040\300\040\300\040\200\040\200\040\200\040\200\040\200\040\200\040"
  "\300\040\300\040\200\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\000@\040\200\040\300\040\200\040\200\040\300\040\300\040"
  "\300\040\300\040\200\040\200\040\300\040\200\303\030\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\000@\040\200\040\200\040\300\040\300"
  "\212\372\212\372\212\372\212\372\040\300\040\300\040\200\040\200\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\354\374\303"
  "\030\040\200\040\200\040\300\040\300\040\300\040\300\040\300\040\300\040\200\040\200"
  "\303\030\354\374\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\303\030\354\374Ba\303\030\303\030\040\200\040\200\040\200\040\200\040\200\040"
  "\200\303\030\303\030Ba\354\374\303\030\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\303\030\354\374\350\352BaBa\303\030\303\030\303\030\303\030\303"
  "\030\303\030BaBa\350\352\354\374\303\030\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\303\030\350\352BaBaBaBaBaBaBaBaBaBa\350\352\303"
  "\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\350\352Ba@\211@\211a\302a\302@\211@\211Ba\350\352\303\030"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030@\211a\302@\211BaBa@\211a\302@\211\303\030"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\303\030\303\030\303\030\350\352\350\352\350"
  "\352\350\352\303\030\303\030\303\030\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\262"
  "\021\303\030\303\030\303\030\303\030\303\030\303\030\262\021\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\002\300\262\021\000h\000h\000h\000h\000h\000h\262\021\002\300\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\303\030\002\300\010\352\070\063\070\063\002\300\002\300\002\300\002\300\070\063\070\063\010\352"
  "\002\300\000@\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\002\300\010\352\070\063\274l\274l\274l\274l\274l\274l\070\063\010"
  "\352\002\300\000@\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030\000h\000h\303\030\303\030\303\030\303\030\303\030\303\030\303\030"
  "\303\030\000h\000h\000@\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030\303\030.c\025\245\025\245\377\377\377\377\025"
  "\245\025\245.c\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\303\030.c.c\207\061\207\061\207\061"
  "\207\061\207\061\207\061.c.c\303\030\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\303\030\303\030\303\030\303\030\303\030\207\061"
  "\207\061\207\061\207\061\207\061\207\061\303\030\303\030\303\030\303\030\303\030\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061\303\030\025\245"
  "\377\377\377\377\303\030\207\061\303\030\303\030\207\061\303\030\377\377\377\377"
  "\025\245\303\030\207\061\303\030\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\303\030"
  "\303\030\303\030\025\245\303\030\377\377\377\377\303\030\025\245\025\245\303\030"
  "\377\377\377\377\303\030\025\245\303\030\303\030\303\030\303\030\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\207"
  "\061\207\061\207\061\207\061\303\030\303\030\025\245\025\245\303\030\303\030\303\030"
  "\303\030\303\030\303\030\025\245\025\245\303\030\303\030\207\061\207\061\207\061\207"
  "\061\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\303\030.c\025\245\025\245.c\303\030\000h\002\300\002\300\010\352\010\352\010\352\010\352"
  "\010\352\010\352\002\300\002\300\000h\303\030.c\025\245\025\245.c\303\030\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061\207\061"
  "\207\061\207\061\303\030\303\030\303\030\000h\000h\002\300\002\300\002\300\002\300\000h\000h\303"
  "\030\303\030\303\030\207\061\207\061\207\061\207\061\303\030\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061\207\061\207\061"
  "\207\061\303\030\357\204\357\204\303\030\303\030\303\030\303\030\303\030\303\030"
  "\303\030\303\030\357\204\357\204\303\030\207\061\207\061\207\061\207\061\303\030"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\303"
  "\030\207\061\207\061\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\207\061"
  "\207\061\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\303\030\303\030\303\030\303\030\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\303\030\303\030\303\030\303\030\357\204\357\204\357\204\357"
  "\204\357\204",
};

