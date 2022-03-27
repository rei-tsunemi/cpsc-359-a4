/* GIMP RGB C-Source image dump (right.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 2 + 1];
} gimp_image = {
  32, 32, 2,
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\000@\000@\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\000@\000@\040\300\040\300\040\300\303\030\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\000@\040\200\040\300\212\372\212\372\212"
  "\372\212\372\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\000@\040\200\040\300"
  "\212\372\212\372\212\372\212\372\377\377\303\030\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\000@\000"
  "@\040\200\040\300\040\300\212\372\040\300\040\300\377\377\377\377\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\000@\040\200\040\200\040\300\040\300\040\300\040\300\040\200\303\030\303\030"
  "\303\030\303\030\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\000@\040\200\040\200\040\200\040\300\040\300\040\200\303\030"
  "\303\030\040\300\212\372\212\372\212\372\212\372\040\300\303\030\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\040\200\040\200\040\300"
  "\040\300\040\200\040\200\040\300\040\300\040\300\040\200\303\030\303\030\303\030\303"
  "\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\040"
  "\200\040\200\303\030\040\200\040\200\040\200\303\030\303\030\303\030\303\030\350\352"
  "\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030\040\200\303\030\325\376\303\030BaBa\350\352\350\352\235"
  "\316\067\002\350\352\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\303\030\325\376\350\352\354\374B"
  "aBaBa\350\352\377\377\303\030\354\374\303\030\303\030\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\354\374\350"
  "\352\354\374BaBa\350\352\350\352\354\374\354\374\325\376\325\376\325\376"
  "\325\376\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030\354\374\350\352\350\352\350\352\303\030\303\030\354\374"
  "\354\374\354\374\354\374\354\374\354\374\303\030\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\350\352\350\352"
  "\350\352\303\030\303\030\303\030\303\030\350\352\350\352\350\352\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\303\030Ba\303\030\350\352\350\352\350\352\303\030\303\030\303\030\303\030\303"
  "\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\303\030\303\030\303\030\303\030\350\352\350"
  "\352\354\374\354\374\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\262\021\262\021\000h\000h\303\030\303\030\303\030\303\030\303\030\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\303\030\262\021\000h\002\300\002\300\010\352\303\030\303"
  "\030\000h\037\306\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\303\030\262\021\070\063\000h\002\300\010\352\010\352"
  "\010\352\010\352\303\030\303\030\303\030\303\030\303\030\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\303\030\303\030\262\021\070\063\303\030"
  "\000h\002\300\002\300\010\352\010\352\010\352\002\300\377\377\377\377\377\377\303\030"
  "\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061.c\303\030\070\063"
  "\070\063\303\030\303\030\000h\002\300\002\300\002\300\377\377\377\377\377\377\377\377"
  "\037\306\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061.c\303"
  "\030\262\021\070\063\274l\274l\303\030\303\030\303\030\303\030\037\306\377\377\377"
  "\377\037\306\037\306\303\030\303\030\303\030\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061"
  ".c.c\303\030\262\021\070\063\070\063\274l\274l\274l\274l\303\030\303\030\303\030\303"
  "\030\303\030@\302@\302\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\207\061.c"
  ".c\303\030\303\030\303\030\070\063\070\063\070\063\274l\274l\274l\262\021@\211@\302"
  "@\302@\302\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030\303\030\303\030\303\030\303\030\207\061\207\061"
  "\207\061\207\061\207\061\303\030\303\030\303\030\274l\274l\274l\262\021@\211@\302"
  "@\302@\211\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\303\030\303\030.c.c\025\245\303\030\303\030\303\030\303\030\303"
  "\030\303\030\207\061\207\061\207\061\303\030\303\030\303\030\262\021@\211\303\030\303"
  "\030\303\030\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\303\030\207\061a\376\340\377\340\377\025\245\303\030\000h\002\300"
  "\002\300\002\300\303\030\303\030\303\030\303\030\207\061\207\061\303\030\303\030\207"
  "\061.c.c\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030\207\061a\376.c\340\377.c\303\030\000h\000h\000h\002\300\002\300\002"
  "\300\010\352\010\352\303\030\303\030\303\030\303\030\207\061a\376\340\377.c\303"
  "\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030"
  "\207\061a\376a\376a\376\207\061\303\030\303\030\303\030\303\030\000h\000h\002\300\002\300"
  "\002\300\002\300\002\300\000h\303\030\207\061a\376a\376.c\303\030\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\207\061\207\061"
  "\207\061\303\030\303\030\357\204\357\204\357\204\303\030\303\030\303\030\303\030"
  "\303\030\303\030\303\030\303\030\303\030\207\061\207\061\207\061\303\030\303\030\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303"
  "\030\303\030\303\030\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030"
  "\303\030\303\030\357\204\357\204\357\204\357\204",
};
