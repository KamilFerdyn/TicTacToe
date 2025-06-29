#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

enum GameMode {
    none,
    playerVsPlayerEnum,
    playerVsComputerEnum,
    choosingDifficulty
};

enum DifficultyLevel {
    noneLevel,
    easy,
    hard
};

DifficultyLevel difficulty = noneLevel;
GameMode gameMode = none;

char checkWinner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> findBestMove(char board[3][3], char aiPlayer, char humanPlayer) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = aiPlayer;
                if (checkWinner(board) == aiPlayer) {
                    board[i][j] = ' '; // Cofnięcie ruchu
                    return std::make_pair(i, j);
                }
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = humanPlayer;
                if (checkWinner(board) == humanPlayer) {
                    board[i][j] = ' '; 
                    return std::make_pair(i, j);
                }
                board[i][j] = ' ';
            }
        }
    }

    if (board[1][1] == ' ') {
        return std::make_pair(1, 1);
    }

    if (board[0][0] == ' ') return std::make_pair(0, 0);
    if (board[0][2] == ' ') return std::make_pair(0, 2);
    if (board[2][0] == ' ') return std::make_pair(2, 0);
    if (board[2][2] == ' ') return std::make_pair(2, 2);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1); // Nie powinno nigdy nastąpić, jeśli gra jest prawidłowo zarządzana
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Kolko i Krzyzyk Kamila Ferdyna");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Text currentPlayerText("Ruch: X", font, 30);
    currentPlayerText.setFillColor(sf::Color::Black);
    currentPlayerText.setPosition(10, 10);

    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};
    char currentPlayer = 'X';
    bool gameActive = false;

    sf::Text playerVsPlayer("Gracz vs Gracz", font, 30);
    playerVsPlayer.setFillColor(sf::Color::Black);
    playerVsPlayer.setPosition(150, 200);

    sf::Text playerVsComputer("Gracz vs Komputer", font, 30);
    playerVsComputer.setFillColor(sf::Color::Black);
    playerVsComputer.setPosition(150, 300);

    sf::RectangleShape button1(sf::Vector2f(300, 80));
    button1.setPosition(150, 190);
    button1.setFillColor(sf::Color::White);
    button1.setOutlineColor(sf::Color::Black);
    button1.setOutlineThickness(5);

    sf::RectangleShape button2(sf::Vector2f(300, 80));
    button2.setPosition(150, 290);
    button2.setFillColor(sf::Color::White);
    button2.setOutlineColor(sf::Color::Black);
    button2.setOutlineThickness(5);

    sf::RectangleShape easyButton(sf::Vector2f(300, 80));
    easyButton.setPosition(150, 190);
    easyButton.setFillColor(sf::Color::White);
    easyButton.setOutlineColor(sf::Color::Black);
    easyButton.setOutlineThickness(5);

    sf::RectangleShape hardButton(sf::Vector2f(300, 80));
    hardButton.setPosition(150, 290);
    hardButton.setFillColor(sf::Color::White);
    hardButton.setOutlineColor(sf::Color::Black);
    hardButton.setOutlineThickness(5);

    sf::Text easyText("Latwy poziom", font, 30);
    easyText.setFillColor(sf::Color::Black);
    easyText.setPosition(200, 200);

    sf::Text hardText("Trudny poziom", font, 30);
    hardText.setFillColor(sf::Color::Black);
    hardText.setPosition(200, 300);

    sf::RectangleShape menuButton(sf::Vector2f(150, 50));
    menuButton.setPosition(225, 500);
    menuButton.setFillColor(sf::Color::White);
    menuButton.setOutlineColor(sf::Color::Black);
    menuButton.setOutlineThickness(5);

    sf::Text menuButtonText("Menu", font, 24);
    menuButtonText.setFillColor(sf::Color::Black);
    menuButtonText.setPosition(265, 510);

    sf::RectangleShape line1(sf::Vector2f(600, 5));
    sf::RectangleShape line2(sf::Vector2f(600, 5));
    sf::RectangleShape line3(sf::Vector2f(5, 600));
    sf::RectangleShape line4(sf::Vector2f(5, 600));

    line1.setPosition(0, 200);
    line2.setPosition(0, 400);
    line3.setPosition(200, 0);
    line4.setPosition(400, 0);

    line1.setFillColor(sf::Color::Black);
    line2.setFillColor(sf::Color::Black);
    line3.setFillColor(sf::Color::Black);
    line4.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (gameMode == none) {
                        if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            gameMode = playerVsPlayerEnum;
                            gameActive = true;
                        }

                        if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            gameMode = choosingDifficulty;
                        }
                    } else if (gameMode == choosingDifficulty) {
                        if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            difficulty = easy;
                            gameMode = playerVsComputerEnum;
                            gameActive = true;
                        }
                        if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            difficulty = hard;
                            gameMode = playerVsComputerEnum;
                            gameActive = true;
                        }
                    } else if (gameActive) {
                        int row = mousePos.y / 200;
                        int col = mousePos.x / 200;

                        if (row < 3 && col < 3 && board[row][col] == ' ') {
                            board[row][col] = currentPlayer;
                            char winner = checkWinner(board);

                            if (winner != ' ') {
                                currentPlayerText.setString(std::string(1, winner) + " wygrywa!");
                                gameActive = false;
                            } else if (isBoardFull(board)) {
                                currentPlayerText.setString("Remis!");
                                gameActive = false;
                            } else {
                                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                currentPlayerText.setString("Ruch: " + std::string(1, currentPlayer));
                            }

                            if (gameMode == playerVsComputerEnum && difficulty == easy && gameActive) {
                                bool moveMade = false;
                                while (!moveMade) {
                                    int aiRow = std::rand() % 3;
                                    int aiCol = std::rand() % 3;
                                    if (board[aiRow][aiCol] == ' ') {
                                        board[aiRow][aiCol] = currentPlayer;
                                        moveMade = true;
                                    }
                                }
                                winner = checkWinner(board);
                                if (winner != ' ') {
                                    currentPlayerText.setString(std::string(1, winner) + " wygrywa!");
                                    gameActive = false;
                                } else if (isBoardFull(board)) {
                                    currentPlayerText.setString("Remis!");
                                    gameActive = false;
                                } else {
                                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                    currentPlayerText.setString("Ruch: " + std::string(1, currentPlayer));
                                }
                            }

                            if (gameMode == playerVsComputerEnum && difficulty == hard && gameActive) {
                                std::pair<int, int> bestMove = findBestMove(board, currentPlayer, (currentPlayer == 'X') ? 'O' : 'X');
                                if (bestMove.first != -1) {
                                    board[bestMove.first][bestMove.second] = currentPlayer;
                                }

                                winner = checkWinner(board);
                                if (winner != ' ') {
                                    currentPlayerText.setString(std::string(1, winner) + " wygrywa!");
                                    gameActive = false;
                                } else if (isBoardFull(board)) {
                                    currentPlayerText.setString("Remis!");
                                    gameActive = false;
                                } else {
                                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                    currentPlayerText.setString("Ruch: " + std::string(1, currentPlayer));
                                }
                            }
                        }
                    }

                    if (!gameActive && menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                        gameMode != none) {
                        gameMode = none;
                        difficulty = noneLevel;
                        gameActive = false;
                        currentPlayer = 'X';
                        currentPlayerText.setString("Ruch: " + std::string(1, currentPlayer));
                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                board[i][j] = ' ';
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        if (gameMode == none) {
            window.draw(button1);
            window.draw(playerVsPlayer);
            window.draw(button2);
            window.draw(playerVsComputer);
        } else if (gameMode == choosingDifficulty) {
            window.draw(easyButton);
            window.draw(hardButton);
            window.draw(easyText);
            window.draw(hardText);
        } else if (gameMode != none) {
            window.draw(line1);
            window.draw(line2);
            window.draw(line3);
            window.draw(line4);

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == 'X' || board[i][j] == 'O') {
                        sf::Text mark(std::string(1, board[i][j]), font, 100);
                        mark.setFillColor(sf::Color::Black);
                        mark.setPosition(j * 200 + 50, i * 200 + 50);
                        window.draw(mark);
                    }
                }
            }
            window.draw(currentPlayerText);

            if (!gameActive) {
                window.draw(menuButton);
                window.draw(menuButtonText);
            }
        }

        window.display();
    }

    return 0;
}
