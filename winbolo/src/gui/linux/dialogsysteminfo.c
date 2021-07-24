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
*Name:          Dialog - System Info
*Filename:      dialogsysteminfo.c
*Author:        John Morrison
*Creation Date: 23/1/99
*Last Modified: 29/4/00
*Purpose:
*  Looks after the system info dialog box.
**********************************************************/

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
#include "draw.h"
#include "dialogsysteminfo.h"

/* Text Widgets */
GtkWidget *lblSimModelling;
GtkWidget *lblCommProcessing;
GtkWidget *lblGraphics;
GtkWidget *lblAi;
GtkWidget *lblTotal;
GtkWidget *lblFPS;

int sysInfoTimer;

/*********************************************************
*NAME:          dialogSysInfoUpdate
*AUTHOR:        John Morrison
*CREATION DATE: 29/1/99
*LAST MODIFIED: 23/1/99
*PURPOSE:
* Updates the system info dialog box
*
*ARGUMENTS:
*  hWnd - The dialog window handle
*********************************************************/
gint dialogSysInfoUpdate(gpointer data) {
  int value;       /* Used to hold the frame rate */
  float graphics;
  float sim;
  float net;
  char str[FILENAME_MAX]; /* Frame rate as a string */

  /* Frame Rate */
  str[0] = '\0';
  value = drawGetFrameRate();
  sprintf(str, "%d", value);
  gtk_label_set_text(GTK_LABEL(lblFPS), str);

  /* Graphics */
  value = windowGetDrawTime();
  str[0] = '\0';
  value /= 2.0;
  graphics = (float) ((value/SECOND) *100.0);
  sprintf(str, "%.2f %%", graphics);
  gtk_label_set_text(GTK_LABEL(lblGraphics), str);

  /* Sim */
  value = windowGetSimTime();
  str[0] = '\0';
  sim = (float) ((value/SECOND)*100.0);
  sprintf(str, "%.2f %%", sim);
  gtk_label_set_text(GTK_LABEL(lblSimModelling), str);

  /* Net */
  value = windowGetNetTime();
  str[0] = '\0';
  net = (float) ((value/SECOND)*100.0);
  sprintf(str, "%.2f %%", net);
  gtk_label_set_text(GTK_LABEL(lblCommProcessing), str);

  /* AI */
  value = windowGetAiTime();
  str[0] = '\0';
  net = (float) ((value/SECOND)*100.0);
  sprintf(str, "%.2f %%", net);
  gtk_label_set_text(GTK_LABEL(lblAi), str);

  /* Total */
  sim += graphics + net;
  sprintf(str, "%.2f %%", sim);
  gtk_label_set_text(GTK_LABEL(lblTotal), str);

  return TRUE;
}

void windowSystemInfoClose();

gint dialogSystemInfoClose(GtkWidget *widget, gpointer gdata) {
  gtk_timeout_remove(sysInfoTimer);
  windowSystemInfoClose();
  return FALSE;
}


