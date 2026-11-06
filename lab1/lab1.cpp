#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;
    int age;

public:
  
    Animal(const std::string& name, int age) : name(name), age(age) {
        std::cout << "Animal created: " << name << ", Age: " << age << std::endl;
    }
    virtual void makeSound() const {
        std::cout << "Animal sound!" << std::endl;
    }
  
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Dog : public Animal {
private:
    std::string breed;

public:
  
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age), breed(breed) {
        std::cout << "Dog created: " << name << ", Age: " << age << ", Breed: " << breed << std::endl;
    }

    
    void makeSound() const {
        std::cout << "Bark!" << std::endl;
    }

    
    void displayInfo() const {
        Animal::displayInfo(); 
        std::cout << "Breed: " << breed << std::endl;
    }
};


class Cat : public Animal {
private:
    std::string color;

public:
  
    Cat(const std::string& name, int age, const std::string& color)
        : Animal(name, age), color(color) {
        std::cout << "Cat created: " << name << ", Age: " << age << ", Color: " << color << std::endl;
    }

    void makeSound() const override {
        std::cout << "Meow!" << std::endl; 
    }

    
    void displayInfo() const {
        Animal::displayInfo(); 
        std::cout << "Color: " << color << std::endl;
    }
};

int main() {
    
    Animal animal("Generic Animal", 5);
    animal.displayInfo();
    animal.makeSound();

    std::cout << std::endl;

  
    Dog dog("Buddy", 3, "Golden Retriever");
    dog.displayInfo();
    dog.makeSound();

    std::cout << std::endl;

    Cat cat("Tom", 2, "Black");
    cat.displayInfo();
    cat.makeSound();

    return 0;
}
