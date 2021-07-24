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
#include "../../bolo/network.h"
#include "dialognetworkinfo.h"

/* Labels */
GtkWidget *lblServerAddress;
GtkWidget *lblGameAddress;
GtkWidget *lblPing;
GtkWidget *lblPPS;
GtkWidget *lblStatus;
GtkWidget *lblErrors;
GtkWidget *dialogNetworkUs;
/* Timer */
int timerNetworkInfo;


/*********************************************************
*NAME:          dialogNetInfoUpdate
*AUTHOR:        John Morrison
*CREATION DATE: 3/3/99
*LAST MODIFIED: 1/9/99
*PURPOSE:
* Updates the network info dialog box
*
*ARGUMENTS:
*  hWnd - The dialog window handle
*********************************************************/
gint dialogNetInfoUpdate(gpointer data) {
  int ping;               /* Downstream delay */
  int ppsec;              /* Packets per second */
  int numErrors;          /* Number of errors */
  char str[FILENAME_MAX]; /* Strings to display */

  /* Get addresses */
  netGetServerAddressStr(str);
  gtk_label_set_text(GTK_LABEL(lblServerAddress), str);

  /* Get data */
  netGetStats(str, &ping, &ppsec, &numErrors);
  /* Print data items */
  gtk_label_set_text(GTK_LABEL(lblStatus), str);
  sprintf(str, "%i", ping);
  gtk_label_set_text(GTK_LABEL(lblPing), str);
  sprintf(str, "%i", ppsec);
  gtk_label_set_text(GTK_LABEL(lblPPS), str);
  sprintf(str, "%i", numErrors);
  gtk_label_set_text(GTK_LABEL(lblErrors), str);
  return TRUE;
}

void windowNetworkInfoClose();

gint dialogNetworkInfoClose(GtkWidget *widget, gpointer gdata) {
  gtk_timeout_remove(timerNetworkInfo);
  windowNetworkInfoClose();
  return FALSE;
}


