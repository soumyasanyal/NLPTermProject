#include &lt;gtk/gtk.h&gt;
int
main(int argc, char *argv[]) 
{
  GtkWidget *window;

  gtk_init(&amp;argc, &amp;argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_signal_connect(GTK_OBJECT(window), &quot;destroy&quot;,
    GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
  gtk_widget_show(window);
  gtk_main();

  return 0;
}
