#include<stdio.h>
#include<gtk/gtk.h>

int main(int argc,char *argv[])
{
  GtkWidget *window;
  gtk_init(&argc,&argv);
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),500,500);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);//thoatkhinhanexit.

	GtkWidget *fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);

        //iconandimage
        GdkPixbuf *icon;
        GError *error = NULL;
        icon = gdk_pixbuf_new_from_file("icon.png", &error);
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	GtkWidget *box;
	GtkWidget *image;
	box = gtk_box_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	image = gtk_image_new_from_file ("hinhnen.jpg");
        gtk_widget_set_size_request(image,30,30);
	gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
	gtk_container_add (GTK_CONTAINER (fixed), box);
	gtk_widget_show(fixed);
	gtk_widget_show (box);
	gtk_widget_show (image);


  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}

//gcc tn.c -o tn  `pkg-config gtk+-3.0 --cflags --libs` 