GtkWidget*
dialogNetworkInformationCreate(void)
{
  GtkWidget *dialogNetworkInformation;
  GtkWidget *vbox1;
  GtkWidget *hbox13;
  GtkWidget *hbox14;
  GtkWidget *label31;
  GtkWidget *hbox15;
  GtkWidget *label33;
  GtkWidget *hbox16;
  GtkWidget *label35;
  GtkWidget *hbox17;
  GtkWidget *label37;
  GtkWidget *hbox18;
  GtkWidget *label41;
  GtkWidget *label29;
  char str[FILENAME_MAX]; /* Strings to display */

  dialogNetworkInformation = gtk_dialog_new();
  gtk_object_set_data (GTK_OBJECT (dialogNetworkInformation), "dialogNetworkInformation", dialogNetworkInformation);
  gtk_widget_set_usize (dialogNetworkInformation, 300, 150);
  gtk_container_set_border_width (GTK_CONTAINER (dialogNetworkInformation), 15);
  gtk_window_set_title (GTK_WINDOW (dialogNetworkInformation), "LinBolo Network Information");
  gtk_window_set_policy(GTK_WINDOW(dialogNetworkInformation), FALSE, FALSE, FALSE);
  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_container_child_set (vbox1, GTK_OBJECT (dialogNetworkInformation), "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogNetworkInformation), vbox1);

  hbox13 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox13);

  gtk_container_child_set (hbox13, GTK_OBJECT (dialogNetworkInformation), "hbox13");
  gtk_widget_show (hbox13);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox13, TRUE, TRUE, 0);

  label29 = gtk_label_new ("Server Addresss: ");
  gtk_widget_ref (label29);

  gtk_container_child_set (label29, GTK_OBJECT (dialogNetworkInformation), "label29");
  gtk_widget_show (label29);
  gtk_box_pack_start (GTK_BOX (hbox13), label29, FALSE, FALSE, 0);

  lblServerAddress = gtk_label_new ("");
  gtk_widget_ref (lblServerAddress);

  gtk_container_child_set (lblServerAddress, GTK_OBJECT (dialogNetworkInformation), "lblServerAddress");
  gtk_widget_show (lblServerAddress);
  gtk_box_pack_end (GTK_BOX (hbox13), lblServerAddress, FALSE, FALSE, 0);

  hbox14 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox14);

  gtk_container_child_set (hbox14, GTK_OBJECT (dialogNetworkInformation), "hbox14");
  gtk_widget_show (hbox14);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox14, TRUE, TRUE, 0);

  label31 = gtk_label_new ("This game address");
  gtk_widget_ref (label31);

  gtk_container_child_set (label31, GTK_OBJECT (dialogNetworkInformation), "label31");
  gtk_widget_show (label31);
  gtk_box_pack_start (GTK_BOX (hbox14), label31, FALSE, FALSE, 0);

  lblGameAddress = gtk_label_new ("");
  gtk_widget_ref (lblGameAddress);

  gtk_container_child_set (lblGameAddress, GTK_OBJECT (dialogNetworkInformation), "lblGameAddress");
  gtk_widget_show (lblGameAddress);
  gtk_box_pack_end (GTK_BOX (hbox14), lblGameAddress, FALSE, FALSE, 0);

  hbox15 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox15);

  gtk_container_child_set (hbox15, GTK_OBJECT (dialogNetworkInformation), "hbox15");
  gtk_widget_show (hbox15);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox15, TRUE, TRUE, 0);

  label33 = gtk_label_new ("Server ping (ms) ");
  gtk_widget_ref (label33);

  gtk_container_child_set (label33, GTK_OBJECT (dialogNetworkInformation), "label33");
  gtk_widget_show (label33);
  gtk_box_pack_start (GTK_BOX (hbox15), label33, FALSE, FALSE, 0);

  lblPing = gtk_label_new ("");
  gtk_widget_ref (lblPing);

  gtk_container_child_set (lblPing, GTK_OBJECT (dialogNetworkInformation), "lblPing");
  gtk_widget_show (lblPing);
  gtk_box_pack_end (GTK_BOX (hbox15), lblPing, FALSE, FALSE, 0);

  hbox16 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox16);

  gtk_container_child_set (hbox16, GTK_OBJECT (dialogNetworkInformation), "hbox16");
  gtk_widget_show (hbox16);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox16, TRUE, TRUE, 0);

  label35 = gtk_label_new ("Packets per second (per player)");
  gtk_widget_ref (label35);

  gtk_container_child_set (label35, GTK_OBJECT (dialogNetworkInformation), "label35");
  gtk_widget_show (label35);
  gtk_box_pack_start (GTK_BOX (hbox16), label35, FALSE, FALSE, 0);

  lblPPS = gtk_label_new ("");
  gtk_widget_ref (lblPPS);

  gtk_container_child_set (lblPPS, GTK_OBJECT (dialogNetworkInformation), "lblPPS");
  gtk_widget_show (lblPPS);
  gtk_box_pack_end (GTK_BOX (hbox16), lblPPS, FALSE, FALSE, 0);

  hbox17 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox17);

  gtk_container_child_set (hbox17, GTK_OBJECT (dialogNetworkInformation), "hbox17");
  gtk_widget_show (hbox17);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox17, TRUE, TRUE, 0);

  label37 = gtk_label_new ("Network status");
  gtk_widget_ref (label37);

  gtk_container_child_set (label37, GTK_OBJECT (dialogNetworkInformation), "label37");
  gtk_widget_show (label37);
  gtk_box_pack_start (GTK_BOX (hbox17), label37, FALSE, FALSE, 0);

  lblStatus = gtk_label_new ("");
  gtk_widget_ref (lblStatus);

  gtk_container_child_set (lblStatus, GTK_OBJECT (dialogNetworkInformation), "lblStatus");
  gtk_widget_show (lblStatus);
  gtk_box_pack_end (GTK_BOX (hbox17), lblStatus, FALSE, FALSE, 0);

  hbox18 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox18);

  gtk_container_child_set (hbox18, GTK_OBJECT (dialogNetworkInformation), "hbox18");
  gtk_widget_show (hbox18);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox18, TRUE, TRUE, 0);

  label41 = gtk_label_new ("Network errors");
  gtk_widget_ref (label41);

  gtk_container_child_set (label41, GTK_OBJECT (dialogNetworkInformation), "label41");
  gtk_widget_show (label41);
  gtk_box_pack_start (GTK_BOX (hbox18), label41, FALSE, FALSE, 0);

  lblErrors = gtk_label_new ("");
  gtk_widget_ref (lblErrors);

  gtk_container_child_set (lblErrors, GTK_OBJECT (dialogNetworkInformation), "lblErrors");
  gtk_widget_show (lblErrors);
  gtk_box_pack_end (GTK_BOX (hbox18), lblErrors, FALSE, FALSE, 0);

  timerNetworkInfo = gtk_timeout_add(250/* SECOND */, dialogNetInfoUpdate, (gpointer) NULL);
  gtk_signal_connect(GTK_OBJECT(dialogNetworkInformation), "delete_event", GTK_SIGNAL_FUNC (dialogNetworkInfoClose), NULL);

  netGetOurAddressStr(str);
  gtk_label_set_text(GTK_LABEL(lblGameAddress), str);
  dialogNetInfoUpdate(NULL);
  dialogNetworkUs = dialogNetworkInformation;
  return dialogNetworkInformation;
}
