#include &lt;stdlib.h&gt;#include &lt;string.h&gt;
#include &lt;gtk/gtk.h&gt;

const gchar *hello = &quot;Hello World! &quot;;
gint direction = -1;
gint cx=0;
gint slen=0;

GtkLabel *label;

void change_dir(GtkLayout *o, gpointer d)
{
  direction = -direction;
}

gchar *rotateby(const gchar *t, gint q, gint l)
{
  gint i, cl = l, j;
  gchar *r = malloc(l+1);
  for(i=q, j=0; cl &gt; 0; cl--, i = (i + 1)%l, j++)
    r[j] = t[i];
  r[l] = 0;
  return r;
}

gboolean scroll_it(gpointer data)
{
  if ( direction &gt; 0 )
    cx = (cx + 1) % slen;
  else
    cx = (cx + slen - 1 ) % slen;
  gchar *scrolled = rotateby(hello, cx, slen);
  gtk_label_set_text(label, scrolled);
  free(scrolled);
  return TRUE;
}


int main(int argc, char **argv)
{
  GtkWidget *win;
  GtkButton *button;
  PangoFontDescription *pd;

  gtk_init(&amp;argc, &amp;argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win), &quot;Basic Animation&quot;);
  g_signal_connect(G_OBJECT(win), &quot;delete-event&quot;, gtk_main_quit, NULL);

  label = (GtkLabel *)gtk_label_new(hello);

  // since we shift a whole character per time, it's better to use
  // a monospace font, so that the shifting seems done at the same pace
  pd = pango_font_description_new();
  pango_font_description_set_family(pd, &quot;monospace&quot;);
  gtk_widget_modify_font(GTK_WIDGET(label), pd);

  button = (GtkButton *)gtk_button_new();
  gtk_container_add(GTK_CONTAINER(button), GTK_WIDGET(label));

  gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(button));
  g_signal_connect(G_OBJECT(button), &quot;clicked&quot;, G_CALLBACK(change_dir), NULL);

  slen = strlen(hello);

  g_timeout_add(125, scroll_it, NULL);
  
  gtk_widget_show_all(GTK_WIDGET(win));
  gtk_main();
  return 0;
}
