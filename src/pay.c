#include "pebble.h"
#include "pay.h"

static struct AmountUi {
  Window *window;
  TextLayer *name_text;
  TextLayer *amount_text;
  int index;
} ui;

static void window_load(Window *window) {
	    APP_LOG(APP_LOG_LEVEL_DEBUG, "Text: %s", "test");

  Layer *window_layer = window_get_root_layer(ui.window);
  GRect bounds = layer_get_bounds(window_layer);

  ui.name_text = text_layer_create((GRect) {
        .origin = { 0, 0 },
        .size = { bounds.size.w, 64 }
      });

  static char buf[32];
  snprintf(buf, 32, "%d", ui.index);
  text_layer_set_text(ui.name_text, buf);
  text_layer_set_text_alignment(ui.name_text, GTextAlignmentCenter);
  text_layer_set_font(ui.name_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(ui.name_text));
}

static void window_unload(Window *window) {
  text_layer_destroy(ui.name_text);
}

void pay_amount(int index) {

  ui.index = index;

  const bool animated = true;

  window_stack_push(ui.window, animated);

}


void pay_init(void) {
  ui.window = window_create();
  window_set_window_handlers(ui.window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

}

void pay_deinit(void) {
  window_destroy(ui.window);
}
