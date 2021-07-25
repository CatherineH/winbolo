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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include "../../bolo/global.h"
#include "../linresource.h"
#include "../lang.h"

GtkWidget *label1;
GtkWidget *dialogAllianceUs;
BYTE dialogAlliancePlayerNum;
bool dialogAllianceIsShowing = FALSE;

void dialogAllianceSetName(char *playerName, BYTE playerNum) {
  char output[FILENAME_MAX];

  dialogAlliancePlayerNum = playerNum;
  strcpy(output, playerName);
  strcat(output, langGetText(STR_DLGALLIANCE_BLURB));

  gtk_label_set_text(GTK_LABEL(label1), output);
  gdk_threads_enter();
  gtk_widget_show(dialogAllianceUs);
  gdk_threads_leave();
  dialogAllianceIsShowing = TRUE;
}

gboolean dialogAllianceAccept(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
  netAllianceAccept(dialogAlliancePlayerNum);
  dialogAllianceIsShowing = FALSE;
  gtk_widget_hide(dialogAllianceUs);
  return FALSE;
}
gboolean dialogAllianceReject(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
  dialogAllianceIsShowing = FALSE;
  gtk_widget_hide(dialogAllianceUs);

  return FALSE;
}

GtkWidget* dialogAllianceCreate (void) {
  GtkWidget *dialogAlliance;
  GtkWidget *vbox1;
  GtkWidget *hbox1;
  GtkWidget *button1;
  GtkWidget *button2;

  dialogAlliance = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_object_set_data (dialogAlliance, "dialogAlliance", dialogAlliance);
  gtk_container_set_border_width (GTK_CONTAINER (dialogAlliance), 15);
  gtk_window_set_title (GTK_WINDOW (dialogAlliance), "Alliance Request");

  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);
  gtk_container_child_set (vbox1, dialogAlliance, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogAlliance), vbox1);

  label1 = gtk_label_new ("%s requests alliance. Accept?\n");
  g_object_ref (label1);
  gtk_container_child_set (label1, dialogAlliance, "label1");
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);

  hbox1 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox1);
  gtk_container_child_set (hbox1, dialogAlliance, "hbox1");
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  button1 = gtk_button_new_with_label ("Accept");
  g_object_ref (button1);
  gtk_container_child_set (button1, dialogAlliance, "button1");
  gtk_widget_show (button1);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, TRUE, 0);
  gtk_widget_set_can_focus(button1, TRUE);

  button2 = gtk_button_new_with_label ("Reject");
  g_object_ref (button2);
  gtk_container_child_set (button2, dialogAlliance, "button2");
  gtk_widget_show (button2);
  gtk_box_pack_start (GTK_BOX (hbox1), button2, TRUE, TRUE, 0);

  g_signal_connect(button1, "clicked", G_CALLBACK(dialogAllianceAccept), 0);
  g_signal_connect(button2, "clicked", G_CALLBACK(dialogAllianceReject), 0);

  dialogAllianceUs = dialogAlliance;
  return dialogAlliance;
}
