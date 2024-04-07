#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>


// Fonction de rappel pour le bouton
void changeBackgroundColor(Fl_Widget* widget, void* data) {
    Fl_Window* window = (Fl_Window*)data;

    // Changer la couleur de fond en rouge
    window->color(FL_RED); // Rouge
    window->redraw(); // Redessiner la fenêtre pour refléter les changements
}

int main() {
    Fl_Window* window = new Fl_Window(400, 300, "Changer la couleur de fond");

    // Créer un bouton pour changer la couleur de fond
    Fl_Button* button = new Fl_Button(150, 150, 100, 50, "Changer couleur");
    button->callback(changeBackgroundColor, (void*)window); // Passer la fenêtre comme données

    window->end();
    window->show();

    return Fl::run();
}
