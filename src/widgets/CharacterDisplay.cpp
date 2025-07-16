#include "CharacterDisplay.hpp"

using namespace rack;

void CharacterDisplay::drawLetter(char letter, int x, int y)
{
    switch (letter)
    {
    case '0':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 4, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 2, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case '1':
        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 1, x, y);
        lightPixel(2, 2, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 4, x, y);
        lightPixel(2, 5, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 6, x, y);
        break;
    case '2':
        lightPixel(0, 1, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 6, x, y);
        break;
    case '3':
        lightPixel(0, 1, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case '4':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);

        lightPixel(1, 3, x, y);

        lightPixel(2, 3, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 1, x, y);
        lightPixel(3, 2, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 4, x, y);
        lightPixel(3, 5, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 3, x, y);
        break;
    case '5':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case '6':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case '7':
        lightPixel(0, 0, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 4, x, y);
        lightPixel(1, 5, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        break;
    case '8':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case '9':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'A':
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 1, x, y);
        lightPixel(1, 3, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);

        lightPixel(3, 1, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'B':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'C':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'D':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'E':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'F':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 0, x, y);
        break;
    case 'G':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 4, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 4, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'H':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 3, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'I':
        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 1, x, y);
        lightPixel(2, 2, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 4, x, y);
        lightPixel(2, 5, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 6, x, y);
        break;
    case 'J':
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 6, x, y);

        lightPixel(2, 6, x, y);

        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'K':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 3, x, y);

        lightPixel(2, 2, x, y);
        lightPixel(2, 4, x, y);

        lightPixel(3, 1, x, y);
        lightPixel(3, 5, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'L':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 6, x, y);
        lightPixel(2, 6, x, y);
        lightPixel(3, 6, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'M':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 1, x, y);
        lightPixel(2, 2, x, y);
        lightPixel(3, 1, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'N':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 2, x, y);

        lightPixel(2, 3, x, y);

        lightPixel(3, 4, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'O':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'P':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        break;
    case 'Q':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 4, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 5, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'R':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'S':
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 3, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 3, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 1, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'T':
        lightPixel(0, 0, x, y);

        lightPixel(1, 0, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 1, x, y);
        lightPixel(2, 2, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 4, x, y);
        lightPixel(2, 5, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);

        lightPixel(4, 0, x, y);
        break;
    case 'U':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);

        lightPixel(1, 6, x, y);

        lightPixel(2, 6, x, y);

        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        break;
    case 'V':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);

        lightPixel(1, 5, x, y);

        lightPixel(2, 6, x, y);

        lightPixel(3, 5, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        break;
    case 'W':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 5, x, y);

        lightPixel(2, 4, x, y);

        lightPixel(3, 5, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        lightPixel(4, 3, x, y);
        lightPixel(4, 4, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'X':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 2, x, y);
        lightPixel(1, 4, x, y);

        lightPixel(2, 3, x, y);

        lightPixel(3, 2, x, y);
        lightPixel(3, 4, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 5, x, y);
        lightPixel(4, 6, x, y);
        break;
    case 'Y':
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);

        lightPixel(1, 3, x, y);

        lightPixel(2, 4, x, y);
        lightPixel(2, 5, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 3, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 2, x, y);
        break;
    case 'Z':
        lightPixel(0, 0, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);

        lightPixel(1, 0, x, y);
        lightPixel(1, 4, x, y);
        lightPixel(1, 6, x, y);

        lightPixel(2, 0, x, y);
        lightPixel(2, 3, x, y);
        lightPixel(2, 6, x, y);

        lightPixel(3, 0, x, y);
        lightPixel(3, 2, x, y);
        lightPixel(3, 6, x, y);

        lightPixel(4, 0, x, y);
        lightPixel(4, 1, x, y);
        lightPixel(4, 6, x, y);
        break;
    }
}