/* GIMP RGB C-Source image dump (spike.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 2 + 1];
} gimp_spike = {
  32, 32, 2,
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\212R\212R\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000\000\000\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\000\000Y\316Y\316\000\000\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\212R\212R\337\377\337\377\212R\212R\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000Y\316\337\377\337"
  "\377Y\316\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\000\000\000\000\000\000\000\000\212R\212R\222\224\337"
  "\377\337\377\222\224\212R\212R\000\000\000\000\000\000\000\000\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\000\000Y\316Y\316\212R\212R\000\310\000\310\222\224"
  "\222\224\000\310\000\310\212R\212RY\316Y\316\000\000\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\000\000Y\316\337\377Y\316Y\316\212R\040\361\040\361"
  "\040\361\040\361\212RY\316Y\316\337\377Y\316\000\000\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\000\000\212RY\316\337\377\337\377Y\316\222\224\040"
  "\361\040\361\222\224Y\316\337\377\337\377Y\316\212R\000\000\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\000\000\212RY\316\337\377\337\377\337\377"
  "\222\224\040\361\040\361\222\224\337\377\337\377\337\377Y\316\212R\000\000\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\212R\000\000\212R\000\310\212RY\316\337\377"
  "\222\224\000\310\040\361\040\361\000\310\222\224\337\377Y\316\212R\000\310\212R\000"
  "\000\212R\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\000\000\212RY\316\222\224\000\310\040\361\040\361\222\224\000"
  "\310\040\361\040\361\040\361\040\361\000\310\222\224\040\361\040\361\000\310\222\224"
  "Y\316\212R\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\212R\000\000Y\316\337\377\337\377\337\377\222\224\040\361\040\361\040\361\040"
  "\361\040\361\040\361\040\361\040\361\040\361\040\361\040\361\040\361\222\224\337"
  "\377\337\377\337\377Y\316\000\000\212R\337\236\337\236\337\236\337\236\337\236"
  "\337\236\212R\000\000Y\316\337\377\337\377\337\377\222\224\040\361\040\361\040\361"
  "\040\361\040\361\040\361\040\361\040\361\040\361\040\361\040\361\040\361\222\224\337"
  "\377\337\377\337\377Y\316\000\000\212R\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\000\000\212RY\316\222\224\000\310\040\361\040\361\222\224"
  "\000\310\040\361\040\361\040\361\040\361\000\310\222\224\040\361\040\361\000\310\222"
  "\224Y\316\212R\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\212R\000\000\212R\000\310\212RY\316\337\377\222"
  "\224\000\310\040\361\040\361\000\310\222\224\337\377Y\316\212R\000\310\212R\000\000\212"
  "R\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\000\000\212RY\316\337\377\337\377\337"
  "\377\222\224\040\361\040\361\222\224\337\377\337\377\337\377Y\316\212R\000\000"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000\212RY\316\337"
  "\377\337\377Y\316\222\224\040\361\040\361\222\224Y\316\337\377\337\377Y\316"
  "\212R\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000Y\316"
  "\337\377Y\316Y\316\212R\040\361\040\361\040\361\040\361\212RY\316Y\316\337\377"
  "Y\316\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000Y\316"
  "Y\316\212R\212R\000\310\000\310\222\224\222\224\000\310\000\310\212R\212RY\316Y\316"
  "\000\000\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337"
  "\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\000\000\000\000\000\000"
  "\000\000\212R\212R\222\224\337\377\337\377\222\224\212R\212R\000\000\000\000\000\000\000\000"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\000\000Y\316\337\377\337\377Y\316\000\000\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\212R\212R\337\377\337\377"
  "\212R\212R\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\000\000Y\316Y\316\000\000\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\000\000\000\000\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\212R\212R\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236\337\236"
  "\337\236\337\236\337\236\337\236",
};

