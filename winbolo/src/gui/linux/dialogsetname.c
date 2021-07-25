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


/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include "../../bolo/backend.h"
#include "../linresource.h"
#include "../lang.h"
#include "gamefront.h"
#include "messagebox.h"

GtkWidget *idc_setnametxt;
bool setNameInGame = FALSE; /* Are we in a game or not */
GtkWidget *dialogSetNameUs;

gboolean dialogSetNameOK(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
  bool closeDialog;              /* Should the dialog be closed */
  bool changeOK;                 /* Is the name change ok */
  char oldName[PLAYER_NAME_LEN]; /* Old player name */
  char newName[PLAYER_NAME_LEN]; /* New player name */
  gchar *str;

  /* Set the name */
  oldName[0] = '\0';
  newName[0] = '\0';
  closeDialog = FALSE;
  changeOK = TRUE;

  screenGetPlayerName(oldName);
  str = gtk_entry_get_text(GTK_ENTRY(idc_setnametxt));
  strncpy(newName, str, sizeof(newName));
  newName[PLAYER_NAME_LAST] = '\0';

  utilStripName(newName);
  if (newName[0] == EMPTY_CHAR) {
    MessageBox("Sorry, you can not leave this blank", DIALOG_BOX_TITLE);
  } else if (newName[0] == '*') {
    MessageBox("Sorry, names can not begin with a '*'", DIALOG_BOX_TITLE);
  } else if (strcmp(oldName, newName) == 0) {
    /* Names are the same */
    closeDialog = TRUE;
  } else {
    if (setNameInGame == TRUE) {
      changeOK = screenSetPlayerName(newName);
      if (changeOK == FALSE) {
        if (strcmp(oldName, newName) != 0) {
          /* Someone else in the game must have our name already - Can't change */
          MessageBox(langGetText(NETERR_PLAYERNAMEINUSE), DIALOG_BOX_TITLE);
        }
      } else {
        closeDialog = TRUE;
      }
    } else {
      /* Tell game front about */
      closeDialog = TRUE;
      gameFrontSetPlayerName(newName);
    }
  }
 /* Close the dialog if necessary */
 if (closeDialog == TRUE) {
    gtk_grab_remove(dialogSetNameUs);
    gtk_widget_destroy(dialogSetNameUs);
    gtk_main_quit();
  }
  return FALSE;
}

gboolean dialogSetNameKey(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
  if (event->keyval == 65293) {
    dialogSetNameOK(dialogSetNameUs, NULL, NULL);
  }
  return FALSE;
}

gboolean dialogSetNameClose(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  gtk_grab_remove(dialogSetNameUs);
  gtk_widget_destroy(dialogSetNameUs);
  gtk_main_quit();
  return FALSE;
}


GtkWidget* dialogSetNameCreate(bool inGame) {
  GtkWidget *dialogSetName;
  GtkWidget *vbox1;
  GtkWidget *label1;
  GtkWidget *hbox1;
  GtkWidget *button1;
  char playerName[FILENAME_MAX]; /* Player Name */

  setNameInGame = inGame;

  dialogSetName = gtk_dialog_new();
  g_object_set_data (dialogSetName, "dialogSetName", dialogSetName);
  gtk_container_set_border_width (GTK_CONTAINER (dialogSetName), 10);
  gtk_window_set_title (GTK_WINDOW (dialogSetName), "Enter Player Name");
  gtk_window_set_position (GTK_WINDOW (dialogSetName), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (dialogSetName), TRUE);
  gtk_window_set_policy (GTK_WINDOW (dialogSetName), FALSE, FALSE, FALSE);

  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);
  gtk_container_child_set (vbox1, dialogSetName, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogSetName), vbox1);

  label1 = gtk_label_new ("Enter the new player name for your tank");
  g_object_ref (label1);
  gtk_container_child_set (label1, dialogSetName, "label1");
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

  hbox1 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox1);
  gtk_container_child_set (hbox1, dialogSetName, "hbox1");
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox1), 10);

  idc_setnametxt = gtk_entry_new ();
  g_object_ref (idc_setnametxt);
  gtk_container_child_set (idc_setnametxt, dialogSetName, "idc_setnametxt");
  gtk_widget_show (idc_setnametxt);
  gtk_box_pack_start (GTK_BOX (hbox1), idc_setnametxt, TRUE, TRUE, 0);

  button1 = gtk_button_new_with_label ("OK");
  g_object_ref (button1);
  gtk_container_child_set (button1, dialogSetName, "button1");
  gtk_widget_show (button1);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, TRUE, 0);

  g_signal_connect(dialogSetName, "delete_event", G_CALLBACK(dialogSetNameClose), NULL);
  g_signal_connect(button1, "clicked", G_CALLBACK(dialogSetNameOK), 0);
  g_signal_connect(idc_setnametxt, "key-press-event", G_CALLBACK(dialogSetNameKey), 0);

  /* Get the name */
  playerName[0] = '\0';
  if (setNameInGame == TRUE) {
    screenGetPlayerName(playerName);
  } else {
    gameFrontGetPlayerName(playerName);
  }
  gtk_entry_set_text(GTK_ENTRY(idc_setnametxt), playerName);
  dialogSetNameUs = dialogSetName;
  return dialogSetName;
}
