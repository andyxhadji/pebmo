#include "friends.h"
#include "pebble.h"
#include "pay.h"

#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 200
#define NUM_SECOND_MENU_ITEMS 0

static Window *window;

// This is a simple menu layer
static SimpleMenuLayer *simple_menu_layer;

// A simple menu layer can have multiple sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

// Each section is composed of a number of menu items
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];

static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];

// Menu items can optionally have icons
static GBitmap *menu_icon_image;

static bool special_flag = false;

static int hit_count = 0;

static int count = 0;

static int num_a_items = 0;
 
Tuple **names;

Tuple *text_tuple;

static int ping_count = 0;

static int name_count = 0;

static void out_sent_handler(DictionaryIterator *sent, void *context) {
   // outgoing message was delivered
 }


static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
   // outgoing message failed
 }

static void in_received_handler(DictionaryIterator *iter, void *context) {

            Tuple *tuple = dict_find(iter, 0);

           uint8_t *length = tuple->value->data;

                              //APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", length);
           uint8_t increment = 1;
            for(uint8_t t = 0; t < *length; t = t + increment){
                count++;
              }  
               APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", count);

             names = malloc(sizeof(Tuple *)*(count));

          int x; 
          for (x = 0; x < count; x++){

            tuple = dict_find(iter, (x+1));

      //      if (x == 0){
              //names = malloc(sizeof(Tuple *)*count);
       //     } else {
              //names[x] = malloc(sizeof(char)*(*tuple->value->cstring).length);
              names[x] = tuple;
             // APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", names[x]->value->cstring);
              //APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", "test");

            }
          

          post_data();
        


}


static void in_dropped_handler(AppMessageResult reason, void *context) {
   // incoming message dropped
 }
// You can capture when the user selects a menu icon with a menu item select callback
static void menu_select_callback(int index, void *ctx) {

  pay_amount(index);
}

// You can specify special callbacks to differentiate functionality of a menu item
static void special_select_callback(int index, void *ctx) {
  // Of course, you can do more complicated things in a menu item select callback
  // Here, we have a simple toggle
  special_flag = !special_flag;

  SimpleMenuItem *menu_item = &second_menu_items[index];

  if (special_flag) {
    menu_item->subtitle = "Okay, it's not so special.";
  } else {
    menu_item->subtitle = "Well, maybe a little.";
  }

  if (++hit_count > 5) {
    menu_item->title = "Very Special Item";
  }

  // Mark the layer to be updated
  layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
}

void post_data (void){
    menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  // Although we already defined NUM_FIRST_MENU_ITEMS, you can define
  // an int as such to easily change the order of menu items later
//  int num_a_items = 0;
  for (int x = 0; x < count; x++) {
      first_menu_items[x] = (SimpleMenuItem){
    // You should give each menu item a title and callback
    .title = names[x]->value->cstring,
    .callback = menu_select_callback,
    };
  }
  /*
    first_menu_items[num_a_items++] = (SimpleMenuItem){
    // You should give each menu item a title and callback
    .title = text_tuple->value->cstring,
    .callback = menu_select_callback,
    };
*/
  // Bind the menu items to the corresponding menu sections
  menu_sections[0] = (SimpleMenuSection){
    .title = "          Pay Someone!",
    .num_items = NUM_FIRST_MENU_ITEMS,
    .items = first_menu_items,
  };

  // Now we prepare to initialize the simple menu layer
  // We need the bounds to specify the simple menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Initialize the simple menu layer
  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);

  // Add it to the window for display
  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}
// This initializes the menu upon window load
static void window_load(Window *window) {
  // We'll have to load the icon before we can use it

}

// Deinitialize resources on window unload that were initialized on window load
void window_unload(Window *window) {
  simple_menu_layer_destroy(simple_menu_layer);

  // Cleanup the menu icon
  gbitmap_destroy(menu_icon_image);
  free(names);

}

 void friends_init(void) {


  window = window_create();


  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });   
    //window_stack_push(window, true /* Animated */);
    app_message_register_inbox_received(in_received_handler);
   app_message_register_inbox_dropped(in_dropped_handler);
   app_message_register_outbox_sent(out_sent_handler);
   app_message_register_outbox_failed(out_failed_handler);


   
 }

 void friends_deinit(void) {
    window_destroy(window);
 }
 
 void display_people(int index){
    window_stack_push(window, true);


   const uint32_t inbound_size = 22400;
   const uint32_t outbound_size = 64;
   app_message_open(inbound_size, outbound_size);

   // create message to phone 
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    //original
    Tuplet value = TupletInteger(100, 15);

    //Tuplet value3 = TupletInteger(101, 15);
    //if (index){
    //dict_write_tuplet(iter, &value3);

    //} else {
    dict_write_tuplet(iter, &value);
 // }
    
    app_message_outbox_send();

  
 }

