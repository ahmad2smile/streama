//
// Created by ahmad on 8/15/24.
//

#ifndef ORAI_TEXTLIST_H
#define ORAI_TEXTLIST_H


#include "Component.h"
#include "Text.h"

class TextList final : public Component {
public:
    explicit TextList(sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize = 25,
                      const sf::Vector2f& position = {0, 0}, const sf::Vector2f& size = {0, 0});

    ~TextList() override;

    void setItems(std::vector<std::wstring>& values) const;

    void addItem(std::wstring&& value) const;

    [[nodiscard]] const Text* getSelectedItem() const;

    void clear() const;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<Text*>* _items;
    unsigned int _fontSize;
    float _scrollOffset;
    const Text* _selectedText;
    size_t _selectedTextIndex;
    const sf::Color _colorSelected = sf::Color(0, 0, 250);
    const sf::Color _colorDark = sf::Color(128, 128, 128);
    const sf::Color _colorLight = sf::Color(192, 192, 192);
};


#endif //ORAI_TEXTLIST_H
