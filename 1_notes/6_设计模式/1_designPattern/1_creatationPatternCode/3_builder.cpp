
#include <iostream>
#include <string>

class Burger {
  public:
    Burger(int size, bool cheese, bool pepperoni, bool lettuce, bool tomato)
        : size(size),
          cheese(cheese),
          pepperoni(pepperoni),
          lettuce(lettuce),
          tomato(tomato) {}

    void show() const {
        std::cout << "Burger size: " << size << "\n"
                  << "Cheese: " << (cheese ? "Yes" : "No") << "\n"
                  << "Pepperoni: " << (pepperoni ? "Yes" : "No") << "\n"
                  << "Lettuce: " << (lettuce ? "Yes" : "No") << "\n"
                  << "Tomato: " << (tomato ? "Yes" : "No") << std::endl;
    }

  private:
    int size;
    bool cheese;
    bool pepperoni;
    bool lettuce;
    bool tomato;
};

class BurgerBuilder {
  public:
    BurgerBuilder(int size)
        : size(size),
          cheese(false),
          pepperoni(false),
          lettuce(false),
          tomato(false) {}

    BurgerBuilder& addCheese() {
        cheese = true;
        return *this;
    }

    BurgerBuilder& addPepperoni() {
        pepperoni = true;
        return *this;
    }

    BurgerBuilder& addLettuce() {
        lettuce = true;
        return *this;
    }

    BurgerBuilder& addTomato() {
        tomato = true;
        return *this;
    }

    Burger build() const {
        return Burger(size, cheese, pepperoni, lettuce, tomato);
    }

  private:
    int size;
    bool cheese;
    bool pepperoni;
    bool lettuce;
    bool tomato;
};

int main() {
    Burger burger =
        BurgerBuilder(14).addPepperoni().addLettuce().addTomato().build();

    burger.show();

    return 0;
}
