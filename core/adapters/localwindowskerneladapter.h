/*
Copyright 2020-2024 Vector 35 Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once
#include "dbgengadapter.h"

namespace BinaryNinjaDebugger {
    class LocalWindowsKernelAdapter: public DbgEngAdapter
    {
    public:
		LocalWindowsKernelAdapter(BinaryView* data);

        [[nodiscard]] bool ExecuteWithArgsInternal(const std::string& path, const std::string& args,
           const std::string& workingDir, const LaunchConfigurations& configs = {}) override;

		bool Start() override;
		void Reset() override;

		bool Detach() override;
		bool Quit() override;

		bool Attach(std::uint32_t pid) override { return false; }
		bool Connect(const std::string& server, std::uint32_t port) override { return false; }
		std::vector<DebugProcess> GetProcessList() override {return {}; }
		bool ConnectToDebugServer(const std::string& server, std::uint32_t port) override { return false; }
		bool DisconnectDebugServer() override { return false; }
    };

    class LocalWindowsKernelAdapterType : public DebugAdapterType
    {
    public:
		LocalWindowsKernelAdapterType();
        virtual DebugAdapter* Create(BinaryNinja::BinaryView* data);
        virtual bool IsValidForData(BinaryNinja::BinaryView* data);
        virtual bool CanExecute(BinaryNinja::BinaryView* data);
        virtual bool CanConnect(BinaryNinja::BinaryView* data);
    };

    void InitLocalWindowsKernelAdapterType();
};
