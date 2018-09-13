#include<stdio.h>
#include <gtk/gtk.h> 

int main( int argc, char *argv[]) { 
	GtkWidget *window; 
	gtk_init(&argc, &argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_widget_show(window); gtk_main(); 
	return 0;
}
/*gcc tn.c -o tn  `pkg-config gtk+-2.0 --cflags --libs` -I/usr/include/libglade-2.0/ -lglade-2.0

trong do tn:ten file tao ra.
	   tn :ten chung ta muon hien ra o tren cung cua window.
*/
