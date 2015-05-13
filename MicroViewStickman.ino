/**
 * MicroView Stickman
 * This draws a stickman on the MicroView
 *
 * Licence: MIT
 * Creation: Original May 13, 2015
 * Copyright 2015 Ethan Smith
 */

#include <MicroView.h>
#include "Geometry.h"

int SCREEN_WIDTH = uView.getLCDWidth();
int SCREEN_HEIGHT = uView.getLCDHeight();

int CENTER_X = SCREEN_WIDTH/2;
int CENTER_Y = SCREEN_HEIGHT/2;

int HeadSize = 12;
int BodyHeight = 14;
int LegHeight = 22;
int LegSplit = 10;
int ArmLength = 7;
int ForearmLength = 8;
int NeckHeight = 4;
int TotalHeight = LegHeight+BodyHeight+HeadSize;

void setup() {
   uView.begin();
   uView.clear(ALL);
   uView.display();
}

void loop() {
   uView.clear(PAGE);

   Point origin = { .x = CENTER_X, .y = CENTER_Y };

   drawBody(origin);
   drawHead(origin);
   drawLeg(origin, LimbLeft);
   drawLeg(origin, LimbRight);
   drawArm(origin, LimbLeft, 50, 30);
   drawArm(origin, LimbRight, 7, -60);

   uView.display();
}

void drawBody(Point origin) {
   uView.line(origin.x, origin.y, origin.x, origin.y+BodyHeight);
}

void drawHead(Point origin) {
   uView.circle(origin.x, origin.y-HeadSize/2, HeadSize/2);
}

void drawLeg(Point origin, int direction) {
   origin.y += BodyHeight; // Shift for body
   uView.line(origin.x, origin.y, origin.x+LegSplit*direction, origin.y+LegHeight);
}

void drawArm(Point origin, int direction, int rotationA, int rotationB) {
   origin.y += NeckHeight; // Shift for neck

   int dx = cos(rotationA * (PI / 180)) * ArmLength * direction;
   int dy = sin(rotationA * (PI / 180)) * ArmLength;

   int x = origin.x + dx;
   int y = origin.y + dy;

   uView.line(origin.x, origin.y, x, y);

   int foreDX = cos((rotationA + rotationB) * (PI / 180)) * ForearmLength * direction;
   int foreDY = sin((rotationA + rotationB) * (PI / 180)) * ForearmLength;

   uView.line(x, y, x+foreDX, y+foreDY);
}
