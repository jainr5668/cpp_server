#include "VfsService.h"
#include "VfsServiceInjections.h"
#include <vector>
#include <map>
#include <algorithm>
#include "Utils.h"

namespace services
{
    namespace VfsService
    {
        VfsService::VfsService(std::unique_ptr<VfsServiceInjections> vfsServiceInjections)
            : vfsServiceInjections_(std::move(vfsServiceInjections))
        {
            logger_.info("VfsService::VfsService Entry");
            Node *nullParent = nullptr;
            cwd_ = root_ = new services::VfsService::Node("/", true, nullParent);
            for (auto &child : std::vector<std::string>{"home", "bin", "etc", "var", "boot", "dev", "lib", "mnt", "opt", "proc", "root", "run", "sbin", "srv", "sys", "tmp", "usr"})
            {
                executeCommand("mkdir " + child);
            }
            logger_.info("VfsService::VfsService Exit");
        }

        VfsService::~VfsService()
        {
            rm(root_, true);
            delete cwd_;
        }

        std::string VfsService::executeCommand(std::string command)
        {
            logger_.info("VfsService::executeCommand Entry");
            auto commandVector = Utils::splitByStream(command);
            std::string result;
            command = commandVector[0];
            if (command == "ls")
            {
                result = ls(commandVector.size() > 1 ? commandVector[1] : "");
            }
            else if (command == "cd")
            {
                result = cd(commandVector.size() > 1 ? commandVector[1] : "");
            }
            else if (command == "pwd")
            {
                result = pwd();
            }
            else if (command == "mkdir")
            {
                result = mkdir(commandVector.size() > 1 ? commandVector[1] : "");
            }
            else if (command == "rmdir")
            {
                result = "rmdir";
            }
            else if (command == "touch")
            {
                result = "touch";
            }
            else if (command == "rm")
            {
                result = "rm";
            }
            else if (command == "exit")
            {
                result = "exit";
            }
            else
            {
                result = "Invalid command";
            }
            logger_.info("VfsService::executeCommand Exit");
            return result;
        }

        std::string VfsService::ls(std::string path)
        {
            std::string result;
            services::VfsService::Node *node = nullptr;
            if (path.empty())
            {
                node = cwd_;
            }
            if (node == nullptr)
            {
                result = "Invalid path";
            }
            else
            {

                std::vector<std::string> items;
                for (const auto &pair : cwd_->children)
                {
                    items.push_back(pair.first);
                }
                std::sort(items.begin(), items.end());
                for (const auto &item : items)
                {
                    result += item + " ";
                }
            }
            return result;
        }

        std::string VfsService::pwd()
        {
            std::string result;
            services::VfsService::Node *node = cwd_;
            while (node != nullptr)
            {
                if (node->name != root_->name)
                {
                    result = "/" + node->name + result;
                }
                node = node->parent;
            }
            if (result.empty() && cwd_->name == root_->name)
            {
                result = cwd_->name;
            }
            return result;
        }

        std::string VfsService::cd(std::string path)
        {
            if (path == "..")
            {
                cwd_ = cwd_->parent;
                return "";
            }
            else if (path == "/")
            {
                cwd_ = root_;
                return "";
            }
            else
            {
                for (auto &child : cwd_->children)
                {
                    if (child.first == path)
                    {
                        cwd_ = child.second;
                        return "";
                    }
                }
            }
            return "Invalid Path";
        }

        std::string VfsService::mkdir(std::string path)
        {
            std::string result;
            if (path.empty())
            {
                result = "Invalid path";
            }
            if (cwd_->children.find(path) != cwd_->children.end())
            {
                return "Directory already exists";
            }
            auto node = cwd_;
            for (auto &name : Utils::splitByStream(path, '/'))
            {
                if (node->children.find(name) == node->children.end())
                {
                    node->children[name] = new services::VfsService::Node(name, true, node);
                }
                node = node->children[name];
            }
            return result;
        }

        std::string VfsService::rm(Node *node, bool rmChildren)
        {
            std::string result;
            if (node == nullptr)
            {
                result = "Invalid path";
            }
            else
            {
                if (node->children.empty())
                {
                    node->parent->children.erase(node->name);
                    delete node;
                }
                else
                {
                    if (rmChildren)
                    {
                        for (auto &child : node->children)
                        {
                            rm(child.second, true);
                        }
                    }
                    result = "Directory not empty";
                }
                // node->parent->children.erase(node->name);
                // delete node;
            }
            return result;
        }
    } // namespace VfsService
} // namespace services