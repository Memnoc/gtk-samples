#include <gtk/gtk.h>

#define GRID_SIZE 3

GtkWidget *buttons[GRID_SIZE][GRID_SIZE];
GtkWidget *message_label;
int player = 1;
int moves = 0;

const gchar *highlight_style = ".winning-cell {"
                               "   color: green;"
                               "}";

// Function to highlight the winning cells
void highlight_winner(GtkWidget *button1, GtkWidget *button2,
                      GtkWidget *button3) {
  g_print("Highlighting winner!\n"); // Debug print statement
  GtkStyleContext *context1 = gtk_widget_get_style_context(button1);
  GtkStyleContext *context2 = gtk_widget_get_style_context(button2);
  GtkStyleContext *context3 = gtk_widget_get_style_context(button3);

  gtk_style_context_add_class(context1, "winning-cell");
  gtk_style_context_add_class(context2, "winning-cell");
  gtk_style_context_add_class(context3, "winning-cell");
}

// Function to disable all buttons
void disable_buttons() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      gtk_widget_set_sensitive(buttons[i][j], FALSE);
    }
  }
}
// Callback function for when a button is clicked
void button_clicked(GtkWidget *widget, gpointer data) {
  GtkWidget *button = GTK_WIDGET(widget);
  const gchar *label = gtk_button_get_label(GTK_BUTTON(button));

  // Check if the button is empty and the game is not over
  if (g_strcmp0(label, "") == 0 &&
      g_strcmp0(gtk_label_get_text(GTK_LABEL(message_label)), "") == 0) {
    // Set the button label based on the current player
    gchar *player_symbol = (player == 1) ? "X" : "O";
    gtk_button_set_label(GTK_BUTTON(button), player_symbol);
    player = (player == 1) ? 2 : 1;
    moves++;

    // Check for a winner
    for (int i = 0; i < GRID_SIZE; i++) {
      if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][0])),
                    player_symbol) == 0 &&
          g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][1])),
                    player_symbol) == 0 &&
          g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][2])),
                    player_symbol) == 0) {
        // Horizontal win
        highlight_winner(buttons[i][0], buttons[i][1], buttons[i][2]);
        gtk_label_set_text(GTK_LABEL(message_label),
                           g_strdup_printf("%s wins!", player_symbol));
        disable_buttons();
        return;
      }
      if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][i])),
                    player_symbol) == 0 &&
          g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][i])),
                    player_symbol) == 0 &&
          g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][i])),
                    player_symbol) == 0) {
        // Vertical win
        highlight_winner(buttons[0][i], buttons[1][i], buttons[2][i]);
        gtk_label_set_text(GTK_LABEL(message_label),
                           g_strdup_printf("%s wins!", player_symbol));
        disable_buttons();
        return;
      }
    }
    if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][0])),
                  player_symbol) == 0 &&
        g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][1])),
                  player_symbol) == 0 &&
        g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][2])),
                  player_symbol) == 0) {
      // Diagonal win (top-left to bottom-right)
      highlight_winner(buttons[0][0], buttons[1][1], buttons[2][2]);
      gtk_label_set_text(GTK_LABEL(message_label),
                         g_strdup_printf("%s wins!", player_symbol));
      disable_buttons();
      return;
    }
    if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][2])),
                  player_symbol) == 0 &&
        g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][1])),
                  player_symbol) == 0 &&
        g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][0])),
                  player_symbol) == 0) {
      // Diagonal win (top-right to bottom-left)
      highlight_winner(buttons[0][2], buttons[1][1], buttons[2][0]);
      gtk_label_set_text(GTK_LABEL(message_label),
                         g_strdup_printf("%s wins!", player_symbol));
      disable_buttons();
      return;
    }

    // Check for a draw
    if (moves == GRID_SIZE * GRID_SIZE) {
      gtk_label_set_text(GTK_LABEL(message_label), "It's a draw!");
      return;
    }
  }
}
// // Callback function for when a button is clicked
// void button_clicked(GtkWidget *widget, gpointer data) {
//   GtkWidget *button = GTK_WIDGET(widget);
//   const gchar *label = gtk_button_get_label(GTK_BUTTON(button));
//
//   // Check if the button is empty
//   if (g_strcmp0(label, "") == 0) {
//     // Set the button label based on the current player
//     gchar *player_symbol = (player == 1) ? "X" : "O";
//     gtk_button_set_label(GTK_BUTTON(button), player_symbol);
//     player = (player == 1) ? 2 : 1;
//     moves++;
//
//     // Check for a winner
//     for (int i = 0; i < GRID_SIZE; i++) {
//       if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][0])),
//                     player_symbol) == 0 &&
//           g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][1])),
//                     player_symbol) == 0 &&
//           g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][2])),
//                     player_symbol) == 0) {
//         // Horizontal win
//         gtk_label_set_text(GTK_LABEL(message_label),
//                            g_strdup_printf("%s wins!", player_symbol));
//         return;
//       }
//       if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][i])),
//                     player_symbol) == 0 &&
//           g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][i])),
//                     player_symbol) == 0 &&
//           g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][i])),
//                     player_symbol) == 0) {
//         // Vertical win
//         gtk_label_set_text(GTK_LABEL(message_label),
//                            g_strdup_printf("%s wins!", player_symbol));
//         return;
//       }
//     }
//     if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][0])),
//                   player_symbol) == 0 &&
//         g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][1])),
//                   player_symbol) == 0 &&
//         g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][2])),
//                   player_symbol) == 0) {
//       // Diagonal win (top-left to bottom-right)
//       gtk_label_set_text(GTK_LABEL(message_label),
//                          g_strdup_printf("%s wins!", player_symbol));
//       return;
//     }
//     if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[0][2])),
//                   player_symbol) == 0 &&
//         g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[1][1])),
//                   player_symbol) == 0 &&
//         g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[2][0])),
//                   player_symbol) == 0) {
//       // Diagonal win (top-right to bottom-left)
//       gtk_label_set_text(GTK_LABEL(message_label),
//                          g_strdup_printf("%s wins!", player_symbol));
//       return;
//     }
//
//     // Check for a draw
//     if (moves == GRID_SIZE * GRID_SIZE) {
//       gtk_label_set_text(GTK_LABEL(message_label), "It's a draw!");
//       return;
//     }
//   }
// }

