#pragma once
#include <iostream>
#include "IWorkerAction.h"
class IExecutionEvent;

/// <summary>
/// Converted to an IWorkerAction for thread pool scheduling
/// </summary>
class StreamAssetLoader :    public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String path;
	IExecutionEvent* execEvent;
};

