#include &lt;stdio.h&gt;#include &lt;gtk/gtk.h&gt;

const gchar *clickme = &quot;Click Me&quot;;
guint counter = 0;

#define MAXLEN 64
void clickedme(GtkButton *o, gpointer d)
{
    GtkLabel *l = GTK_LABEL(d);
    char nt[MAXLEN];
    
    counter++;
    snprintf(nt, MAXLEN, &quot;You clicked me %d times&quot;, counter);
    gtk_label_set_text(l, nt);
}

int main(int argc, char **argv)
{
    GtkWindow *win;
    GtkButton *button;
    GtkLabel *label;
    GtkVBox *vbox;

    gtk_init(&amp;argc, &amp;argv);
    win = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(win, clickme);
    button = (GtkButton*)gtk_button_new_with_label(clickme);
    label = (GtkLabel*)gtk_label_new(&quot;There have been no clicks yet&quot;);
    gtk_label_set_single_line_mode(label, TRUE);
    vbox = (GtkVBox*)gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(label));
    gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(button));
    gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(vbox));
    g_signal_connect(G_OBJECT(win), &quot;delete-event&quot;, (GCallback)gtk_main_quit, NULL);
    g_signal_connect(G_OBJECT(button), &quot;clicked&quot;, (GCallback)clickedme, label);
    gtk_widget_show_all(GTK_WIDGET(win));
    gtk_main();
    return 0;
}
