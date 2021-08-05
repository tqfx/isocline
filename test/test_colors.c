/* ----------------------------------------------------------------------------
  Copyright (c) 2021, Daan Leijen
  This is free software; you can redistribute it and/or modify it
  under the terms of the MIT License. A copy of the license can be
  found in the "LICENSE" file at the root of this distribution.

  Example that shows the color palette of the terminal
-----------------------------------------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isocline.h"


typedef enum color_order_e {
  RGB,
  BGR,
  GRB
} color_order_t;

static void write_palette( int order) {
  ic_term_write("\n  // ");
  ic_term_write(order == RGB ? "17x9x9" : (order == BGR ? "9x9x17" : "9x17x9"));
  ic_term_write("colors");
  for (int x = 0; x <= 256; x += 16) {
    ic_term_reset();
    ic_term_write("\n  ");
    for (int y = 0; y <= 256; y += 32) {
      for (int z = 0; z <= 256; z += 32) {
        ic_color_t c = (order == RGB ? ic_rgbx(x,y,z) : (order == BGR ? ic_rgbx(z,y,x) : ic_rgbx(y,x,z)));
        ic_term_color( c );
        ic_term_write("@");
      }
      ic_term_write(" ");
    }
  }
  ic_term_reset();
  ic_term_write("\n\n");
}

static void show_ansi_color( ic_color_t color, const char* name ) {
  printf("\x1B[%dm%16s\x1B[0m | \x1B[1;%dmbold\x1B[0m | \x1B[%dmbright\x1B[0m\n", color, name, color, color+60);    
}

// main example
int main() 
{
  // how many bits has our palette? (24 bits is good :-)
  printf("terminal color bits: %d\n", ic_term_get_color_bits());

  // Write out a palette
  ic_term_writeln("colors rgb:"); 
  write_palette(RGB);
  write_palette(BGR);
  write_palette(GRB);

  ic_term_writeln("\n\nansi red:");
  ic_term_color(IC_ANSI_MAROON); ic_term_write("ansi8-red ");
  ic_term_color(IC_ANSI_RED); ic_term_write("ansi16-bright-red ");
  ic_term_color(IC_RGB(0xD70000)); ic_term_write("ansi256-red160 ");
  ic_term_color(IC_RGB(0xfa1754)); ic_term_write("rgb-cherry");
  ic_term_reset(); ic_term_writeln("");

  // Shades
  ic_term_writeln("\nshades:");
  for (int i = 0; i <= 64; i++) {
    ic_term_color(ic_rgbx((i==64 ? 255 : i*4), 0, 0)); ic_term_write((i%8==0 ? "#" : "@"));
  }
  ic_term_writeln("");  
  for (int i = 0; i <= 64; i++) {
    ic_term_color(ic_rgbx(0, (i==64 ? 255 : i*4), 0)); ic_term_write((i%8==0 ? "#" : "@"));
  }
  ic_term_writeln("");  
  for (int i = 0; i <= 64; i++) {
    ic_term_color(ic_rgbx(0, 0, (i==64 ? 255 : i*4))); ic_term_write((i%8==0 ? "#" : "@"));
  }
  ic_term_writeln("");  
  for (int i = 0; i <= 64; i++) {
    int g = (i==64 ? 255 : i*4);
    ic_term_color(ic_rgbx(g, g, g)); ic_term_write((i%8==0 ? "#" : "@"));
  }
  ic_term_writeln("");
  ic_term_reset();
  
  // direct ANSI escapes
  ic_term_write("\n\ndirect ansi escape sequence colors:\n");
  show_ansi_color(IC_ANSI_BLACK,"black");
  show_ansi_color(IC_ANSI_MAROON,"maroon");
  show_ansi_color(IC_ANSI_GREEN,"green");
  show_ansi_color(IC_ANSI_ORANGE,"orange/brown");
  show_ansi_color(IC_ANSI_NAVY,"navy");
  show_ansi_color(IC_ANSI_PURPLE,"purple");
  show_ansi_color(IC_ANSI_TEAL,"teal");
  show_ansi_color(IC_ANSI_LIGHTGRAY,"lighgray/white");
  show_ansi_color(IC_ANSI_DEFAULT,"default");
  
  ic_term_reset();
  ic_term_writeln("");
  return 0;
}