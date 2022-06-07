/*
Copyright 2020-2022 Vector 35 Inc.

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

#include <QToolBar>
#include <QMenu>
#include <QToolButton>
#include <QIcon>
#include <QLineEdit>
#include "binaryninjaapi.h"
#include "uicontext.h"
#include "debuggerwidget.h"
#include "debuggerapi.h"
#include "statusbar.h"

// Each UIContext has exactly one GlobalDebuggerUI. One GlobalDebuggerUI can contain multiple DebuggerUI.
class GlobalDebuggerUI: public QObject
{
Q_OBJECT

private:
	UIContext* m_context;
	DebuggerController* m_controller;
	QMainWindow* m_window;
	DebuggerStatusBarContainer* m_status;

public:
	GlobalDebuggerUI(UIContext* context);
	~GlobalDebuggerUI();

	static void InitializeUI();

	static GlobalDebuggerUI* CreateForContext(UIContext* context);
	static GlobalDebuggerUI* GetForContext(UIContext* context);
	static void RemoveForContext(UIContext* context);

	void SetActiveFrame(ViewFrame* frame);

	void SetupMenu(UIContext* context);
};



class DebuggerUI: public QObject
{
    Q_OBJECT

private:
	UIContext* m_context;
    DebuggerController* m_controller;
	QMainWindow* m_window;
	QLabel* m_status;

	size_t m_eventCallback;

public:
    DebuggerUI(UIContext* context, DebuggerController* controller);
	~DebuggerUI();

    static void InitializeUI();

	static DebuggerUI* CreateForViewFrame(ViewFrame* frame);
	static DebuggerUI* GetForViewFrame(ViewFrame* frame);

	void SetActiveFrame(ViewFrame* frame);

	TagTypeRef getPCTagType(BinaryViewRef data);
	TagTypeRef getBreakpointTagType(BinaryViewRef data);

	void navigateDebugger(uint64_t address);

signals:
	void debuggerEvent(const DebuggerEvent& event);

private slots:
	void updateUI(const DebuggerEvent& event);
};
