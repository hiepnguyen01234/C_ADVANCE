#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <gtk/gtk.h> 
#include "b_tree/inc/btree.h"
GtkWidget *search;
GtkWidget *label;
void message(char *text)
{
  GtkWidget *window=gtk_window_new(GTK_WINDOW_POPUP);
  GtkWidget *dialog;
  dialog=gtk_message_dialog_new((GtkWindow*)window, GTK_DIALOG_MODAL,GTK_MESSAGE_INFO, GTK_BUTTONS_OK,text);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
void searchword(GtkWidget *wiget,gpointer *view)
{
  int n;
  char tv[10000];
  char tv1[3];
  BTA *av=btopn("AnhViet.dat",0,0);
  BTA *hs=btopn("history.dat",0,0);
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
  if(btsel(av, gtk_entry_get_text(GTK_ENTRY(search)),tv,10000,&n)==0) message("search was done");
  else message("cannot search");
  gtk_text_buffer_set_text(buffer,tv,-1);
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view),buffer);
  btins(hs,gtk_entry_get_text(GTK_ENTRY(search)),NULL,NULL);
  btcls(av);
  btcls(hs);
}
void addword(GtkWidget *wiget,gpointer *view)
{
  BTA *av=btopn("AnhViet.dat",0,0);
  char *tv;
  GtkTextIter start,end;
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
  gtk_text_buffer_get_start_iter(buffer,&start);
  gtk_text_buffer_get_end_iter(buffer,&end);
  tv=gtk_text_buffer_get_text(buffer,&start,&end,FALSE);
  if(btins(av,gtk_entry_get_text(GTK_ENTRY(search)),tv,strlen(tv)+1)==0) message("insert was done");
  else message("cannot insert");
  btcls(av);
}
void deleteword(GtkWidget *wiget,gpointer *search)
{
  BTA *av=btopn("AnhViet.dat",0,0);
  if(btdel(av,gtk_entry_get_text(GTK_ENTRY(search)))==0) 
    message("delete word");
  else message("cannot delete"); 
  btcls(av);
}
void fixword(GtkWidget *wiget,gpointer *view)
{
  deleteword(wiget,search);
  addword(wiget,view);
}
void history(GtkWidget *wiget,gpointer *view)
{
  int n;
  char ta[10000];
  char ta1[100];
  char tv[10000];
  BTA *hs=btopn("history.dat",0,0);
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
  btpos(hs,ZSTART);
  while(1)
    {
      if(btseln(hs,ta1,tv,sizeof(tv),&n) == QNOKEY)
	break;
      strcat(ta,"\n");
      strcat(ta,ta1);
    }
  gtk_text_buffer_set_text(buffer,ta,-1);
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view),buffer);
  btcls(hs);
}
int main( int argc, char *argv[]) 
{
	GtkWidget *window; 
	gtk_init(&argc, &argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_position (GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	search=gtk_search_entry_new ();
	label=gtk_label_new("TUDIEN:ANH-VIET");
	GtkWidget *fixed=gtk_fixed_new(); 
	GtkWidget *scroll=gtk_scrolled_window_new(NULL,NULL);
	GtkWidget *view=gtk_text_view_new();
	GtkWidget *button1=gtk_button_new_with_label("add word");
	GtkWidget *button2=gtk_button_new_with_label("delete word");
	GtkWidget *button3=gtk_button_new_with_label("search word");
	GtkWidget *button4=gtk_button_new_with_label("fix word");
	GtkWidget *button5=gtk_button_new_with_label("history");
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(view),GTK_WRAP_WORD_CHAR);
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_container_add(GTK_CONTAINER(scroll),view);

        //iconandimage
        GdkPixbuf *icon;
        GError *error = NULL;
        icon = gdk_pixbuf_new_from_file("icon.png", &error);
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	GtkWidget *box;
	GtkWidget *image;
	box = gtk_box_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	image = gtk_image_new_from_file ("hinhnen1.jpg");
        gtk_widget_set_size_request(image,500,500);
	gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
	gtk_container_add (GTK_CONTAINER (fixed), box);
	gtk_widget_show(fixed);
	gtk_widget_show (box);
	gtk_widget_show (image);

	gtk_fixed_put(GTK_FIXED(fixed),search,200,10);
	gtk_fixed_put(GTK_FIXED(fixed),button1,10,100);
	gtk_fixed_put(GTK_FIXED(fixed),button2,10,180);
	gtk_fixed_put(GTK_FIXED(fixed),button3,10,260);
	gtk_fixed_put(GTK_FIXED(fixed),button4,10,340);
	gtk_fixed_put(GTK_FIXED(fixed),button5,10,420);
	gtk_fixed_put(GTK_FIXED(fixed),scroll,150,100);
	gtk_fixed_put(GTK_FIXED(fixed),label,450,480);
	gtk_widget_set_size_request(search,10,30);
	gtk_widget_set_size_request(button1,100,80);
	gtk_widget_set_size_request(button2,100,80);
	gtk_widget_set_size_request(button3,100,80);
	gtk_widget_set_size_request(button4,100,80);
	gtk_widget_set_size_request(button5,100,80);
	gtk_widget_set_size_request(scroll,320,360);
	g_signal_connect(button3,"clicked",G_CALLBACK(searchword),view);
	g_signal_connect(button1,"clicked",G_CALLBACK(addword),view);
	g_signal_connect(button2,"clicked",G_CALLBACK(deleteword),search);
	g_signal_connect(button4,"clicked",G_CALLBACK(fixword),view);
	g_signal_connect(button5,"clicked",G_CALLBACK(history),view);
	g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main(); 
	return 0;
}
//gcc window.c -o window `pkg-config gtk+-3.0 --cflags --libs`  b_tree/lib/libbt.a -w
