#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h> 
#include<assert.h>
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
  BTA *av=btopn("AnhViet.dat",0,0);
  BTA *hs=btopn("history.dat",0,0);
  if(hs==NULL) hs=btcrt("history.dat",0,0);
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));//khoitao'buffer'trong'view'

  //gtk_entry_set_text(GTK_ENTRY(search),"search");//chenchu"search"

  if(btsel(av, gtk_entry_get_text(GTK_ENTRY(search)),tv,10000,&n)==0) message("search was done");

//gtk_label_set_text(GTK_LABEL(label),"search was done");//duyettimtrong'b_tree'

  else message("cannot search");

//tk_label_set_text(GTK_LABEL(label),"cannot search");

  gtk_text_buffer_set_text(buffer,tv,-1);//chentatca'tv'vao'buffer'quathamso'-1'
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view),buffer);//chen'buffer'vao'view'
  //btins(hs,gtk_entry_get_text(GTK_ENTRY(search)),tv1,strlen(tv1)+1);
  btins(hs,gtk_entry_get_text(GTK_ENTRY(search)),tv,strlen(tv)+1);
  btcls(av);
  //printf("%s  %s\n",gtk_entry_get_text(GTK_ENTRY(search)),tv1);
  btcls(hs);
  //gtk_label_set_text(GTK_LABEL(label),tv);
  //gtk_label_set_text(GTK_LABEL(label),"teo teo");//doiten'label'
}
void addword(GtkWidget *wiget,gpointer *view)
{
  BTA *av=btopn("AnhViet.dat",0,0);
  char *tv;
  GtkTextIter start,end;//khoitaogiatridauvacuoitrong'view_buffer'
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));//khoitao'buffer'

  gtk_text_buffer_get_start_iter(buffer,&start);//laydauvao
  gtk_text_buffer_get_end_iter(buffer,&end);//laydiemcuoi

  //gtk_entry_set_text(GTK_ENTRY(search),"new_word");//chenchu"new_word"
  tv=gtk_text_buffer_get_text(buffer,&start,&end,FALSE);//gan'tv'

  if(btins(av,gtk_entry_get_text(GTK_ENTRY(search)),tv,strlen(tv)+1)==0) message("insert was done");
  //gtk_label_set_text(GTK_LABEL(label),"insert was done.");
  else message("cannot insert");
  //gtk_label_set_text(GTK_LABEL(label),"cannot insert.\n");
  btcls(av);
}
void deleteword(GtkWidget *wiget,gpointer *search)
{
  BTA *av=btopn("AnhViet.dat",0,0);
  if(btdel(av,gtk_entry_get_text(GTK_ENTRY(search)))==0) 
    message("delete word");//gtk_label_set_text(GTK_LABEL(label),"deleted word.\n");
  else message("cannot delete"); //gtk_label_set_text(GTK_LABEL(label),"cannot delete.\n");
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
  GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));//khoitao'buffer'trong'view'

  btpos(hs,ZSTART);
  while(1)
    {
      if(btseln(hs,ta1,tv,sizeof(tv),&n) == QNOKEY)
	break;
      strcat(ta,"\n");
      strcat(ta,ta1);
    }
  gtk_text_buffer_set_text(buffer,ta,-1);//chentatca'tv'vao'buffer'quathamso'-1'
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view),buffer);//chen'buffer'vao'view'
  btcls(hs);
}

int main( int argc, char *argv[]) 
{
  // GtkWidget *label=gtk_label_new( "no cho vao tu\nxisofj sosl\n");//khoitao'label'
  //khoitaochu"search"
  //gchar *text="search";
  //khoitaowindow
	GtkWidget *window; 
	gtk_init(&argc, &argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);//kichco

	gtk_window_set_position (GTK_WINDOW(window),GTK_WIN_POS_CENTER);//caidat'window'ogiuamanhinh

	search=gtk_search_entry_new ();//khoitaohamtimkiem
	label=gtk_label_new("TUDIEN:ANH-VIET");//khoitao'label'

	GtkWidget *fixed=gtk_fixed_new(); //khoitaonen'fixed'
	GtkWidget *scroll=gtk_scrolled_window_new(NULL,NULL);
	GtkWidget *view=gtk_text_view_new();
	GtkWidget *button1=gtk_button_new_with_label("add word");//khoitaonut'themtu'
	GtkWidget *button2=gtk_button_new_with_label("delete word");//khoitaonut'gopy'
	GtkWidget *button3=gtk_button_new_with_label("search word");//khoitaonut'xoatu'
	GtkWidget *button4=gtk_button_new_with_label("fix word");//khoitao'suatu'
	GtkWidget *button5=gtk_button_new_with_label("history");//khoitao'history'

	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(view),GTK_WRAP_WORD_CHAR);//khoiphaixuongdongtrong'scroll'

	gtk_container_add(GTK_CONTAINER(window), fixed);//chenvaowindownen'fixed',neukhongchenvao'search'ngaytudau
	gtk_container_add(GTK_CONTAINER(scroll),view);//chen'view'vao'scroll'



