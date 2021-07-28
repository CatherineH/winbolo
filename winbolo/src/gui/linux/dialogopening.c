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


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include "smalllogo.xpm"
#include "../../bolo/global.h"
#include "gamefront.h"
#include "messagebox.h"
#include "dialogwinbolonet.h"
#include "boloicon.xpm"


GtkWidget *idc_opentutorial;
GtkWidget *idc_opensingle;
GtkWidget *idc_opentcp;
GtkWidget *idc_openlocal;
GtkWidget *idc_openinternet;
GtkWidget *us;

GtkRequisition req;
gint opening_configure_event (GtkWidget *window, GdkEventConfigure *event) {
  //TODO: change to cairo surface
  /*GdkPixmap *pixmap;
  GdkBitmap *mask;

  pixmap = gdk_pixmap_create_from_xpm_d (gtk_widget_get_window(window), &mask, gtk_widget_get_style(&window)->bg[GTK_STATE_NORMAL], boloicon_xpm);
  gdk_window_set_icon (gtk_widget_get_window(window), NULL, pixmap, mask);*/
  return TRUE;
}



gboolean dialogOpeningClose(GtkWidget *widget,  GdkEventButton *event, gpointer user_data) {
  gtk_widget_destroy(us);
  gtk_main_quit();
  return FALSE;
}

void dialogOpeningWinbolonet(GtkWidget *widget, gpointer user_data) {
  GtkWidget *wbn;

  wbn = dialogWinboloNetCreate();
  gtk_grab_add(wbn);
  gtk_widget_show(wbn);
  gtk_main();

}

void dialogOpeningOK(GtkWidget *widget, gpointer user_data) {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_opentcp)) == TRUE) {
    gameFrontSetDlgState(us, openUdp);
  } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_openlocal)) == TRUE) {
    gameFrontSetDlgState(us, openLan);
  } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_openinternet)) == TRUE) {
    gameFrontSetDlgState(us, openInternet);
  } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(idc_opentutorial)) == TRUE) {
    gameFrontSetDlgState(us, openTutorial);
  } else {
    gameFrontSetDlgState(us, openSetup);
  }
}

void dialogOpeningQuit(GtkWidget *widget, gpointer user_data) {
  // TODO: figure out whether this is essential
  // gdk_key_repeat_restore();
  exit(0);
}

void dialogOpeningCloseBox(GtkWidget *widget, gpointer user_data) {
  // TODO: figure out whether this is essential
  // gdk_key_repeat_restore();
  exit(0);
}


void dialogOpeningHelp(GtkWidget *widget, gpointer user_data) {
  MessageBox("Please consult the manual.pdf file in the LinBolo directory.", DIALOG_BOX_TITLE);
}

