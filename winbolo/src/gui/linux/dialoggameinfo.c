/*
 * $Id$
 *
 * Copyright (c) 1998-2008 John Morrison.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


/*********************************************************
*Name:          Dialog - Game Info
*Filename:      dialoggameinfo.c
*Author:        John Morrison
*Creation Date: 26/1/99
*Last Modified: 28/4/00
*Purpose:
*  Looks after the game info dialog box.
*********************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include "../lang.h"
#include "../../bolo/global.h"
#include "../../bolo/backend.h"
#include "../linresource.h"
#include "dialoggameinfo.h"

/* Text Labels */
GtkWidget *lblMapName;
GtkWidget *lblNumPlayers;
GtkWidget *lblGameType;
GtkWidget *lblHiddenMines;
GtkWidget *lblCompTanks;
GtkWidget *lblGameTimeLimit;

/* Game Timer */
int timerGameInfo;
BYTE dlgGameInfoNumPlayers;      /* Number of players in the game */
long dlgGameInfoTimeRemain;     /* Time remaining in the game */


/*********************************************************
*NAME:          dialogGameInfoUpdate
*AUTHOR:        John Morrison
*CREATION DATE: 26/1/99
*LAST MODIFIED: 26/1/99
*PURPOSE:
* Called each time the dialog is supposed to be updated.
*
*ARGUMENTS:
*  hWnd - The dialog window handle
*********************************************************/
gint dialogGameInfoUpdate(gpointer data) {
BYTE newPlayers; /* The number of newPlayers in the game */
char str[FILENAME_MAX];    /* Used to update things as required */

  newPlayers = screenGetNumPlayers();
  if (newPlayers != dlgGameInfoNumPlayers) {
    dlgGameInfoNumPlayers = newPlayers;
    sprintf(str, "%d", dlgGameInfoNumPlayers);
    gtk_label_set_text(GTK_LABEL(lblNumPlayers), str);
  }
  if (dlgGameInfoTimeRemain != UNLIMITED_GAME_TIME) {
    dlgGameInfoTimeRemain = screenGetGameTimeLeft();
    dlgGameInfoTimeRemain /= NUM_SECONDS_MINUTE;
    dlgGameInfoTimeRemain /= GAME_NUMGAMETICKS_SEC;
    dlgGameInfoTimeRemain++;
    sprintf(str, langGetText(STR_DLGGAMEINFO_TIMEREMAINING), dlgGameInfoTimeRemain );
    gtk_label_set_text(GTK_LABEL(lblGameTimeLimit), str);
  }
  return TRUE;
}

void windowGameInfoClose();

gint dialogGameInfoClose(GtkWidget *widget, gpointer gdata) {
  gtk_timeout_remove(timerGameInfo);
  windowGameInfoClose();
  return FALSE;
}

