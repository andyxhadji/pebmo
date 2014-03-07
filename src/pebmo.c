#include "pebble.h"
#include "pay.h"
#include "friends.h"
#include "complete.h"
#include "choose.h"
#include "venmo.h"
#include "about.h"

static void init(void) {
  choose_init();
  venmo_init();
  about_init();
  friends_init();
  pay_init();
  complete_init();
}

static void deinit(void) {
  choose_deinit();
  venmo_deinit();
  about_deinit();
  friends_deinit();
  pay_deinit();
  complete_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();

  return 0;
}
