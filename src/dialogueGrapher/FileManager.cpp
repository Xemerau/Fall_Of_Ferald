#include "FileManager.h"
#include <iostream>
#include <fstream>

FileManager::FileManager()
{
	/*std::ifstream ifs(globalFlagPath);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const Json::Value& globals = obj["globals"];
	for (int i = 0; i < globals.size(); ++i)
	{
		std::cout << globals[i]["key"].asString();
		std::cout << " " << globals[i]["value"].asBool();
		std::cout << std::endl;
	}*/
}

void FileManager::loadDialogue(const std::string& moduleFile)
{
	std::ifstream ifs(dialogueFolder + moduleFile);
	Json::Reader reader;
	Json::Value obj;

	if (ifs.good())
	{
		reader.parse(ifs, obj);
		const Json::Value& nodes = obj["nodes"];

		std::cout << "Module Name: " << obj["module"].asString() << std::endl;
		for (int i = 0; i < nodes.size(); ++i)
		{
			// Getting the connections
			const Json::Value& conns = nodes[i]["connectors"];

			std::cout << "ID: " << nodes[i]["id"].asString() << std::endl;
			std::cout << "header: " << nodes[i]["header"].asString() << std::endl;
			std::cout << "body: " << nodes[i]["body"].asString() << std::endl;
			std::cout << "connectors:\n{" << std::endl;

			for (int j = 0; j < conns.size(); ++j)
			{
				// Getting this connections flags
				const Json::Value& flags = conns[j]["flags"];

				std::cout << "\ttargetID: " << conns[j]["targetID"].asString() << std::endl;
				std::cout << "\tchoiceText: " << conns[j]["choiceText"].asString() << std::endl;
				std::cout << "\tpriority: " << conns[j]["priority"].asInt() << std::endl;
				std::cout << "\tflags:\n\t{" << std::endl;

				for (int k = 0; k < flags.size(); ++k)
				{
					std::cout << "\t\t" << flags[k]["key"].asString() << std::endl;
					std::cout << "\t\t" << flags[k]["value"].asBool() << std::endl;
				}
				std::cout << "\t}" << std::endl;
			}
			std::cout << "}" << std::endl;
		}
	}
	else std::cerr << moduleFile << " not found!" << std::endl;
}

std::vector<Node*> FileManager::loadDialogue(const std::string& moduleFile, std::string& moduleName)
{
	std::ifstream ifs(dialogueFolder + moduleFile);
	Json::Reader reader;
	Json::Value obj;
	std::vector<Node*> finalNodes;

	if (ifs.good())
	{
		reader.parse(ifs, obj);
		const Json::Value& nodes = obj["nodes"];

		moduleName = obj["module"].asString();
		
		// Populating the initial nodes
		for (int i = 0; i < nodes.size(); ++i)
		{
			finalNodes.push_back(new Node(nodes[i]["id"].asString()));
			auto currentNode = finalNodes.back();

			currentNode->setHeader(nodes[i]["header"].asString());
			currentNode->setBody(nodes[i]["body"].asString());
		}

		// Now that all the nodes are created, populate the connections
		for (int i = 0; i < nodes.size(); ++i)
		{
			const Json::Value& conns = nodes[i]["connectors"];

			// Adding the connections
			for (int j = 0; j < conns.size(); ++j)
			{
				// Getting this connections flags
				const Json::Value& flags = conns[j]["flags"];

				Node* connectionTarget = NULL;
				const std::string& targetID = conns[j]["targetID"].asString();

				// Finding the pointer to our final node
				for (auto n : finalNodes)
				{
					if (targetID == n->getIdentifier())
					{
						connectionTarget = n;
						break;
					}
				}

				if (connectionTarget == NULL)
				{
					std::cerr << "Cannot create connection, node with ID " << targetID;
					std::cerr << " doesn't exist!" << std::endl;
					break;	// Skipping to the next connection
				}

				Connector connection(finalNodes[i], connectionTarget, conns[j]["priority"].asInt());

				// Populating the flags if need be
				for (int k = 0; k < flags.size(); ++k)
				{
					connection.addFlag(flags[k]["key"].asString(), flags[k]["value"].asBool());
				}

				finalNodes[i]->addConnector(connection);
			}
		}
	}
	else std::cerr << moduleFile << " not found!" << std::endl;

	return finalNodes;
}

FileManager::~FileManager()
{
}