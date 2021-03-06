#include "stdafx.h"
#include "Gui.h"

//====================================== Button class ======================================


gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BUTTON::BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y - (this->shape.getGlobalBounds().height / 2.f) + (this->text.getGlobalBounds().height / 2.f)
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	this->shape.setFillColor(this->idleColor);

}

gui::Button::Button(float x, float y, float width, float height,
	float text_offset_y,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BUTTON::BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y - (this->shape.getGlobalBounds().height / 2.f) + (this->text.getGlobalBounds().height / 2.f) + text_offset_y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	this->shape.setFillColor(this->idleColor);

}

gui::Button::~Button()
{
}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BUTTON::BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hoover and pressed*/

	//Idle
	this->buttonState = BUTTON::BTN_IDLE;

	//Hover

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BUTTON::BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTTON::BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BUTTON::BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BUTTON::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);

		break;
	case BUTTON::BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);

		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);

		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


//====================================== End Button class ======================================
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//====================================== DropDownList class ====================================

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[],
	unsigned nrOfElements, unsigned defaul_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	this->list.reserve(nrOfElements + 1U);

	this->activeElement =
		new gui::Button(
			x, y, width, height,
			&this->font, list[defaul_index], 16,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
		);

	for (unsigned short index = 0; index < nrOfElements; index++)
	{
		this->list.emplace_back(
			new gui::Button(
				x, y + ((index + 1) * height), width, height,
				&this->font, list[index], 16,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				index
			)
		);
	}

}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}

}

//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}


}

void gui::DropDownList::render(sf::RenderTarget& target)
{

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
	this->activeElement->render(target);

}

//====================================== End DropDownList class ================================
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//====================================== TextureSelector class ====================================

//Init Functions
void gui::TextureSelector::initVariables()
{
	this->selected = false;
	this->hidden = false;
	this->hide_btn = NULL;
	this->offset = sf::Vector2f(100.f, 0.f);
}

void gui::TextureSelector::initContainer(float x, float y, float width, float height)
{
	//Setting bounds of container
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	//Setting container
	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);
}

void gui::TextureSelector::initTextureSheet(float x, float y, const sf::Texture* texture_sheet)
{
	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	//Setting textureRect size
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(
			sf::IntRect(
				0,
				0,
				static_cast<int>(this->bounds.getGlobalBounds().width),
				static_cast<int>(this->sheet.getGlobalBounds().height)
			)
		);
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(
			sf::IntRect(
				0,
				0,
				static_cast<int>(this->sheet.getGlobalBounds().width),
				static_cast<int>(this->bounds.getGlobalBounds().height)
			)
		);
	}

	this->textureRect.width = static_cast<int>(this->gridSize);
	this->textureRect.height = static_cast<int>(this->gridSize);
}

//Constructors and Destructors
gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize,
	const sf::Texture* texture_sheet, sf::Font& font, std::string text)
	: gridSize(gridSize), keytimeMax(2.f), keytime(0.f)
{
	this->initVariables();
	this->initContainer(x + offset.x, y + offset.y, width, height);
	this->initTextureSheet(x + offset.x, y + offset.y, texture_sheet);

	this->hide_btn = new gui::Button(
		x, y, 50.f, 50.f,
		&font, text, 16,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 0)
	);

}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

//Accessors
const bool& gui::TextureSelector::getActive() const
{
	return this->selected;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);
	//Update button
	this->hide_btn->update(static_cast<sf::Vector2f>(mousePosWindow));

	if (this->hide_btn->isPressed() && this->getKeytime())
	{
		if (!this->hidden)
			this->hidden = true;
		else
			this->hidden = false;
	}

	if (!this->hidden)
	{
		//If mouse is inside the bounderies, change status to selected.
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->selected = true;
		else
			this->selected = false;

		//If selected set selector Rectangle position
		if (this->selected)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			//Debugging
			//Update texture rectangle position
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{

	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		//If mouse is inside container show selector of a texture
		if (this->selected)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);

}

void gui::TextureSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		//If mouse is inside container show selector of a texture
		if (this->selected)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);
}

//====================================== End DropDownList class ================================
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//====================================== ------------ class ====================================