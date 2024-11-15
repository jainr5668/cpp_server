#pragma once
#include <map>
#include <memory>
#include <string>

namespace services
{
    namespace VfsService
    {
        class Node
        {
        public:
            std::string name;
            bool isDictonary;
            std::map<std::string, Node *> children;
            std::string data;
            Node *parent;
            Node(std::string name, bool isDictonary, Node *parent);
            ~Node();
        }; // class Node
    } // namespace VfsService
} // namespace services