//taoiconvahinhnen
  GdkPixbuf *create_pixbuf(const gchar * filename) 
{  
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
       
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}
GtkWidget *xpm_label_box2( gchar     *xpm_filename
	)
{
	GtkWidget *box;
    //GtkWidget *label;
	GtkWidget *image;

    /* Create box for image and label */
	box = gtk_box_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
	image = gtk_image_new_from_file (xpm_filename);
	gtk_widget_set_size_request(image,1250,30);

    /* Create a label for the button */
    //label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
	gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
//    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

	gtk_widget_show (image);
    //gtk_widget_show (label);

	return box;
}
   GdkPixbuf *icon = create_pixbuf("icon.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
//GtkWidget*layout=gtk_layout_new(NULL,NULL);
//gtk_container_add(GTK_CONTAINER(window), layout);
	GtkWidget*layoutbox = xpm_label_box2 ("hinhnen.jpg");
	gtk_container_add (GTK_CONTAINER (fixed), layoutbox);
	gtk_widget_show(fixed);
	gtk_widget_show (layoutbox);


	//gtk_entry_set_text(GTK_ENTRY(search), text);//chenchu"search"
	gtk_fixed_put(GTK_FIXED(fixed),search,200,10);//chen'search'vaonen'fixed'vadinhvivitri'search'
	gtk_fixed_put(GTK_FIXED(fixed),button1,10,100);//chen'button1'vaonen'fixed'vadinhvivitri'button1'
	gtk_fixed_put(GTK_FIXED(fixed),button2,10,180);//chen'button2'vaonen'fixed'vadinhvivitri'button2'
	gtk_fixed_put(GTK_FIXED(fixed),button3,10,260);//chen'button3'vaonen'fixed'vadinhvivitri'button3'
	gtk_fixed_put(GTK_FIXED(fixed),button4,10,340);//chen'fix'vao vitri
	gtk_fixed_put(GTK_FIXED(fixed),button5,10,420);//chen'history'vao vitri
	gtk_fixed_put(GTK_FIXED(fixed),scroll,150,100);//chenvaonen'fixed'vadinhvivitri
	gtk_fixed_put(GTK_FIXED(fixed),label,450,480);//chen'label'vao vitri

	gtk_widget_set_size_request(search,10,30);//caikichco'search'
	gtk_widget_set_size_request(button1,100,80);//caikichco'button1'
	gtk_widget_set_size_request(button2,100,80);//caikichco'button2'
	gtk_widget_set_size_request(button3,100,80);//caikichco'button3'
	gtk_widget_set_size_request(button4,100,80);//caikichco'button4'
	gtk_widget_set_size_request(button5,100,80);//caikichco'button5'
	gtk_widget_set_size_request(scroll,320,360);//caikichco'scroll'

	g_signal_connect(button3,"clicked",G_CALLBACK(searchword),view);
	g_signal_connect(button1,"clicked",G_CALLBACK(addword),view);
	g_signal_connect(button2,"clicked",G_CALLBACK(deleteword),search);
	g_signal_connect(button4,"clicked",G_CALLBACK(fixword),view);
	g_signal_connect(button5,"clicked",G_CALLBACK(history),view);
	g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);//thoatkhinhanexit.


	gtk_widget_show_all(window);//phaiviet'show_all'dehienthihet.
	gtk_main(); 
	return 0;
}

//gcc tn1.c -o tn1  `pkg-config gtk+-3.0 --cflags --libs` -I/usr/include/libglade-2.0/ -lglade-2.0
//gcc tn1.c -o tn1  `pkg-config gtk+-3.0 --cflags --libs`  b_tree/lib/libbt.a -w
