#include "pebble.h"
#include "pay.h"
#include "friends.h"

static void init(void) {
  friends_init();
  pay_init();
}

static void deinit(void) {
  friends_deinit();
  pay_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();

  return 0;
}
