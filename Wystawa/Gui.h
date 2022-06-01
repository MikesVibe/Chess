#pragma once

enum class BUTTON {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	public:
		//Constructors and Destrucotrs
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);

		Button(float x, float y, float width, float height,
			float text_offset_y,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);


		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	private:
		BUTTON buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	};

	class DropDownList
	{
	public:
		//Constructors and Destrucotrs
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaul_index = 0);
		~DropDownList();

		//Accessors
		const bool getKeytime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);

	private:
		float keytime;
		const float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	};

	class TextureSelector : public sf::Drawable
	{
	public:
		//Constructors and Destrucotrs
		TextureSelector(float x, float y, float width, float height, float gridSize,
			const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		//Public Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		//Private Functions
		void initVariables();
		void initContainer(float x, float y, float width, float height);
		void initTextureSheet(float x, float y, const sf::Texture* texture_sheet);

	private:
		//Private Variables
		float keytime;
		float keytimeMax;
		float gridSize;
		bool selected;
		bool hidden;
		gui::Button* hide_btn;
		sf::Vector2f offset;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	};
}
