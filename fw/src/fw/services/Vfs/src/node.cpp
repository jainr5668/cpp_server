#include "node.h"

namespace services
{
    namespace VfsService
    {
        Node::Node(std::string name, bool isDictonary, Node *parent)
            : name(name), isDictonary(isDictonary), parent(parent)
        {
        }
        Node::~Node()
        {
            for (auto &child : children)
            {
                delete child.second;
            }
        }
    } // namespace VfsService
} // namespace services