///gcc window.c -o window `pkg-config gtk+-3.0 --cflags --libs`  bt-5.0.0/lib/libbt.a -w


#include <gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include"bt-5.0.0/inc/btree.h"


BTA* book;
GtkListStore *list;
GtkWidget *text_mean;



//Tạo cửa sổ thông báo
//parent: cửa sổ cha, type: loại thông báo, mms: chủ đề, content: nội dung 
void Show_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) {
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),GTK_DIALOG_DESTROY_WITH_PARENT,
	                		type,GTK_BUTTONS_OK,"%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

//Xóa cửa sổ
void destroy_something(GtkWidget * widget, gpointer gp) {
	gtk_widget_destroy(gp);
}

//Sửa 1 từ trong từ điển 
static void edit_to_dict(GtkWidget *widget,gpointer data){
	GtkWidget *view;
	GtkWidget *deldialog;
	GtkTextIter start,end;
  	GtkTextBuffer *buffer;
	const gchar *entry_text;
	char *mean,mean2[10000]; int size;

  	entry_text = gtk_entry_get_text (GTK_ENTRY (((GtkWidget**)data)[0]));
	view=((GtkWidget**)data)[1];
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
 	gtk_text_buffer_get_start_iter(buffer,&start);
  	gtk_text_buffer_get_end_iter(buffer,&end);
  	mean=gtk_text_buffer_get_text(buffer,&start,&end,FALSE);
	

	if (entry_text[0]=='\0' || mean[0]=='\0'){
		Show_message(((GtkWidget**)data)[2], GTK_MESSAGE_WARNING, 
			"Cảnh báo!", "Không được bỏ trống phần nào.");
		return 0;
	}


	if (btsel(book,entry_text,mean2,0,&size)!=0)
		Show_message(((GtkWidget**)data)[2], GTK_MESSAGE_ERROR, 
			"Xảy ra lỗi!","Từ này chưa có trong từ điển.");		
	else{	
		// Tạo thông báo xác nhận
		deldialog = gtk_message_dialog_new(GTK_WINDOW(((GtkWidget**)data)[2]),
	                  GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,
	                  GTK_BUTTONS_YES_NO,"Sửa: \"%s\"?", entry_text);
		gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(deldialog), 
			"Bạn thực sự muốn sửa từ \"%s\" không?",entry_text);
	
		

		int result = gtk_dialog_run(GTK_DIALOG(deldialog));
		if (result == GTK_RESPONSE_YES){
			if (btupd(book, entry_text, mean, 10000)==0) 
				Show_message(((GtkWidget**)data)[2], GTK_MESSAGE_INFO, 
						"Thành công!", "Đã sửa từ trong từ điển");
		}
		gtk_widget_destroy(deldialog);
	}
	
}
		

//Tạo form cho cửa sổ chức năng sửa từ 
static void edit_word(GtkWidget *widget,GtkWidget *DATA){
	GtkWidget *window;
	GtkWidget *button1,*button2;
	GtkWidget *label1,*label2;
	GtkWidget *entry;
	GtkWidget *view;
	GtkWidget *scroll;
	GtkWidget *fixed; 

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), " Sua từ ");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	
	view=gtk_text_view_new();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(view),GTK_WRAP_WORD_CHAR);
	scroll=gtk_scrolled_window_new(NULL,NULL);
	gtk_container_add(GTK_CONTAINER(scroll),view);

	label1 = gtk_label_new("NHập từ tiếng anh can sua");
	label2 = gtk_label_new("NHập nghĩa");	

	entry = gtk_entry_new ();
	gtk_entry_set_text(entry,gtk_entry_get_text (GTK_ENTRY (DATA)));

	button1 = gtk_button_new_with_label ("Sửa từ");
	button2 = gtk_button_new_with_label ("Thoát");
	
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_fixed_put(GTK_FIXED(fixed),label1,0,0);
	gtk_fixed_put(GTK_FIXED(fixed),entry,0,20);
	gtk_fixed_put(GTK_FIXED(fixed),label2,0,60);
	gtk_fixed_put(GTK_FIXED(fixed),scroll,0,90);
	gtk_fixed_put(GTK_FIXED(fixed),button1,70,260);
	gtk_fixed_put(GTK_FIXED(fixed),button2,210,260);

	gtk_widget_set_size_request(entry, 300, 30);
	gtk_widget_set_size_request(scroll, 350, 120);
	gtk_widget_set_size_request(button1, 90, 50);
	gtk_widget_set_size_request(button2, 90, 50);

	GtkWidget * data[3];
	data[0] = entry;
	data[1] = view;
	data[2] = window;	

	g_signal_connect (button1, "clicked",G_CALLBACK (edit_to_dict),data);
	g_signal_connect (button2, "clicked",G_CALLBACK(destroy_something),window);
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(destroy_something), window); 

	gtk_widget_show_all(window);
	gtk_main();
}