GtkWidget* dialogOpeningCreate(void) {
  GtkWidget *dialogOpening;
  GtkWidget *vbox1;
  GtkWidget *pixmap1;
  GtkWidget *label1;
  GSList *vbox1_group = NULL;
  GtkWidget *idc_openskip;
  GtkWidget *table1;
  GtkWidget *idc_openquit;
  GtkWidget *idc_openhelp;
  GtkWidget *idc_openlanguages;
  GtkWidget *idc_openok;

  //TODO: replace with cairo surface
  //GdkPixmap *pixmap_data;
  //GdkPixmap *pixmap_mask;
  GtkWidget *pixw;


  dialogOpening = gtk_dialog_new();
  g_object_set_data (dialogOpening, "dialogOpening", dialogOpening);
  gtk_container_set_border_width (GTK_CONTAINER (dialogOpening), 20);
  gtk_window_set_title (GTK_WINDOW (dialogOpening), "Network Selection");
  gtk_window_set_resizable (GTK_WINDOW (dialogOpening), FALSE);
  gtk_window_set_position (GTK_WINDOW (dialogOpening), GTK_WIN_POS_CENTER);
  vbox1 = gtk_vbox_new (FALSE, 0);
  g_object_ref (vbox1);
  gtk_container_child_set (vbox1, dialogOpening, "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogOpening), vbox1);

  /*pixmap_data = gdk_pixmap_colormap_create_from_xpm_d(NULL, gtk_widget_get_colormap(dialogOpening), &pixmap_mask, NULL, smalllogo_xpm);
  pixmap1 = gtk_pixmap_new(pixmap_data, pixmap_mask);
  g_object_ref (pixmap1);
  gdk_pixmap_unref(pixmap_data);
  gdk_pixmap_unref(pixmap_mask);
  gtk_container_child_set (pixmap1, dialogOpening, "pixmap1");
  gtk_widget_show (pixmap1);
  gtk_box_pack_start (GTK_BOX (vbox1), pixmap1, TRUE, TRUE, 0);
  */
  label1 = gtk_label_new ("Welcome to LinBolo, the multiplayer tank game.\nPlease choose a game type from the list below:\n");
  g_object_ref (label1);
  gtk_container_child_set (label1, dialogOpening, "label1");
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

  idc_opentutorial = gtk_radio_button_new_with_label (vbox1_group, "Tutorial (Instruction for first-time player)");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_opentutorial));
  g_object_ref (idc_opentutorial);
  gtk_container_child_set (idc_opentutorial, dialogOpening, "idc_opentutorial");
  gtk_widget_show (idc_opentutorial);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_opentutorial, FALSE, FALSE, 0);

  idc_opensingle = gtk_radio_button_new_with_label (vbox1_group, "Practise (Single Player; No Network)");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_opensingle));
  g_object_ref (idc_opensingle);
  gtk_container_child_set (idc_opensingle, dialogOpening, "idc_opensingle");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(idc_opensingle), TRUE);
  gtk_widget_show (idc_opensingle);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_opensingle, FALSE, FALSE, 0);
  idc_opentcp = gtk_radio_button_new_with_label (vbox1_group, "TCP/IP");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_opentcp));
  g_object_ref (idc_opentcp);
  gtk_container_child_set (idc_opentcp, dialogOpening, "idc_opentcp");
  gtk_widget_show (idc_opentcp);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_opentcp, FALSE, FALSE, 0);

  idc_openlocal = gtk_radio_button_new_with_label (vbox1_group, "Local Network (Broadcast Search)");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_openlocal));
  g_object_ref (idc_openlocal);
  gtk_container_child_set (idc_openlocal, dialogOpening, "idc_openlocal");
  gtk_widget_show (idc_openlocal);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_openlocal, FALSE, FALSE, 0);

  idc_openinternet = gtk_radio_button_new_with_label (vbox1_group, "Internet (Tracker Search)");
  vbox1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (idc_openinternet));
  g_object_ref (idc_openinternet);
  gtk_container_child_set (idc_openinternet, dialogOpening, "idc_openinternet");
  gtk_widget_show (idc_openinternet);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_openinternet, FALSE, FALSE, 0);

  idc_openskip = gtk_check_button_new_with_label ("Skip this dialog next time");
  g_object_ref (idc_openskip);
  gtk_container_child_set (idc_openskip, dialogOpening, "idc_openskip");
  gtk_widget_show (idc_openskip);
  gtk_box_pack_start (GTK_BOX (vbox1), idc_openskip, FALSE, FALSE, 10);
  gtk_widget_set_sensitive (idc_openskip, FALSE);

  table1 = gtk_table_new (2, 2, FALSE);
  g_object_ref (table1);
  gtk_container_child_set (table1, dialogOpening, "table1");
  gtk_widget_show (table1);
  gtk_box_pack_start (GTK_BOX (vbox1), table1, TRUE, TRUE, 0);

  idc_openquit = gtk_button_new_with_label ("Quit");
  g_object_ref (idc_openquit);
  gtk_container_child_set (idc_openquit, dialogOpening, "idc_openquit");
  gtk_widget_show (idc_openquit);
  gtk_table_attach (GTK_TABLE (table1), idc_openquit, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  idc_openhelp = gtk_button_new_with_label ("Help");
  g_object_ref (idc_openhelp);
  gtk_container_child_set (idc_openhelp, dialogOpening, "idc_openhelp");
  gtk_widget_show (idc_openhelp);
  gtk_table_attach (GTK_TABLE (table1), idc_openhelp, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  idc_openlanguages = gtk_button_new_with_label ("WinBolo.net");
  g_object_ref (idc_openlanguages);
  gtk_container_child_set (idc_openlanguages, dialogOpening, "idc_openlanguages");
  gtk_widget_set_sensitive(idc_openlanguages, TRUE);
  gtk_widget_show (idc_openlanguages);
  gtk_table_attach (GTK_TABLE (table1), idc_openlanguages, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  idc_openok = gtk_button_new_with_label ("OK");
  g_object_ref (idc_openok);
  gtk_container_child_set (idc_openok, dialogOpening, "idc_openok");
  gtk_widget_show (idc_openok);
  gtk_table_attach (GTK_TABLE (table1), idc_openok, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  g_signal_connect(dialogOpening, "delete_event", G_CALLBACK(dialogOpeningClose), NULL);
  g_signal_connect(idc_openquit, "clicked", G_CALLBACK(dialogOpeningQuit), 0);
  g_signal_connect(idc_openok, "clicked", G_CALLBACK(dialogOpeningOK), 0);
  g_signal_connect(idc_openhelp, "clicked", G_CALLBACK(dialogOpeningHelp), 0);
  g_signal_connect(idc_openlanguages, "clicked", G_CALLBACK(dialogOpeningWinbolonet), 0);
  g_signal_connect(dialogOpening, "destroy", G_CALLBACK(dialogOpeningCloseBox), 0);
  us = dialogOpening;

  g_signal_connect(us, "configure_event", G_CALLBACK(opening_configure_event), 0);


  return dialogOpening;
}
