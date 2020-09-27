#include "Game.h"

#include "common.h"
#include "ErectusProcess.h"
#include "TesWorldSpace.h"
#include "utils.h"

LoadedAreaManager Game::GetLoadedAreaManager()
{
	LoadedAreaManager result = {};

	std::uintptr_t loadedAreaManagerPtr;
	if (!ErectusProcess::Rpm(ErectusProcess::exe + OFFSET_ENTITY_LIST, &loadedAreaManagerPtr, sizeof loadedAreaManagerPtr))
		return result;
	if (!Utils::Valid(loadedAreaManagerPtr))
		return result;

	ErectusProcess::Rpm(loadedAreaManagerPtr, &result, sizeof result);

	return result;
}

LocalPlayer Game::GetLocalPlayer()
{
	LocalPlayer result = {};

	std::uintptr_t localPlayerPtr;
	if (!ErectusProcess::Rpm(ErectusProcess::exe + OFFSET_LOCAL_PLAYER, &localPlayerPtr, sizeof localPlayerPtr))
		return result;
	if (!Utils::Valid(localPlayerPtr))
		return result;

	ErectusProcess::Rpm(localPlayerPtr, &result, sizeof result);
	result.ptr = localPlayerPtr;

	return result;
}

std::vector<TesObjectCell> Game::GetLoadedCells()
{
	auto result = GetLoadedAreaManager().GetLoadedCells();
	result.push_back(GetSkyCell());

	return result;
}

TesObjectCell Game::GetSkyCell()
{
	TesObjectCell result = {};

	DWORD64 worldspacePtr = 0;
	if (!ErectusProcess::Rpm(ErectusProcess::exe + OFFSET_MAIN_WORLDSPACE, &worldspacePtr, sizeof worldspacePtr))
		return result;
	if (!Utils::Valid(worldspacePtr))
		return result;

	TesWorldSpace worldspace = {};
	if (!ErectusProcess::Rpm(worldspacePtr, &worldspace, sizeof worldspace))
		return result;

	ErectusProcess::Rpm(worldspace.skyCellPtr, &result, sizeof result);

	return result;
}