//Xóa từ khỏi từ điển 
static void delete_to_dict(GtkWidget *widget,gpointer data){

	const gchar *entry_text;
	char *mean,mean2[10000]; int size;

  	entry_text = gtk_entry_get_text (GTK_ENTRY (((GtkWidget**)data)[0]));
	
	if (entry_text[0]=='\0'){
		Show_message(((GtkWidget**)data)[2], GTK_MESSAGE_WARNING, 
			"Cảnh báo!", "Nhập từ cần xóa vào.");
		return 0;
	}

	if (btsel(book,entry_text,mean2,10000,&size)!=0){
		Show_message(((GtkWidget**)data)[2],GTK_MESSAGE_ERROR, 
			"Xảy ra lỗi!","Không tìm thấy từ này trong từ điển.");
		return 0;
	}


	//Tạo cửa sổ thông báo yêu cầu xác nhận
	GtkWidget *deldialog;
	deldialog = gtk_message_dialog_new(GTK_WINDOW(((GtkWidget**)data)[2]),
	                                   GTK_DIALOG_DESTROY_WITH_PARENT,
	                                   GTK_MESSAGE_QUESTION,
	                                   GTK_BUTTONS_YES_NO,
	                                   "Xóa: \"%s\"?", entry_text);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(deldialog), 			"Bạn thực sự muốn xóa từ \"%s\" chứ?",entry_text);

	int result = gtk_dialog_run(GTK_DIALOG(deldialog));
	if (result == GTK_RESPONSE_YES){
		if (btdel(book, entry_text)==0)
			Show_message(((GtkWidget**)data)[2], GTK_MESSAGE_INFO, 
					"Thành công!", "Da xoa khỏi từ điển");
	}
	gtk_widget_destroy(deldialog);	
}


//Tạo form cửa sổ xóa từ
static void delete_word(GtkWidget *widget,GtkWidget *DATA){
	GtkWidget *window;
	GtkWidget *button1,*button2;
	GtkWidget *label1,*label2;
	GtkWidget *entry;
	GtkWidget *fixed;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), " Thêm từ ");
	gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	
	label1 = gtk_label_new("NHập từ cần xóa");
	entry = gtk_entry_new ();
	gtk_entry_set_text(entry,gtk_entry_get_text (GTK_ENTRY (DATA)));
	button1 = gtk_button_new_with_label ("Xoá");
	button2 = gtk_button_new_with_label ("Thoát");
	
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_fixed_put(GTK_FIXED(fixed),label1,0,0);
	gtk_fixed_put(GTK_FIXED(fixed),entry,0,20);
	gtk_fixed_put(GTK_FIXED(fixed),button1,40,100);
	gtk_fixed_put(GTK_FIXED(fixed),button2,180,100);

	gtk_widget_set_size_request(entry, 300, 30);
	gtk_widget_set_size_request(button1, 90, 50);
	gtk_widget_set_size_request(button2, 90, 50);

	GtkWidget *data[3];
	data[0] = entry;
	data[2] = window;	

	g_signal_connect (button1, "clicked",G_CALLBACK (delete_to_dict),data);
	g_signal_connect (button2, "clicked",G_CALLBACK(destroy_something),window);
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(destroy_something), window); 
	
	gtk_widget_show_all(window);
	gtk_main();
}


