#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

int main (int argc, char *argv[])
{ 
GladeXML *ui;
gtk_init(&argc, &argv);
ui = glade_xml_new ("glade_hello.glade", "main_window", NULL);
glade_xml_signal_autoconnect(ui);
gtk_main();
return 0;
} 

//gcc 3_cuaso.c -o 3_cuaso  `pkg-config gtk+-2.0 --cflags --libs` -I/usr/include/libglade-2.0/ -lglade-2.0
