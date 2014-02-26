#include "pebble.h"
#include "choose.h"
#include "friends.h"

#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 4
#define NUM_SECOND_MENU_ITEMS 1
// This is a simple menu layer
static SimpleMenuLayer *simple_menu_layer;

// A simple menu layer can have multiple sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

// Each section is composed of a number of menu items
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];

static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];

// Menu items can optionally have icons
static GBitmap *menu_icon_image;

Window *window;

void groups (void){
    menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  // Although we already defined NUM_FIRST_MENU_ITEMS, you can define
  // an int as such to easily change the order of menu items later
  int num_a_items = 0;
 
  // This is an example of how you'd set a simple menu item
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    // You should give each menu item a title and callback
    .title = "Venmo Friends",
    .callback = menu_select_callback,
  };

  // The menu items appear in the order saved in the menu items array
 /* first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Check In Friends",
    // You can also give menu items a subtitle
    //.subtitle = "Here's a subtitle",
    .callback = menu_select_callback,
  };
  */

  // Bind the menu items to the corresponding menu sections
  menu_sections[0] = (SimpleMenuSection){
    .title = "         Choose group",
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

static void menu_select_callback(int index, void *ctx) {
  // Here we just change the subtitle to a literal string
  //first_menu_items[index].subtitle = "You've hit select here!";
  // Mark the layer to be updated
  //layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
  //payAmount(first_menu_items[index]);
  //simple_menu_layer_destroy(simple_menu_layer);
  display_people(index);

}

static void window_load(Window *window) {
  // We'll have to load the icon before we can use it
	groups();
}
static void window_unload(Window *window){
	simple_menu_layer_destroy(simple_menu_layer);
}
 void choose_init(void) {

  window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });   
    window_stack_push(window, true /* Animated */);

 }
 void choose_deinit(void){
 	window_destroy(window);
 }
