#include "button.h"
#include "exit.h"

static void selectButtonPressed(void *menu)
{
  ((Menu *)menu)->select();
}

static void upButtonPressed(void *menu)
{
  ((Menu *)menu)->prev_item();
}

static void downButtonPressed(void *menu)
{
  ((Menu *)menu)->next_item();
}

void clear_btns()
{
  upBtn.reset();
  downBtn.reset();
  leftBtn.reset();
  rightBtn.reset();
  upBtn.attachClick(nullptr, nullptr);
  downBtn.attachClick(nullptr, nullptr);
  leftBtn.attachClick(nullptr, nullptr);
  rightBtn.attachClick(nullptr, nullptr);
  upBtn.attachDoubleClick(nullptr, nullptr);
  downBtn.attachDoubleClick(nullptr, nullptr);
  leftBtn.attachDoubleClick(nullptr, nullptr);
  rightBtn.attachDoubleClick(nullptr, nullptr);
  upBtn.attachLongPressStart(nullptr, nullptr);
  downBtn.attachLongPressStart(nullptr, nullptr);
  leftBtn.attachLongPressStart(nullptr, nullptr);
  rightBtn.attachLongPressStart(nullptr, nullptr);
  upBtn.attachDuringLongPress(nullptr, nullptr);
  downBtn.attachDuringLongPress(nullptr, nullptr);
  leftBtn.attachDuringLongPress(nullptr, nullptr);
  rightBtn.attachDuringLongPress(nullptr, nullptr);
  upBtn.attachLongPressStop(nullptr, nullptr);
  downBtn.attachLongPressStop(nullptr, nullptr);
  leftBtn.attachLongPressStop(nullptr, nullptr);
  rightBtn.attachLongPressStop(nullptr, nullptr);
  upBtn.attachClick(nullptr);
  downBtn.attachClick(nullptr);
  leftBtn.attachClick(nullptr);
  rightBtn.attachClick(nullptr);
  upBtn.attachDoubleClick(nullptr);
  downBtn.attachDoubleClick(nullptr);
  leftBtn.attachDoubleClick(nullptr);
  rightBtn.attachDoubleClick(nullptr);
  upBtn.attachLongPressStart(nullptr);
  downBtn.attachLongPressStart(nullptr);
  leftBtn.attachLongPressStart(nullptr);
  rightBtn.attachLongPressStart(nullptr);
  upBtn.attachDuringLongPress(nullptr);
  downBtn.attachDuringLongPress(nullptr);
  leftBtn.attachDuringLongPress(nullptr);
  rightBtn.attachDuringLongPress(nullptr);
  upBtn.attachLongPressStop(nullptr);
  downBtn.attachLongPressStop(nullptr);
  leftBtn.attachLongPressStop(nullptr);
  rightBtn.attachLongPressStop(nullptr);
}

void init_btns(Menu *menu)
{
  clear_btns();
  upBtn.attachClick(upButtonPressed, (void *)menu);
  downBtn.attachClick(downButtonPressed, (void *)menu);
  rightBtn.attachClick(selectButtonPressed, (void *)menu);
  leftBtn.attachClick(exit_handle);
  quit = false;
}