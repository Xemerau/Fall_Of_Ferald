#include "NodeView.h"
#include <iostream>

// Determines the node ID using the current module ID and the number of
// nodes in the module
NodeView::NodeView(const std::string& moduleID, int nodeCount,
				   const sf::Vector2f position, const sf::Font& font)
{
	node = new Node(moduleID + std::to_string(nodeCount));
	this->position = position;

	// Default sizes
	size = sf::Vector2f(100, 100);
	sf::Vector2f iboxSize(size.x - (2 * spacing), size.y / 2 - (2*spacing));
	sf::Vector2f iboxPos = this->position;

	// Initilising the base rectangle
	baseRect = sf::RectangleShape(size);
	baseRect.setPosition(this->position);
	baseRect.setPosition(this->position.x, this->position.y);
	baseRect.setFillColor(sf::Color(100, 32, 32));
	idText = sf::Text(moduleID + std::to_string(nodeCount), font);
	idText.setPosition(this->position);
	idText.move(0, -35);

	// Creating the header input box
	iboxPos.x += spacing;
	iboxPos.y += spacing;
	headerInput = InputBox(iboxPos, iboxSize, font);

	// Creating the body input box
	iboxPos = headerInput.getPosition();
	iboxPos.y += (iboxSize.y + spacing * 2);
	bodyInput = InputBox(iboxPos, iboxSize, font);
	/*for(int i = 0; i < 3; ++i)
	{
		rects[i] = sf::RectangleShape(position);
		rects[i].setPosition(this->position);

		texts[i] = sf::Text("", font);
		texts[i].setPosition(this->position);

		// Base box & text
		if(i == 0)
		{
			rects[i].setSize(size);
			rects[i].setFillColor(sf::Color(100,32,32));
			texts[i].setString(node->getIdentifier());
			texts[i].setPosition(this->position.x, this->position.y - 35);
		}
		else
		{
			rects[i].setPosition(this->position.x + spacing,
								 (this->position.y * i) + spacing);
			rects[i].setSize(textboxSize);
		}
	}*/
}

void NodeView::setID(const std::string& moduleID, int nodeNumber)
{
	if (node)
	{
		std::string newID = moduleID + std::to_string(nodeNumber);
		node->setID(newID);
		idText.setString(newID);
	}
}

void NodeView::move(const sf::Vector2f& vector)
{
	baseRect.move(vector);
	idText.move(vector);
	headerInput.move(vector);
	bodyInput.move(vector);
}

void NodeView::setScale(float scale)
{
	if(scale < 0)
		return;

	baseRect.setScale(scale, scale);
	idText.setScale(baseRect.getScale());
	headerInput.setScale(baseRect.getScale());
	bodyInput.setScale(baseRect.getScale());
}

sf::FloatRect NodeView::getGlobalBounds()
{
	return baseRect.getGlobalBounds();
}

bool NodeView::removeRequired(const sf::Vector2f& mousePos)
{
	if(baseRect.getGlobalBounds().contains(mousePos))
	{
		delete node;
		node = NULL;
		return true;
	}
	else
	{
		return false;
	}
}
InputBox* NodeView::getSelectedInputBox(const sf::Vector2f& mousePos)
{
	if (headerInput.checkClicked(mousePos))
		return &headerInput;
	else if (bodyInput.checkClicked(mousePos))
		return &bodyInput;
	else return NULL;
}

// Returns the header/body value saved in Node if either input box is selected
std::string NodeView::getUnsavedInput()
{
	if (!node)
		return "";

	if (headerInput.isSelected())
		return node->getHeader();
	else if (bodyInput.isSelected())
		return node->getBody();
	else return "";
}

void NodeView::update()
{
	if (node)
	{
		node->setHeader(headerInput.getString());
		node->setBody(bodyInput.getString());

		// DEBUG
		std::cout << node->getIdentifier() << ":" << std::endl;
		std::cout << "\tHEADER: " << node->getHeader() << std::endl;
		std::cout << "\tBODY: " << node->getBody() << std::endl;
	}
}


void NodeView::render(sf::RenderWindow& window)
{
	window.draw(baseRect);
	window.draw(idText);
	headerInput.render(window);
	bodyInput.render(window);
}

NodeView::~NodeView()
{
	delete node;
	node = 0;
}