#ifndef D3d12DescriptorHeap_h__
#define D3d12DescriptorHeap_h__

#include <d3d12.h>
#include "d3d11_helper.h"
#include "FatalError.h"
#include <vector>
#include "ForwardListItem.h"
#include <wrl.h>

using namespace Microsoft::WRL;

class D3d12DescriptorHeapAllocator {
public:
	//Assuming that heap is EMPTY!
	D3d12DescriptorHeapAllocator(ComPtr<ID3D12DescriptorHeap> heap):_heap(heap)
	{
		_descriptor = heap->GetDesc();
		_heapStartAddress = heap->GetCPUDescriptorHandleForHeapStart().ptr;
		ID3D12DevicePtr device;
		heap->GetDevice(IID_PPV_ARGS(&device));
		_itemSize = device->GetDescriptorHandleIncrementSize(_descriptor.Type);

		_items.resize(_descriptor.NumDescriptors);
		//init free items list 
		for(size_t i = 0; i < _descriptor.NumDescriptors - 1; ++i){
			_items[i].next = &_items[i + 1];
		}
		_items[_descriptor.NumDescriptors - 1].next = nullptr;
		_listHead = &_items[0];
	}

	D3D12_CPU_DESCRIPTOR_HANDLE alloc(){
		if(_listHead == nullptr){
			return {0};
		}
		auto allocatedId = getItemIndex(_listHead);
		auto resultAddress = _heapStartAddress + (allocatedId * _itemSize);
		_listHead = _listHead->next;
		return{ resultAddress };
	}
	void free(D3D12_CPU_DESCRIPTOR_HANDLE handle){
		auto itemId = getDescriptorId(handle);
		if (itemId >= _items.size()) {
			throw std::exception("Invalid handle");
		}
		auto freeItem = &_items[itemId];
		freeItem->next = _listHead;
		_listHead = freeItem;

	}
	ComPtr<ID3D12DescriptorHeap> getHeap()
	{
		return _heap;
	}
	size_t getItemSize() const
	{
		return _itemSize;
	}
	size_t getDescriptorId(D3D12_CPU_DESCRIPTOR_HANDLE handle) const
	{
		if (handle.ptr < _heapStartAddress) {
			throw std::exception("Invalid handle");
		}
		return (handle.ptr - _heapStartAddress) / _itemSize;
	}
	size_t getDescriptorsCount() const
	{
		return _descriptor.NumDescriptors;
	}
private:
	size_t getItemIndex(const ForwardListItem* item) const noexcept{
		return (item - &_items[0]);
	}
	ComPtr<ID3D12DescriptorHeap> _heap;
	ForwardListItem* _listHead = nullptr;
	std::vector<ForwardListItem> _items;
	D3D12_DESCRIPTOR_HEAP_DESC _descriptor;
	size_t _itemSize;
	size_t _heapStartAddress;
};

#endif // D3d12DescriptorHeap_h__