int main(int argc, char *argv[]) {

	btinit();
	book=btopn("words.dat",0,0);
	if(!book){
		printf("Khong the mo file!\n");
		return 0;
	}	


	//Khao bao cac bien	
	GtkWidget *window;
	GtkWidget *label;
	GtkWidget *text_search;
	GtkWidget *search_button;
	GtkWidget *edit_button;
	GtkWidget *insert_button;
	GtkWidget *delete_button;
	GtkWidget *history_button;
	GtkWidget *exit_button;
	GtkWidget *scrolling;


	//Khoi tao cua so man hinh chinh
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Test");
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
	

  	
	label = gtk_label_new("NHập từ cần tìm");
	
	//Khởi tạo text_search để nhập từ 
	text_search = gtk_search_entry_new ();
    	gtk_entry_set_max_length (GTK_ENTRY (text_search), 50);	


	//Khởi tạo comple: danh sách các gợi ý khi tìm kiếm  
	GtkEntryCompletion *comple;
	comple = gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(comple, 0);
	list = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
	        G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);
	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
	gtk_entry_set_completion(GTK_ENTRY(text_search), comple);
	

	//Khởi tạo các nút
	search_button = gtk_button_new_with_label ("Tìm kiếm");
	edit_button = gtk_button_new_with_label ("Sửa từ");
	insert_button = gtk_button_new_with_label ("Thêm từ");
	delete_button = gtk_button_new_with_label ("Xóa từ");
	history_button = gtk_button_new_with_label ("Lịch sử");
	exit_button = gtk_button_new_with_label ("Thoát");
	

	//Khởi tạo text_mean để hiện thị nghĩa khi tìm kiếm
	scrolling=gtk_scrolled_window_new(NULL,NULL);
	text_mean=gtk_text_view_new();
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_mean), GTK_WRAP_WORD_CHAR);//Chong tran be ngang
	gtk_container_add(GTK_CONTAINER(scrolling), text_mean);


	//Định vị trí cho các đối tượng 
	GtkWidget *fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_fixed_put(GTK_FIXED(fixed),label,10,0);
	gtk_fixed_put(GTK_FIXED(fixed),text_search,10,20);
	gtk_fixed_put(GTK_FIXED(fixed),search_button,200,10);
	gtk_fixed_put(GTK_FIXED(fixed),edit_button,280,10);
	gtk_fixed_put(GTK_FIXED(fixed),insert_button,360,10);
	gtk_fixed_put(GTK_FIXED(fixed),delete_button,440,10);
	gtk_fixed_put(GTK_FIXED(fixed),history_button,520,10);
	gtk_fixed_put(GTK_FIXED(fixed),exit_button,600,10);
	gtk_fixed_put(GTK_FIXED(fixed),scrolling,210,80);
	

	//Định kích thước cho các đối tượng 
	gtk_widget_set_size_request(text_search, 180, 30);
	gtk_widget_set_size_request(search_button, 75, 45);
	gtk_widget_set_size_request(edit_button, 75, 45);
	gtk_widget_set_size_request(insert_button, 75, 45);
	gtk_widget_set_size_request(delete_button, 75, 45);
	gtk_widget_set_size_request(history_button, 75, 45);
	gtk_widget_set_size_request(exit_button, 75, 45);
	gtk_widget_set_size_request(scrolling, 435, 380);


	//Tạo các sự kiện 
	//g_signal_connect (text_search, "changed",G_CALLBACK (remove_all_list),NULL);
	//g_signal_connect (text_search, "changed",G_CALLBACK (suggest_word),text_search);
	//g_signal_connect (text_search, "activate",G_CALLBACK (search_word),text_search);
	//g_signal_connect (search_button, "clicked",G_CALLBACK (search_word),text_search);
	g_signal_connect (edit_button, "clicked",G_CALLBACK (edit_word),text_search);
	//g_signal_connect (insert_button, "clicked",G_CALLBACK (insert_word),NULL);
	g_signal_connect (delete_button, "clicked",G_CALLBACK (delete_word),text_search);
	//g_signal_connect (history_button, "clicked",G_CALLBACK (history_word),NULL);
	g_signal_connect (exit_button, "clicked",G_CALLBACK (gtk_main_quit),NULL);
 	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();

	btcls(book);
	return 0;
}

