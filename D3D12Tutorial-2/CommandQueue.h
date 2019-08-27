/**
 * Wrapper classf or a ID3D12CommandQueue, per https://www.3dgep.com/learning-directx12-2/
 * Mostly the same, with additional comments
 */

#pragma once

#include <d3d12.h>	// For ID3D12CommandQueue, ID3D12Device2, ID3D12Fence
#include <wrl.h>	// Microsoft::WRL::ComPtr

#include <cstdint>	// uint64_t
#include <queue>	

using namespace Microsoft::WRL; 

class CommandQueue
{
public:
	CommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	virtual ~CommandQueue();

	// Get an available command list from the command queue
	ComPtr<ID3D12GraphicsCommandList2> GetCommandList();

	// Exec a command list, returns fence value to wait for for this command list
	uint64_t ExecuteCommandList(ComPtr<ID3D12GraphicsCommandList2> commandList);

	uint64_t Signal();
	bool IsFenceComplete(uint64_t fenceValue);
	void WaitForFenceValue(uint64_t fenceValue);
	void Flush();

	ComPtr<ID3D12CommandQueue> GetD3D12CommandQueue() const;

protected:
	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator();
	ComPtr<ID3D12GraphicsCommandList2> CreateCommandList(ComPtr<ID3D12CommandAllocator> allocator);

private:
	// Keep track of command allocators 'in flight'


};