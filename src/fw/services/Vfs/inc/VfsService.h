#pragma once
#include "IVfsService.h"
#include "VfsServiceInjections.h"
#include "node.h"
#include "logger.h"

namespace services
{
    namespace VfsService
    {
        class VfsService : public IVfsService
        {
        public:
            VfsService(std::unique_ptr<VfsServiceInjections> vfsServiceInjections);
            ~VfsService();
            std::string executeCommand(std::string command) override;

        private:
            Logger logger_;
            std::unique_ptr<VfsServiceInjections> vfsServiceInjections_;
            Node *root_{nullptr};
            Node *cwd_{nullptr};
            std::string ls(std::string path);
            std::string pwd();
            std::string cd(std::string path);
            std::string mkdir(std::string path);
            std::string rm(Node* node, bool rmChildren);
        };
    } // namespace VfsService
} // namespace services
