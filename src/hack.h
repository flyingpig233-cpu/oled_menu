#pragma once

#include "menu.h"
#include <BleKeyboard.h>

char *current_key;
BleKeyboard bleKeyboard("智能翻页笔");

void hack_handle(Menu *menu);