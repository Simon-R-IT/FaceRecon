#include <stdlib.h>
#include <gtk/gtk.h> 

void AddImage(GtkButton* button, GtkImage* Image);
void file_ok_sel(GtkWidget *w, GtkFileSelection *fs);
void FileSelec(GtkButton* button);

int main(int argc,char **argv)
{ 
	/* Widgets delcaration */
	GtkWidget *pWindow;
	GtkWidget *pTable;
	GtkWidget *pButton[3];
	GtkWidget *pImage;
	gtk_init(&argc,&argv);
  
	/* Main Window settings */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 1000, 700);
	gtk_window_set_title(GTK_WINDOW(pWindow), "FaceRecon");
	g_signal_connect(G_OBJECT(pWindow), "destroy",G_CALLBACK(gtk_main_quit),NULL);
	pTable = gtk_table_new(10,8,TRUE);
	gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

	/* Initialization */
	pButton[0] = gtk_button_new_with_label("Load Image");
	pButton[1] = gtk_button_new_with_label("Load Image From File");
	pButton[2] = gtk_button_new_with_label("Quit");
	pImage = gtk_image_new();
	gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[0],1,2,3,4);
	gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[1],1,2,4,5);
	gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[2],1,2,5,6);
	gtk_table_attach_defaults(GTK_TABLE(pTable), pImage,5,9,1,9);
    
	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(AddImage), pImage);
	g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(FileSelec),NULL);
	g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(gtk_main_quit),NULL);
	/* Window display */
	gtk_widget_show_all(pWindow);
	/* Start */
	gtk_main();
    
	return EXIT_SUCCESS;
}

void AddImage(GtkButton* button, GtkImage* Image)
{
	gtk_image_set_from_file(Image, "./test.png");
}

void FileSelec(GtkButton* button)
{
	GtkWidget *selec;
	selec = gtk_file_selection_new("File Selection");
	
//	gtk_signal_connect(selec,"destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(selec)->ok_button),"clicked", G_CALLBACK(file_ok_sel), selec);
	gtk_widget_show(selec);
}

 void file_ok_sel(GtkWidget *w, GtkFileSelection *fs)
{
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
	gtk_widget_destroy(GTK_WIDGET(fs));

}

/*char* FileChooser(GtkButton* button)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	dialog = gtk_file_chooser_dialog_new("Open File", parent_window,action,_("_Cancel"),GTK_RESPONSE_CANCEL,_("_Open"),GTK_RESPONSE_ACCEPT,NULL);
	res = gtk_dialog_ru(GTK_DIALOG(dialog));
	if(res == GTK_RESPONSE_ACCEPT)
	{
		char *filename
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
	}
	gtk_widget_destroy(dialog);
	return filename
}


void file_ok_sel(GtkWidget *w, GtkFileSelection *fs, GtkImage* Image)
{
	
	gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs));
	gtk_widget_destroy(GTK_WIDGET(fs));

}*/
