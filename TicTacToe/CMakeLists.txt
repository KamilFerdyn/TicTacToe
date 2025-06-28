cmake_minimum_required(VERSION 3.28)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Ustaw ścieżki do SFML zainstalowanego przez Homebrew
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml")

# Znajdź bibliotekę SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Dodaj plik źródłowy
add_executable(TicTacToe TicTacToe.cpp)

# Połącz projekt z bibliotekami SFML
target_link_libraries(TicTacToe sfml-system sfml-window sfml-graphics sfml-network sfml-audio)