﻿#include "Init_Static.h"

// Init order of vehicle
INIT_BASE(CVEHICLE);
INIT_OBJECT(CVEHICLE, CTRUCK);
INIT_OBJECT(CVEHICLE, CCAR);

// Init order of animal
INIT_BASE(CANIMAL);
INIT_OBJECT(CANIMAL, CDOG);
INIT_OBJECT(CANIMAL, CBIRD);