// Callback function for when the "New Game" button is clicked
void new_game_clicked(GtkWidget *widget, gpointer data) {
  // Clear the button labels and reset game variables
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      gtk_button_set_label(GTK_BUTTON(buttons[i][j]), "");
    }
  }
  gtk_label_set_text(GTK_LABEL(message_label), "");
  player = 1;
  moves = 0;
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *new_game_button;

  // Initialize GTK
  gtk_init(&argc, &argv);

  // Create the main window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 350);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkCssProvider *css_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(css_provider, highlight_style, -1, NULL);
  gtk_style_context_add_provider_for_screen(
      gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  // Create the grid
  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  // Set grid alignment to center within the window
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  // Add buttons to the grid
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      buttons[i][j] = gtk_button_new();
      gtk_grid_attach(GTK_GRID(grid), buttons[i][j], i, j, 1, 1);
      g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(button_clicked),
                       NULL);
    }
  }

  // Create the message label
  message_label = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), message_label, 0, GRID_SIZE, GRID_SIZE, 1);

  // Add "New Game" button
  new_game_button = gtk_button_new_with_label("New Game");
  gtk_grid_attach(GTK_GRID(grid), new_game_button, 0, GRID_SIZE + 1, GRID_SIZE,
                  1);
  g_signal_connect(new_game_button, "clicked", G_CALLBACK(new_game_clicked),
                   NULL);

  // Display the window
  gtk_widget_show_all(window);

  // Start the GTK main loop
  gtk_main();

  return 0;
}
