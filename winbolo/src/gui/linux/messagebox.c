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
#include "SDL/SDL.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "../../bolo/global.h"

GtkWidget *mbUs;
#define timeGetTime() SDL_GetTicks()

gboolean messageBoxOK(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  gtk_grab_remove(mbUs);
  gtk_widget_destroy(mbUs);
  gtk_main_quit();
  return FALSE;
}

gboolean messageBoxClose(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  gtk_grab_remove(mbUs);
  gtk_widget_destroy(mbUs);
  gtk_main_quit();
 return FALSE;
}


GtkWidget* create_MessageBox (char *name, char *label) {
  GtkWidget *MessageBox;
  GtkWidget *vbox1;
  GtkWidget *label1;
  GtkWidget *idc_messageboxok;

  MessageBox = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (MessageBox), "name", MessageBox);
  gtk_window_set_title (GTK_WINDOW (MessageBox), name);
  gtk_window_set_policy (GTK_WINDOW (MessageBox), FALSE, FALSE, FALSE);
  gtk_window_set_position (GTK_WINDOW (MessageBox), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (MessageBox), TRUE);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_container_child_set (vbox1, GTK_OBJECT (MessageBox), "vbox1");
  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 5);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (MessageBox), vbox1);

  label1 = gtk_label_new (label);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);
  gtk_widget_ref (label1);
  gtk_container_child_set (label1, GTK_OBJECT (MessageBox), "label1");
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 10);

  idc_messageboxok = gtk_button_new_with_label ("OK");
  gtk_widget_ref (idc_messageboxok);
  gtk_container_child_set (idc_messageboxok, GTK_OBJECT (MessageBox), "idc_messageboxok");
  gtk_container_set_border_width (GTK_CONTAINER (idc_messageboxok), 5);
  gtk_widget_show (idc_messageboxok);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_messageboxok, FALSE, FALSE, 5);
  GTK_WIDGET_SET_FLAGS (idc_messageboxok, GTK_CAN_DEFAULT);

  gtk_widget_grab_focus (idc_messageboxok);
  gtk_widget_grab_default (idc_messageboxok);

  gtk_signal_connect(GTK_OBJECT(idc_messageboxok), "clicked", GTK_SIGNAL_FUNC(messageBoxOK), 0);
  gtk_signal_connect(GTK_OBJECT(MessageBox), "delete_event", GTK_SIGNAL_FUNC(messageBoxClose), 0);
  mbUs = MessageBox;
  return MessageBox;
}

void MessageBox(char *label, char *title) {
  GtkWidget *mb;
  mb = create_MessageBox(title, label);
  gtk_widget_show(mb);
  gtk_grab_add(mb);
  gtk_main();
}

void MessageBox2(char *label, char *title, char *label2, char *title2) {
  MessageBox(label, title);
  MessageBox(label2, title2);
}

void MessageBox3(char *label, char *title, char *label2, char *title2, char *label3, char *title3) {
  MessageBox(label, title);
  MessageBox(label2, title2);
  MessageBox(label3, title3);
}
