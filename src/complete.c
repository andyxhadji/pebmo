#include "pebble.h"
#include "complete.h"

static Window *window;
TextLayer *text_layer;

static void window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) {
        .origin = { 0, 30 },
        .size = { bounds.size.w, 64 }
      });

  text_layer_set_text(text_layer, "Payment complete");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window){
	text_layer_destroy(text_layer);
}

void completedCharge(void){
	const bool animated = true;
	window_stack_push(window, animated);
}


void complete_init(void){
  window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });   
}

void complete_deinit(void){
	window_destroy(window);
}