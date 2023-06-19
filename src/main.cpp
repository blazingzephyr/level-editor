#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ui/styling/TextStyle.hpp"
#include "ui/styling/TextTheme.hpp"
#include "utility/Config.hpp"
#include "utility/Config.hpp"
#include "ui/controls/InputControl.hpp"
#include "ui/controls/NumericUpDown.hpp"
#include <cassert>

#include "utility/Io.hpp"

int main()
{
    //auto a = le::readFile("D:\\Personal\\Projects\\Post-Mid2022\\LevelEditor\\LICENSE");
    


    //fopen_s(&file, "D:\\Personal\\Projects\\Post-Mid2022\\LevelEditor\\A", "w+");

    //fwrite(L"Õåõåõ", 1, 5, file);
    //fclose(file);

    le::writeFile("D:\\Personal\\Projects\\Post-Mid2022\\LevelEditor\\LICENSE", L"ÒÅÑÒÎÂÛÉ ÒÅÊÑÒ");

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::Texture texture;
    texture.loadFromFile("D:\\Personal\\Projects\\Post-Mid2022\\LevelEditor\\resources\\CHKBX.png");

    sf::Font font;
    font.loadFromFile("D:\\Personal\\Projects\\Post-Mid2022\\LevelEditor\\resources\\fbUsv8C5el.ttf");

    le::TextStyle style1;
    style1.m_characterSize = 35;
    style1.m_fillColor = sf::Color::White;
    style1.m_font = &font;
    style1.m_horizontal_align = le::TextStyle::HorizontalAlignment::Center;
    style1.m_vertical_align = le::TextStyle::VerticalAlignment::Center;
    style1.m_letterSpacingFactor = 1;
    style1.m_lineSpacingFactor = 1;
    style1.m_outlineThickness = 0;
    style1.m_outlineColor = sf::Color::Green;
    style1.m_style = sf::Text::Style::Regular;

    le::TextStyle style2;
    style2.m_characterSize = 35;
    style2.m_fillColor = sf::Color::Yellow;
    style2.m_font = &font;
    style2.m_horizontal_align = le::TextStyle::HorizontalAlignment::Center;
    style2.m_vertical_align = le::TextStyle::VerticalAlignment::Center;
    style2.m_letterSpacingFactor = 1;
    style2.m_lineSpacingFactor = 1;
    style2.m_outlineThickness = 0;
    style2.m_outlineColor = sf::Color::Green;
    style2.m_style = sf::Text::Style::Regular;

    le::TextStyle style3;
    style3.m_characterSize = 35;
    style3.m_fillColor = sf::Color::Blue;
    style3.m_font = &font;
    style3.m_horizontal_align = le::TextStyle::HorizontalAlignment::Center;
    style3.m_vertical_align = le::TextStyle::VerticalAlignment::Center;
    style3.m_letterSpacingFactor = 1;
    style3.m_lineSpacingFactor = 1;
    style3.m_outlineThickness = 0;
    style3.m_outlineColor = sf::Color::Green;
    style3.m_style = sf::Text::Style::Regular;

    le::TextStyle style4;
    style4.m_characterSize = 35;
    style4.m_fillColor = sf::Color::Red;
    style4.m_font = &font;
    style4.m_horizontal_align = le::TextStyle::HorizontalAlignment::Center;
    style4.m_vertical_align = le::TextStyle::VerticalAlignment::Center;
    style4.m_letterSpacingFactor = 1;
    style4.m_lineSpacingFactor = 1;
    style4.m_outlineThickness = 0;
    style4.m_outlineColor = sf::Color::Green;
    style4.m_style = sf::Text::Style::Regular;

    le::TextTheme theme = {};
    theme.m_default = &style1;
    theme.m_disabled = &style2;
    theme.m_hovered = &style3;
    theme.m_held = &style4;

    le::InputTextStyle is = {
        .m_cursorDefault = new sf::Cursor(),
        .m_cursorText = new sf::Cursor(),
        .m_selection = sf::Color(0, 50, 255, 120),
        .m_cursor = sf::Color::Red,
        .m_cursorWidth = 2.5f
    };

    is.m_cursorDefault->loadFromSystem(sf::Cursor::Arrow);
    is.m_cursorText->loadFromSystem(sf::Cursor::Text);

    //le::InputControl ic = le::InputControl(
    //    sf::Vector2f(100, 100),
    //    sf::Vector2f(200, 50),
    //    texture,
    //    sf::IntRect(0, 92, 200, 50),
    //    sf::IntRect(0, 92 + 50, 200, 50),
    //    &theme,
    //    &is,
    //    [](le::InputControl&, sf::String) { },
    //    L"HELLYEAH"
    //);

    le::IntNumeric ic = le::IntNumeric(
        sf::Vector2f(500, 200),
        sf::Vector3f(20, 20-92, 30),
        sf::Vector2f(200, 50),
        sf::Vector2f(92, 92),
        texture,
        sf::IntRect(0, 92, 200, 50),
        sf::IntRect(0, 92 + 50, 200, 50),
        sf::IntRect(0, 0, 92, 92),
        sf::IntRect(92, 0, 92, 92),
        &theme,
        &is,
        0,
        100,
        50,
        1,
        300
    );

    while (window.isOpen())
    {
        ic.update();

        sf::Event event;
        while (window.pollEvent(event))
        {
            ic.onWindowEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(ic);
        window.display();
    }

    return 0;
}