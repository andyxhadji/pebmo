#include "pebble.h"
#include "pay.h"
#include "friends.h"
#include "complete.h"

static void init(void) {
  friends_init();
  pay_init();
  complete_init();
}

static void deinit(void) {
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
