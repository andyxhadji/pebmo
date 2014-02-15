#include "pebble.h"
#include "pay.h"

static struct AmountUi {
  Window *window;
  TextLayer *name_text;
  TextLayer *amount_text;
  int amount;
  int index;
} ui;


static void window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(ui.window);
  GRect bounds = layer_get_bounds(window_layer);

  ui.amount_text = text_layer_create((GRect) {
        .origin = { 0, 30 },
        .size = { bounds.size.w, 64 }
      });
  static char buf[32];
  snprintf(buf, 32, "$ %d", ui.amount);
  text_layer_set_text(ui.amount_text, buf);
  text_layer_set_text_alignment(ui.amount_text, GTextAlignmentCenter);
  text_layer_set_font(ui.amount_text, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  layer_add_child(window_layer, text_layer_get_layer(ui.amount_text));
}

static void window_unload(Window *window) {
  text_layer_destroy(ui.name_text);
}

void pay_amount(int index) {
  ui.amount = 0;
  ui.index = index;

  const bool animated = true;

  window_stack_push(ui.window, animated);

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {

  ++ui.amount;

  static char buf[32];
  snprintf(buf, 32, "$ %u", ui.amount);
  text_layer_set_text(ui.amount_text, buf);
  layer_mark_dirty(text_layer_get_layer(ui.amount_text));

}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {

 if (ui.amount > 0){
  --ui.amount;
}

  static char buf[32];
  snprintf(buf, 32, "$ %u", ui.amount);
  text_layer_set_text(ui.amount_text, buf);
  layer_mark_dirty(text_layer_get_layer(ui.amount_text));

}


static void click_config_provider(void *context) {
  const uint16_t repeat_interval_ms = 100;
  window_set_click_context(BUTTON_ID_UP, context);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, repeat_interval_ms, up_click_handler);

  window_set_click_context(BUTTON_ID_DOWN, context);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, repeat_interval_ms, down_click_handler);

}

void pay_init(void) {
  ui.window = window_create();

  window_set_click_config_provider(ui.window, click_config_provider);

  window_set_window_handlers(ui.window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

}

void pay_deinit(void) {
  window_destroy(ui.window);
}