GtkWidget* dialogGameInfoCreate(void) {
  GtkWidget *dialogGameInfo;
  GtkWidget *vbox1;
  GtkWidget *hbox6;
  GtkWidget *label12;
  GtkWidget *hbox7;
  GtkWidget *label14;
  GtkWidget *hbox8;
  GtkWidget *label16;
  GtkWidget *hbox9;
  GtkWidget *label18;
  GtkWidget *hbox10;
  GtkWidget *label20;
  GtkWidget *hbox11;
  GtkWidget *label22;
  char mapName[FILENAME_MAX];  /* Map Name */
  int temp;                    /* Used to hold various values */
  bool bTemp;                  /* Used for holding misc bool variables */
  char *text;
  gameType *t;

  dialogGameInfo = gtk_dialog_new();
  g_object_set_data (dialogGameInfo, "dialogGameInfo", dialogGameInfo);
  gtk_widget_set_usize (dialogGameInfo, 300, 150);
  gtk_container_set_border_width (GTK_CONTAINER (dialogGameInfo), 15);
  gtk_window_set_title (GTK_WINDOW (dialogGameInfo), "LinBolo Game Information");
    gtk_window_set_policy(GTK_WINDOW(dialogGameInfo), FALSE, FALSE, FALSE);
  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);
  gtk_container_child_set (vbox1, dialogGameInfo, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogGameInfo), vbox1);

  hbox6 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox6);
  gtk_container_child_set (hbox6, dialogGameInfo, "hbox6");
  gtk_widget_show (hbox6);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox6, TRUE, TRUE, 0);

  label12 = gtk_label_new ("Map Name:");
  g_object_ref (label12);
  gtk_container_child_set (label12, dialogGameInfo, "label12");
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (hbox6), label12, FALSE, FALSE, 0);

  lblMapName = gtk_label_new ("");
  g_object_ref (lblMapName);

  gtk_container_child_set (lblMapName, dialogGameInfo, "lblMapName");
  gtk_widget_show (lblMapName);
  gtk_box_pack_end (GTK_BOX (hbox6), lblMapName, FALSE, FALSE, 0);

  hbox7 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox7);
  gtk_container_child_set (hbox7, dialogGameInfo, "hbox7");
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox7, TRUE, TRUE, 0);

  label14 = gtk_label_new ("Number of Players:");
  g_object_ref (label14);
  gtk_container_child_set (label14, dialogGameInfo, "label14");
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (hbox7), label14, FALSE, FALSE, 0);

  lblNumPlayers = gtk_label_new ("");
  g_object_ref (lblNumPlayers);
  gtk_container_child_set (lblNumPlayers, dialogGameInfo, "lblNumPlayers");
  gtk_widget_show (lblNumPlayers);
  gtk_box_pack_end (GTK_BOX (hbox7), lblNumPlayers, FALSE, FALSE, 0);

  hbox8 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox8);
  gtk_container_child_set (hbox8, dialogGameInfo, "hbox8");
  gtk_widget_show (hbox8);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox8, TRUE, TRUE, 0);

  label16 = gtk_label_new ("Game Type:");
  g_object_ref (label16);
  gtk_container_child_set (label16, dialogGameInfo, "label16");
  gtk_widget_show (label16);
  gtk_box_pack_start (GTK_BOX (hbox8), label16, FALSE, FALSE, 0);

  lblGameType = gtk_label_new ("");
  g_object_ref (lblGameType);
  gtk_container_child_set (lblGameType, dialogGameInfo, "lblGameType");
  gtk_widget_show (lblGameType);
  gtk_box_pack_end (GTK_BOX (hbox8), lblGameType, FALSE, FALSE, 0);

  hbox9 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox9);
  gtk_container_child_set (hbox9, dialogGameInfo, "hbox9");
  gtk_widget_show (hbox9);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox9, TRUE, TRUE, 0);

  label18 = gtk_label_new ("Hidden Mines:");
  g_object_ref (label18);
  gtk_container_child_set (label18, dialogGameInfo, "label18");
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox9), label18, FALSE, FALSE, 0);

  lblHiddenMines = gtk_label_new ("");
  g_object_ref (lblHiddenMines);
  gtk_container_child_set (lblHiddenMines, dialogGameInfo, "lblHiddenMines");
  gtk_widget_show (lblHiddenMines);
  gtk_box_pack_end (GTK_BOX (hbox9), lblHiddenMines, FALSE, FALSE, 0);

  hbox10 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox10);
  gtk_container_child_set (hbox10, dialogGameInfo, "hbox10");
  gtk_widget_show (hbox10);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox10, TRUE, TRUE, 0);

  label20 = gtk_label_new ("Computer Tanks Allowed:");
  g_object_ref (label20);
  gtk_container_child_set (label20, dialogGameInfo, "label20");
  gtk_widget_show (label20);
  gtk_box_pack_start (GTK_BOX (hbox10), label20, FALSE, FALSE, 0);

  lblCompTanks = gtk_label_new ("");
  g_object_ref (lblCompTanks);
  gtk_container_child_set (lblCompTanks, dialogGameInfo, "lblCompTanks");
  gtk_widget_show (lblCompTanks);
  gtk_box_pack_end (GTK_BOX (hbox10), lblCompTanks, FALSE, FALSE, 0);

  hbox11 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox11);
  gtk_container_child_set (hbox11, dialogGameInfo, "hbox11");
  gtk_widget_show (hbox11);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox11, TRUE, TRUE, 0);

  label22 = gtk_label_new ("Game Time Limit:");
  g_object_ref (label22);
  gtk_container_child_set (label22, dialogGameInfo, "label22");
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (hbox11), label22, FALSE, FALSE, 0);

  lblGameTimeLimit = gtk_label_new ("");
  g_object_ref (lblGameTimeLimit);
  gtk_container_child_set (lblGameTimeLimit, dialogGameInfo, "lblGameTimeLimit");
  gtk_widget_show (lblGameTimeLimit);
  gtk_box_pack_end (GTK_BOX (hbox11), lblGameTimeLimit, FALSE, FALSE, 0);

  /* Write the map name */
  mapName[0] = '\0';
  screenGetMapName(mapName);
  gtk_label_set_text(GTK_LABEL(lblMapName), mapName);

  /* Number of players */
  dlgGameInfoNumPlayers = screenGetNumPlayers();
  mapName[0] = '\0';
  sprintf(mapName, "%d", dlgGameInfoNumPlayers);
  gtk_label_set_text(GTK_LABEL(lblNumPlayers), mapName);

  /* Game type */
  t = screenGetGameType();
  switch (*t) {
  case gameOpen:
    gtk_label_set_text(GTK_LABEL(lblGameType), langGetText(STR_DLGGAMEINFO_OPEN));
    break;
  case gameTournament:
    gtk_label_set_text(GTK_LABEL(lblGameType), langGetText(STR_DLGGAMEINFO_TOURN));
    break;
  default:
    /* gameStrictTournament */
    gtk_label_set_text(GTK_LABEL(lblGameType), langGetText(STR_DLGGAMEINFO_STRICT));
   break;
  }

  /* Hidden Mines */
  bTemp = screenGetAllowHiddenMines();
  if (bTemp == TRUE) {
    gtk_label_set_text(GTK_LABEL(lblHiddenMines), langGetText(STR_YES));
  } else {
    gtk_label_set_text(GTK_LABEL(lblHiddenMines), langGetText(STR_NO));
  }

  /* Computer players */
  temp = screenGetAiType();
  switch (temp) {
  case aiNone:
    gtk_label_set_text(GTK_LABEL(lblCompTanks), langGetText(STR_NO));
    break;
  case aiYes:
    gtk_label_set_text(GTK_LABEL(lblCompTanks),langGetText(STR_YES));
    break;
  default:
    /* aiYesAdvantage */
    gtk_label_set_text(GTK_LABEL(lblCompTanks), langGetText(STR_DLGGAMEINFO_AIADV));
    break;
  }

  dlgGameInfoTimeRemain = screenGetGameTimeLeft();
  if (dlgGameInfoTimeRemain == UNLIMITED_GAME_TIME) {
    gtk_label_set_text(GTK_LABEL(lblGameTimeLimit),  langGetText(STR_NO));
  }

  dialogGameInfoUpdate(NULL);

  timerGameInfo = gtk_timeout_add (SECOND, dialogGameInfoUpdate, (gpointer) NULL);
   g_signal_connect(dialogGameInfo, "delete_event", G_CALLBACK(dialogGameInfoClose), NULL);
   return dialogGameInfo;
}
