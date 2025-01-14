#include "functions.h"
#include "sha256.h"

bool createAccount(sf::RenderWindow& createAccountPage, std::string& userEmail) {

    //sf::RenderWindow createAccountPage(sf::VideoMode(360, 800), "Create Account", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    if(!font.loadFromFile("fonts/mulish/Mulish-Regular.ttf")) {
        createAccountPage.close();
        std::cout << "Error loading font";
        return 1;
    }

    sf::Color background(255, 252, 227);
    sf::Color button(229, 224, 207);
    sf::Color text(39, 33, 33);
    sf::Color nextButton(0, 145, 65);
    sf::Color nextText(255, 252, 227);
    
    //email TEXT
    sf::Text emailText;
    emailText.setFont(font);
    emailText.setFillColor(text);
    emailText.setString("Email:");
    emailText.setCharacterSize(20);
    emailText.setPosition(50, 50);

    //email BOX
    sf::RectangleShape emailBox(sf::Vector2f(200, 30));
    emailBox.setFillColor(background);
    emailBox.setOutlineColor(text);
    emailBox.setOutlineThickness(1);
    emailBox.setPosition(50, 80);

    //email INPUT
    sf::Text emailInput;
    emailInput.setFont(font);
    emailInput.setCharacterSize(20);
    emailInput.setFillColor(text);
    emailInput.setPosition(55, 85);

    std::string email = "";

    //PASSWORD TEXT
    sf::Text passwordText;
    passwordText.setFont(font);
    passwordText.setFillColor(text);
    passwordText.setString("Password:");
    passwordText.setCharacterSize(20);
    passwordText.setPosition(50, 120);

    //PASSWORD BOX
    sf::RectangleShape passwordBox(sf::Vector2f(200, 30));
    passwordBox.setFillColor(background);
    passwordBox.setOutlineColor(text);
    passwordBox.setOutlineThickness(1);
    passwordBox.setPosition(50, 150);

    //PASSWORD INPUT
    sf::Text passwordInput;
    passwordInput.setFont(font);
    passwordInput.setCharacterSize(20);
    passwordInput.setFillColor(text);
    passwordInput.setPosition(55, 155);

    std::string password = "";

    //REENTER PASSWORD TEXT
    sf::Text reenterPasswordText;
    reenterPasswordText.setFont(font);
    reenterPasswordText.setFillColor(text);
    reenterPasswordText.setString("Re-enter Password:");
    reenterPasswordText.setCharacterSize(20);
    reenterPasswordText.setPosition(50, 190);

    //REENTER PASSWORD BOX
    sf::RectangleShape reenterPasswordBox(sf::Vector2f(200, 30));
    reenterPasswordBox.setFillColor(background);
    reenterPasswordBox.setOutlineColor(text);
    reenterPasswordBox.setOutlineThickness(1);
    reenterPasswordBox.setPosition(50, 220);

    //REENTER PASSWORD INPUT
    sf::Text reenterPasswordInput;
    reenterPasswordInput.setFont(font);
    reenterPasswordInput.setCharacterSize(20);
    reenterPasswordInput.setFillColor(text);
    reenterPasswordInput.setPosition(55, 225);

    std::string reenterPassword = "";

    //createAccount BUTTON
    sf::RectangleShape createAccountButton(sf::Vector2f(200, 30));
    createAccountButton.setFillColor(nextButton);
    createAccountButton.setOutlineColor(nextText);
    createAccountButton.setOutlineThickness(1);
    createAccountButton.setPosition(50, 270);

    sf::Text createAccountButtonText;
    createAccountButtonText.setFont(font);
    createAccountButtonText.setString("Create Account");
    createAccountButtonText.setCharacterSize(20);
    createAccountButtonText.setFillColor(nextText);
    createAccountButtonText.setPosition(80, 270);


    bool emailSelected = false;
    bool passwordSelected = false;
    bool reenterPasswordSelected = false;


    while(createAccountPage.isOpen()) {

        sf::Event event;
        while(createAccountPage.pollEvent(event)) {

            //CLOSE PAGE
            if(event.type == sf::Event::Closed) {
                createAccountPage.close();
                return 1; //createAccount page closed prematurely

            }

            //MOUSE CLICKED
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if(createAccountButton.getGlobalBounds().contains(mousePos)){
                        return createAccountButtonClick(email, password, reenterPassword, userEmail);
                    }
                    else if(emailBox.getGlobalBounds().contains(mousePos)) {
                        emailSelected = true;
                        passwordSelected = false;
                        reenterPasswordSelected = false;
                    }
                    else if(passwordBox.getGlobalBounds().contains(mousePos)) {
                        emailSelected = false;
                        passwordSelected = true;
                        reenterPasswordSelected = false;
                    }
                    else if(reenterPasswordBox.getGlobalBounds().contains(mousePos)) {
                        emailSelected = false;
                        passwordSelected = false;
                        reenterPasswordSelected = true;
                    }
                    else {
                        emailSelected = false;
                        passwordSelected = false;
                        reenterPasswordSelected = false;
                    }
                }
            }

            //HANDLE TEXT INPUT
            if(event.type == sf::Event::TextEntered) {
                if(event.text.unicode == 9){ //Tab
                    if(emailSelected) {
                        emailSelected = false;
                        passwordSelected = true;
                    }
                    else if(passwordSelected) {
                        passwordSelected = false;
                        reenterPasswordSelected = true;
                    }
                    else {
                        reenterPassword = false;
                    }
                }
                else if(event.text.unicode == 27) { //Escape
                    emailSelected = false;
                    passwordSelected = false;
                    reenterPasswordSelected = false;
                }
                else if(event.text.unicode == 10 || event.text.unicode == 13) { //Enter / return
                    return createAccountButtonClick(email, password, reenterPassword, userEmail);
                }
                else if(emailSelected) { //Email text box
                    if(event.text.unicode == 8 && !emailInput.getString().isEmpty()) {
                        emailInput.setString(emailInput.getString().substring(0, emailInput.getString().getSize() - 1));
                    }
                    else if(event.text.unicode != 8) {
                        emailInput.setString(emailInput.getString() + static_cast<char>(event.text.unicode));
                    }
                    email = emailInput.getString();
                }
                else if(passwordSelected) { //Password text box
                    if(event.text.unicode == 8 && !passwordInput.getString().isEmpty()) {
                        passwordInput.setString(passwordInput.getString().substring(0, passwordInput.getString().getSize() - 1));
                    }
                    else if(event.text.unicode != 8) {
                        passwordInput.setString(passwordInput.getString() + static_cast<char>(event.text.unicode));
                    }
                    password = passwordInput.getString();
                }
                else if(reenterPasswordSelected) { //re-enter password text box
                    if(event.text.unicode == 8 && !reenterPasswordInput.getString().isEmpty()) {
                        reenterPasswordInput.setString(reenterPasswordInput.getString().substring(0, reenterPasswordInput.getString().getSize() - 1));
                    }
                    else if(event.text.unicode != 8) {
                        reenterPasswordInput.setString(reenterPasswordInput.getString() + static_cast<char>(event.text.unicode));
                    }
                    reenterPassword = reenterPasswordInput.getString();
                }
            }
        }

        
        //UPDATE SCREEN
        createAccountPage.clear(background);
  
        createAccountPage.draw(emailText);
        createAccountPage.draw(emailBox);
        createAccountPage.draw(emailInput);
        createAccountPage.draw(passwordText);
        createAccountPage.draw(passwordBox);
        createAccountPage.draw(passwordInput);
        createAccountPage.draw(reenterPasswordText);
        createAccountPage.draw(reenterPasswordBox);
        createAccountPage.draw(reenterPasswordInput);
        createAccountPage.draw(createAccountButton);
        createAccountPage.draw(createAccountButtonText);

        createAccountPage.display();
    }

    return 0;
}

bool createAccountButtonClick(const std::string& email, const std::string& password, const std::string& reenterPassword, std::string& userEmail) {
    //Email Valid
    int count = 0, size = email.size();
    for(int i = 0; i < size; i++) {
        if(email[i] == '@') count++;
    }
    if((count < 1 || count > 1) && !(size > 4)){
        //Invalid Email
        std::cout << "Invalid Email" << std::endl;
        return 1;
    }
    if(password != reenterPassword){
        //Invalid Password
        std::cout << "Invalid Password" << std::endl;
        return 1;
    }

    //Do Login
    userEmail = email;
    std::string salt = "salt";
    writeUserInfo(email + '\n' + sha256(const_cast<char*>((password + salt).c_str())), email + ".txt");
    return 0;
                        
}