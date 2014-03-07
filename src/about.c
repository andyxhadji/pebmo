#include "pebble.h"
#include "about.h"
#include "pay.h"

static Window *window;
TextLayer *text_layer;

static void window_load(Window *window) {
  // We'll have to load the icon before we can use it
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) {
        .origin = { 0, 0 },
        .size = { bounds.size.w, 128 }
      });

  text_layer_set_text(text_layer, "Thanks for using Pebmo! Send feedback to andy@adicu.com! If you enjoyed using Pebmo, consider donating! (Press the middle button!)");
  text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
  text_layer_set_overflow_mode(text_layer, GTextOverflowModeFill);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

}

void window_unload2(Window *window) {
  text_layer_destroy(text_layer);

}

static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  pay_amount(1000);
}

static void click_config_provider(void *context) {

  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);

}

void about_init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload2,
});

/*
app_message_register_inbox_received(in_received_handler);
app_message_register_inbox_dropped(in_dropped_handler);
app_message_register_outbox_sent(out_sent_handler);
app_message_register_outbox_failed(out_failed_handler);
*/
}

void about_deinit(void) {
  window_destroy(window);
}

void display_about(int index){
   window_stack_push(window, true);

   const uint32_t inbound_size = 9000000;
   const uint32_t outbound_size = 64;
   app_message_open(inbound_size, outbound_size);
}
