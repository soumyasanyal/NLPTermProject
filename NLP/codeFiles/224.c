#include &lt;gtk/gtk.h&gt;
int main (int argc, char **argv) {
  GtkWidget *window;
  gtk_init(&amp;argc, &amp;argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), &quot;Goodbye, World&quot;);
  g_signal_connect (G_OBJECT (window), &quot;delete-event&quot;, gtk_main_quit, NULL);
  gtk_widget_show_all (window);

  gtk_main();
  return 0;
}