GtkWidget* dialogSystemInfoCreate(void) {
  GtkWidget *dialogSystemInfo;
  GtkWidget *vbox1;
  GtkWidget *hbox7;
  GtkWidget *label13;
  GtkWidget *label26;
  GtkWidget *hbox8;
  GtkWidget *label14;
  GtkWidget *hbox9;
  GtkWidget *label16;
  GtkWidget *hbox10;
  GtkWidget *label18;
  GtkWidget *hbox11;
  GtkWidget *label20;
  GtkWidget *hbox12;
  GtkWidget *label22;
  GtkWidget *label27;
  GtkWidget *hbox13;
  GtkWidget *label24;

  dialogSystemInfo = gtk_dialog_new ();
  gtk_object_set_data (GTK_OBJECT (dialogSystemInfo), "dialogSystemInfo", dialogSystemInfo);
  gtk_widget_set_usize (dialogSystemInfo, 300, 150);
  gtk_container_set_border_width (GTK_CONTAINER (dialogSystemInfo), 15);
  gtk_window_set_title (GTK_WINDOW (dialogSystemInfo), "LinBolo System Information");
    gtk_window_set_policy(GTK_WINDOW(dialogSystemInfo), FALSE, FALSE, FALSE);
  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_container_child_set (vbox1, GTK_OBJECT (dialogSystemInfo), "vbox1");
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (dialogSystemInfo), vbox1);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox7);
  gtk_container_child_set (hbox7, GTK_OBJECT (dialogSystemInfo), "hbox7");
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox7, TRUE, TRUE, 0);

  label13 = gtk_label_new ("CPU Usage: ");
  gtk_widget_ref (label13);
  gtk_container_child_set (label13, GTK_OBJECT (dialogSystemInfo), "label13");
  gtk_widget_show (label13);
  gtk_box_pack_start (GTK_BOX (hbox7), label13, FALSE, FALSE, 0);

  label26 = gtk_label_new ("");
  gtk_widget_ref (label26);
  gtk_container_child_set (label26, GTK_OBJECT (dialogSystemInfo), "label26");
  gtk_widget_show (label26);
  gtk_box_pack_start (GTK_BOX (vbox1), label26, FALSE, FALSE, 0);

  hbox8 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox8);
  gtk_container_child_set (hbox8, GTK_OBJECT (dialogSystemInfo), "hbox8");
  gtk_widget_show (hbox8);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox8, TRUE, TRUE, 0);

  label14 = gtk_label_new ("Simulation modelling: ");
  gtk_widget_ref (label14);
  gtk_container_child_set (label14, GTK_OBJECT (dialogSystemInfo), "label14");
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (hbox8), label14, FALSE, FALSE, 0);

  lblSimModelling = gtk_label_new ("0.00%");
  gtk_widget_ref (lblSimModelling);
  gtk_container_child_set (lblSimModelling, GTK_OBJECT (dialogSystemInfo), "lblSimModelling");
  gtk_widget_show (lblSimModelling);
  gtk_box_pack_end (GTK_BOX (hbox8), lblSimModelling, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (lblSimModelling), GTK_JUSTIFY_FILL);

  hbox9 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox9);
  gtk_container_child_set (hbox9, GTK_OBJECT (dialogSystemInfo), "hbox9");
  gtk_widget_show (hbox9);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox9, TRUE, TRUE, 0);

  label16 = gtk_label_new ("Communication processing:");
  gtk_widget_ref (label16);
  gtk_container_child_set (label16, GTK_OBJECT (dialogSystemInfo), "label16");
  gtk_widget_show (label16);
  gtk_box_pack_start (GTK_BOX (hbox9), label16, FALSE, FALSE, 0);

  lblCommProcessing = gtk_label_new ("0.00%");
  gtk_widget_ref (lblCommProcessing);
  gtk_container_child_set (lblCommProcessing, GTK_OBJECT (dialogSystemInfo), "lblCommProcessing");
  gtk_widget_show (lblCommProcessing);
  gtk_box_pack_end (GTK_BOX (hbox9), lblCommProcessing, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (lblCommProcessing), GTK_JUSTIFY_LEFT);

  hbox10 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox10);
  gtk_container_child_set (hbox10, GTK_OBJECT (dialogSystemInfo), "hbox10");
  gtk_widget_show (hbox10);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox10, TRUE, TRUE, 0);

  label18 = gtk_label_new ("Graphics display:");
  gtk_widget_ref (label18);
  gtk_container_child_set (label18, GTK_OBJECT (dialogSystemInfo), "label18");
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox10), label18, FALSE, FALSE, 0);

  lblGraphics = gtk_label_new ("0.00%");
  gtk_widget_ref (lblGraphics);
  gtk_container_child_set (lblGraphics, GTK_OBJECT (dialogSystemInfo), "lblGraphics");
  gtk_widget_show (lblGraphics);
  gtk_box_pack_end (GTK_BOX (hbox10), lblGraphics, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (lblGraphics), GTK_JUSTIFY_RIGHT);

  hbox11 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox11);
  gtk_container_child_set (hbox11, GTK_OBJECT (dialogSystemInfo), "hbox11");
  gtk_widget_show (hbox11);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox11, FALSE, FALSE, 0);

  label20 = gtk_label_new ("AI tank control processing:");
  gtk_widget_ref (label20);
  gtk_container_child_set (label20, GTK_OBJECT (dialogSystemInfo), "label20");
  gtk_widget_show (label20);
  gtk_box_pack_start (GTK_BOX (hbox11), label20, FALSE, FALSE, 0);

  lblAi = gtk_label_new ("0.00%");
  gtk_widget_ref (lblAi);
  gtk_container_child_set (lblAi, GTK_OBJECT (dialogSystemInfo), "lblAi");
  gtk_widget_show (lblAi);
  gtk_box_pack_end (GTK_BOX (hbox11), lblAi, FALSE, FALSE, 0);

  hbox12 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox12);
  gtk_container_child_set (hbox12, GTK_OBJECT (dialogSystemInfo), "hbox12");
  gtk_widget_show (hbox12);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox12, TRUE, TRUE, 0);

  label22 = gtk_label_new ("Total:");
  gtk_widget_ref (label22);
  gtk_container_child_set (label22, GTK_OBJECT (dialogSystemInfo), "label22");
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (hbox12), label22, FALSE, FALSE, 0);

  lblTotal = gtk_label_new ("0.00%");
  gtk_widget_ref (lblTotal);
  gtk_container_child_set (lblTotal, GTK_OBJECT (dialogSystemInfo), "lblTotal");
  gtk_widget_show (lblTotal);
  gtk_box_pack_end (GTK_BOX (hbox12), lblTotal, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (lblTotal), GTK_JUSTIFY_RIGHT);
  gtk_label_set_line_wrap (GTK_LABEL (lblTotal), TRUE);
  gtk_misc_set_alignment (GTK_MISC (lblTotal), 1, 0.5);

  label27 = gtk_label_new ("");
  gtk_widget_ref (label27);
  gtk_container_child_set (label27, GTK_OBJECT (dialogSystemInfo), "label27");
  gtk_widget_show (label27);
  gtk_box_pack_start (GTK_BOX (vbox1), label27, FALSE, FALSE, 0);

  hbox13 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox13);
  gtk_container_child_set (hbox13, GTK_OBJECT (dialogSystemInfo), "hbox13");
  gtk_widget_show (hbox13);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox13, TRUE, TRUE, 0);

  label24 = gtk_label_new ("Graphics frames per second: ");
  gtk_widget_ref (label24);
  gtk_container_child_set (label24, GTK_OBJECT (dialogSystemInfo), "label24");
  gtk_widget_show (label24);
  gtk_box_pack_start (GTK_BOX (hbox13), label24, FALSE, FALSE, 0);

  lblFPS = gtk_label_new ("2");
  gtk_widget_ref (lblFPS);
  gtk_container_child_set (lblFPS, GTK_OBJECT (dialogSystemInfo), "lblFPS");
  gtk_widget_show (lblFPS);
  gtk_box_pack_end (GTK_BOX (hbox13), lblFPS, FALSE, FALSE, 0);

  sysInfoTimer = gtk_timeout_add (SECOND, dialogSysInfoUpdate, (gpointer) NULL);
  gtk_signal_connect(GTK_OBJECT(dialogSystemInfo), "delete_event", GTK_SIGNAL_FUNC (dialogSystemInfoClose), NULL);
  dialogSysInfoUpdate(NULL);
  return dialogSystemInfo;
}
