#pragma once

#include "menu.h"
#include <OneButton.h>

static void selectButtonPressed(void *menu);

static void upButtonPressed(void *menu);

static void downButtonPressed(void *menu);

OneButton upBtn(5);
OneButton downBtn(4); 
OneButton leftBtn(1);
OneButton rightBtn(8);


void clear_btns();
void init_btns(Menu *menu);