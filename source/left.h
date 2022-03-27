/* GIMP RGB C-Source image dump (left.c) */

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
  "\357\204\357\204\303\030\000@\000@\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\303\030\040\300\040\300\040\300\000@\000@\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\212\372\212\372"
  "\212\372\212\372\040\300\040\200\000@\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\377\377\212\372\212\372\212\372\212\372\040\300\040\200\000@"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\303\030\377\377\377\377\040\300\040"
  "\300\212\372\040\300\040\300\040\200\000@\000@\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\303\030\303\030"
  "\303\030\303\030\040\200\040\300\040\300\040\300\040\300\040\200\040\200\000@\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\040\300\212"
  "\372\212\372\212\372\212\372\040\300\303\030\303\030\040\200\040\300\040\300\040"
  "\200\040\200\040\200\000@\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030\303\030\303\030\303\030\040\200\040\300\040\300\040\300\040\200"
  "\040\200\040\300\040\300\040\200\040\200\303\030\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\303\030\350\352\303\030\303"
  "\030\303\030\303\030\040\200\040\200\040\200\303\030\040\200\040\200\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\303\030\350\352\067\002\235\316\350\352\350\352BaBa\303\030\325\376\303\030\040"
  "\200\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\303\030\303\030\303\030\354\374\303\030\377\377\350\352BaBaBa\354\374\350\352"
  "\325\376\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\303\030\325\376\325\376\325\376\325\376\354\374\354\374\350\352\350\352"
  "BaBa\354\374\350\352\354\374\303\030\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030\354\374\354\374\354\374\354\374\354\374\354"
  "\374\303\030\303\030\350\352\350\352\350\352\354\374\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\350"
  "\352\350\352\350\352\303\030\303\030\303\030\303\030\350\352\350\352\350\352"
  "\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\303\030\303\030\303\030\303\030\303\030\303\030\350"
  "\352\350\352\350\352\303\030Ba\303\030\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303"
  "\030\354\374\354\374\350\352\350\352\303\030\303\030\303\030\303\030\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\303\030\303\030\303\030\303\030\303\030\000h\000h\262\021\262\021\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\303\030\037\306\000h\303\030\303\030\010\352\002\300\002\300\000h\262"
  "\021\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\303\030\303\030\303\030\303\030\303\030\010\352\010\352\010\352\010"
  "\352\002\300\000h\070\063\262\021\303\030\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\303\030\303\030\377\377\377\377\377\377\002\300\010\352\010\352"
  "\010\352\002\300\002\300\000h\303\030\070\063\262\021\303\030\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030\303\030\037\306\377\377\377\377\377\377\377"
  "\377\002\300\002\300\002\300\000h\303\030\303\030\070\063\070\063\303\030.c\207\061\303\030"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\303\030\303\030\303\030\037\306\037\306\377\377\377\377"
  "\037\306\303\030\303\030\303\030\303\030\274l\274l\070\063\262\021\303\030.c\207\061"
  "\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\357\204\303\030@\302@\302\303\030\303\030\303\030\303\030"
  "\303\030\274l\274l\274l\274l\070\063\070\063\262\021\303\030.c.c\207\061\303\030\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\357\204\303\030@\302@\302@\302@\211\262\021\274l\274l\274l\070"
  "\063\070\063\070\063\303\030\303\030\303\030.c.c\207\061\303\030\357\204\357\204\357"
  "\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\357\204\303\030@\211@\302@\302@\211\262\021\274l\274l\274l\303\030\303"
  "\030\303\030\207\061\207\061\207\061\207\061\207\061\303\030\303\030\303\030\303\030"
  "\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\303\030\303\030\303\030\303\030\303\030@\211\262\021\303\030\303\030\303\030"
  "\207\061\207\061\207\061\303\030\303\030\303\030\303\030\303\030\303\030\025\245.c"
  ".c\303\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\303\030\303\030.c.c\207\061\303\030\303\030\207\061\207\061\303\030\303"
  "\030\303\030\303\030\002\300\002\300\002\300\000h\303\030\025\245\340\377\340\377a\376"
  "\207\061\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357"
  "\204\303\030.c\340\377a\376\207\061\303\030\303\030\303\030\303\030\010\352\010\352"
  "\002\300\002\300\002\300\000h\000h\000h\303\030.c\340\377.ca\376\207\061\303\030\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030.ca\376a\376"
  "\207\061\303\030\000h\002\300\002\300\002\300\002\300\002\300\000h\000h\303\030\303\030\303\030"
  "\303\030\207\061a\376a\376a\376\207\061\303\030\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\303\030\303\030\207\061\207\061\207\061\303\030"
  "\303\030\303\030\303\030\303\030\303\030\303\030\303\030\303\030\357\204\357\204"
  "\357\204\303\030\303\030\207\061\207\061\207\061\303\030\303\030\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\357\204\357\204\303\030\303\030\303"
  "\030\303\030\357\204\357\204\357\204\357\204\357\204\357\204\357\204\357\204"
  "\357\204\357\204\357\204\357\204\357\204\303\030\303\030\303\030\303\030\303"
  "\030\357\204\357\204\357\204\357\204\357\204\357\204",
};
