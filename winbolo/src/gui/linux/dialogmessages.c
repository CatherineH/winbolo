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
#include "../../bolo/backend.h"


/* Time to wait before next message send */
#define WAIT_TIME 2000

  GtkWidget *idc_label;
  GtkWidget *idc_allplayers;
  GtkWidget *idc_allallies;
  GtkWidget *idc_allnearby;
  GtkWidget *idc_selection;
  GtkWidget *idc_textmessage;
  GtkWidget *idc_sendbutton;
  bool dialogMessagesEnabled = TRUE;
  guint dialogMessagesTimeoutId;


  gboolean dialogMessagesChange(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
  char output[256]; /* Output string                */
  int numSend;      /* Number of players to send to */

  /* Get the number of selected players */
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allplayers)) == TRUE) {
    numSend = screenGetNumPlayers();
  } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allallies)) == TRUE) {
    numSend = screenNumAllies();
  } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allnearby)) == TRUE) {
    numSend = screenNumNearbyTanks();
  } else {
    numSend = screenNumCheckedPlayers();
  }

  /* Make the appropriate message */
  if (numSend == 1) {
    sprintf(output, langGetText(STR_DLGMSG_SENDPLAYER), 1);
  } else {
    sprintf(output, langGetText(STR_DLGMSG_SENDPLAYERS), numSend);
  }
  /* Print it */
  gtk_label_set_text(GTK_LABEL(idc_label), output);

}


gint dialogMessagesEnableButton(gpointer data) {
  gtk_widget_set_sensitive (idc_sendbutton, TRUE);
  g_source_remove(dialogMessagesTimeoutId);
  dialogMessagesEnabled = TRUE;
  return FALSE;
}

gboolean dialogMessagesSend(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  char message[256]; /* Message to send */
  gchar* gc;

  gc = gtk_entry_get_text(GTK_ENTRY(idc_textmessage));

  if (gc != NULL) {
    strcpy(message, gc);
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allplayers)) == TRUE) {
      screenSendMessageAllPlayers(message);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allallies)) == TRUE) {
      screenSendMessageAllAllies(message);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_allnearby)) == TRUE) {
      screenSendMessageAllNearby(message);
    } else {
      screenSendMessageAllSelected(message);
    }
  }
  dialogMessagesTimeoutId = g_timeout_add (WAIT_TIME, dialogMessagesEnableButton, 0);
  gtk_editable_select_region(GTK_EDITABLE(idc_textmessage), 0, -1);
  dialogMessagesEnabled = FALSE;
  gtk_widget_set_sensitive (idc_sendbutton, FALSE);
  return TRUE;
}


gboolean dialogMessagesKey (GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
  if (event->keyval == 65293) {
    if (dialogMessagesEnabled == TRUE) {
      dialogMessagesSend(NULL, NULL, NULL);
      return FALSE;
    }
  }
  return TRUE;
}

void windowMessagesClose();

gboolean dialogMessagesClose(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  if (dialogMessagesEnabled == FALSE) {
    g_source_remove(dialogMessagesTimeoutId);
  }
  windowMessagesClose();
  gtk_widget_destroy(widget);
}

GtkWidget*
dialogMessagesCreate(void)
{
  GtkWidget *dialogMessages;
  GtkWidget *vbox1;
  GSList *vbox1_group = NULL;
 GtkWidget *hbox1;

  dialogMessagesEnabled = TRUE;
  dialogMessages = gtk_dialog_new();

  g_object_set_data (dialogMessages, "dialogMessages", dialogMessages);
  gtk_container_set_border_width (GTK_CONTAINER (dialogMessages), 20);
  gtk_window_set_title (GTK_WINDOW (dialogMessages), "Send Message");
  gtk_window_set_resizable (GTK_WINDOW (dialogMessages), FALSE);
  gtk_window_set_position (GTK_WINDOW (dialogMessages), GTK_WIN_POS_CENTER);

  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);

  gtk_container_child_set (vbox1, dialogMessages, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogMessages), vbox1);

  idc_allplayers = gtk_radio_button_new_with_label (vbox1_group, "All players");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_allplayers));
  g_object_ref (idc_allplayers);
  gtk_container_child_set (idc_allplayers, dialogMessages, "idc_allplayers");
  gtk_widget_show (idc_allplayers);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_allplayers, FALSE, FALSE, 0);

  idc_allallies = gtk_radio_button_new_with_label (vbox1_group, "All allies");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_allallies));
  g_object_ref (idc_allallies);
  gtk_container_child_set (idc_allallies, dialogMessages, "idc_allallies");
  gtk_widget_show (idc_allallies);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_allallies, FALSE, FALSE, 0);

  idc_allnearby = gtk_radio_button_new_with_label (vbox1_group, "All nearby tanks");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_allnearby));
  g_object_ref (idc_allnearby);
  gtk_container_child_set (idc_allnearby, dialogMessages, "idc_allnearby");
  gtk_widget_show (idc_allnearby);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_allnearby, FALSE, FALSE, 0);

  idc_selection = gtk_radio_button_new_with_label (vbox1_group, "Selection on the Players menu");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_selection));
  g_object_ref (idc_selection);
  gtk_container_child_set (idc_selection, dialogMessages, "idc_selection");
  gtk_widget_show (idc_selection);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_selection, FALSE, FALSE, 0);

  idc_label = gtk_label_new ("Sending message to 1 player");
  g_object_ref (idc_label);
  gtk_container_child_set (idc_label, dialogMessages, "idc_label");
  gtk_widget_show (idc_label);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_label, FALSE, FALSE, 0);

  hbox1 = gtk_hbox_new (FALSE, 0);
  g_object_ref (hbox1);
  gtk_container_child_set (hbox1, dialogMessages, "hbox1");
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  idc_textmessage = gtk_entry_new ();
  g_object_ref (idc_textmessage);
  gtk_container_child_set (idc_textmessage, dialogMessages, "idc_textmessage");
  gtk_widget_show (idc_textmessage);
  gtk_box_pack_start (GTK_BOX (hbox1), idc_textmessage, TRUE, TRUE, 0);
  gtk_widget_set_size_request (idc_textmessage, -2, 22);

  idc_sendbutton = gtk_button_new_with_label ("Send");
  g_object_ref (idc_sendbutton);
  gtk_container_child_set (idc_sendbutton, dialogMessages, "idc_sendbutton");
  gtk_widget_show (idc_sendbutton);
  gtk_box_pack_end (GTK_BOX (hbox1), idc_sendbutton, FALSE, FALSE, 1);
  gtk_widget_set_size_request (idc_sendbutton, -2, 22);

  gtk_widget_grab_focus (idc_textmessage);
  /* Connect Signals */
  g_signal_connect(dialogMessages, "focus_in_event", G_CALLBACK(dialogMessagesChange), 0);
  g_signal_connect(dialogMessages, "delete_event", G_CALLBACK(dialogMessagesClose), 0);
  g_signal_connect(idc_allplayers, "clicked", G_CALLBACK(dialogMessagesChange), 0);
  g_signal_connect(idc_allallies, "clicked", G_CALLBACK(dialogMessagesChange), 0);
  g_signal_connect(idc_allnearby, "clicked", G_CALLBACK(dialogMessagesChange), 0);
  g_signal_connect(idc_selection, "clicked", G_CALLBACK(dialogMessagesChange), 0);
  g_signal_connect(idc_sendbutton, "button_press_event", G_CALLBACK(dialogMessagesSend), 0);
  g_signal_connect(idc_textmessage, "key-press-event", G_CALLBACK(dialogMessagesKey), 0);
  return dialogMessages;
}
