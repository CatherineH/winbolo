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

#include "../../bolo/global.h"
#include "gamefront.h"

GtkWidget *dialogPasswordUs;
GtkWidget *idc_passwordtxt;

gboolean dialogPasswordClose(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  char pass[MAP_STR_SIZE]; /* Tracker address   */
  gchar *str;

  str = gtk_entry_get_text(GTK_ENTRY(idc_passwordtxt));
  strncpy(pass, str, MAP_STR_SIZE);

  gameFrontSetGameOptions(pass, gameOpen, FALSE, FALSE, 0, 0, TRUE);
  gtk_grab_remove(dialogPasswordUs);
  gtk_widget_destroy(dialogPasswordUs);
  gtk_main_quit();
  return FALSE;
}

gboolean dialogPasswordKey(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
  if (event->keyval == 65293) {
    dialogPasswordClose(dialogPasswordUs, NULL, NULL);
  }
  return FALSE;
}


GtkWidget* dialogPasswordCreate(void) {
  GtkWidget *dailogPassword;
  GtkWidget *vbox1;
  GtkWidget *label1;
  GtkWidget *hbox1;
  GtkWidget *button1;

  dailogPassword = gtk_dialog_new();
  g_object_set_data (dailogPassword, "dailogPassword", dailogPassword);
  gtk_container_set_border_width (GTK_CONTAINER (dailogPassword), 7);
  gtk_window_set_title (GTK_WINDOW (dailogPassword), "Password");
  gtk_window_set_modal (GTK_WINDOW (dailogPassword), TRUE);
  gtk_window_set_policy (GTK_WINDOW (dailogPassword), FALSE, FALSE, FALSE);

  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);
  gtk_container_child_set (vbox1, dailogPassword, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dailogPassword), vbox1);
  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 4);

  label1 = gtk_label_new ("This game is password protected.\nEnter the correct password to join:");
  g_object_ref (label1);
  gtk_container_child_set (label1, dailogPassword, "label1");
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

  hbox1 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox1);
  gtk_container_child_set (hbox1, dailogPassword, "hbox1");
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  idc_passwordtxt = gtk_entry_new ();
  g_object_ref (idc_passwordtxt);
  gtk_container_child_set (idc_passwordtxt, dailogPassword, "idc_passwordtxt");
  gtk_widget_show (idc_passwordtxt);
  gtk_box_pack_start (GTK_BOX (hbox1), idc_passwordtxt, TRUE, TRUE, 0);
  gtk_entry_set_visibility (GTK_ENTRY (idc_passwordtxt), FALSE);

  button1 = gtk_button_new_with_label ("OK");
  g_object_ref (button1);
  gtk_container_child_set (button1, dailogPassword, "button1");
  gtk_widget_show (button1);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, TRUE, 0);
  gtk_widget_set_can_default(button1, TRUE);
  gtk_widget_grab_focus (idc_passwordtxt);
  gtk_widget_grab_default (button1);

  g_signal_connect(dailogPassword, "delete_event", G_CALLBACK(dialogPasswordClose), NULL);
  g_signal_connect(button1, "clicked", G_CALLBACK(dialogPasswordClose), 0);
  g_signal_connect(idc_passwordtxt, "key-press-event", G_CALLBACK(dialogPasswordKey), 0);

  dialogPasswordUs = dailogPassword;
  return dailogPassword;
}
